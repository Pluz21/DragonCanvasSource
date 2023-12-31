// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIController.h"
#include "DragonCanvas/Actors/Enemy.h"
#include "BossEnemy.generated.h"

class UPawnSensingComponent;
class AAIController;
class AProjectileBossEnemy;
class AHealthPickUp;

USTRUCT()
struct FMeshData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	bool canBeDestroyed = false;

	// Other properties as needed
};

UCLASS()
class DRAGONCANVAS_API ABossEnemy : public AEnemy
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReturnedToInitialLocationEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnteredAttackRangeEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnteredMinRangeEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoseMeshEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLostAllMeshesEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAggroEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetSetEvent, bool, value);


	UPROPERTY()
	FAggroEvent onAggro;
	UPROPERTY()
	FEnteredMinRangeEvent onEnterMinRange;
	UPROPERTY()
	FEnteredAttackRangeEvent onEnterAttackRange;
	UPROPERTY()
	FLoseMeshEvent onMeshLoss;
	UPROPERTY()
	FLostAllMeshesEvent onAllMeshesLost;
	UPROPERTY()
	FTargetSetEvent onTargetSet;
	UPROPERTY()
	FReturnedToInitialLocationEvent onReturnedToInitialLocation;

	GENERATED_BODY()

	// AI

	UPROPERTY(EditAnywhere)
	FVector initialLocation = FVector(0);
	UPROPERTY(EditAnywhere)
	FRotator initialRotation = FRotator(0);
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPawnSensingComponent> pawnSensor = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AAIController> bossAIController;
	UPROPERTY(EditAnywhere)
	TObjectPtr<APawn> target = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<APawn> lastTarget = nullptr;
	UPROPERTY(EditAnywhere)
	float rotateBackSpeed = 20;
	UPROPERTY(EditAnywhere)
	bool canRotateTowardsPlayer = false;
	UPROPERTY(EditAnywhere)
	float attackRange = 1000.f;
	UPROPERTY(EditAnywhere)
	float minDistanceToPlayer = 600.f;
	
	UPROPERTY(EditAnywhere)
	bool canAttack = false;
	UPROPERTY(EditAnywhere)
	float projectileSpeed = 1500;


	// Meshes
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> thirdMesh = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> fourthMesh = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> fifthMesh = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> faceMesh = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> deathMesh = nullptr;
	UPROPERTY(EditAnywhere)
	TArray<UStaticMeshComponent*> allMeshes;
	UPROPERTY(EditAnywhere)
	FTimerHandle deathMeshTimer;
	UPROPERTY(EditAnywhere)
	float meshBlinkRate = 0.3f;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AHealthPickUp> healthPickupToSpawn;
	UPROPERTY(EditAnywhere)
	TArray<FMeshData> allMeshData;
	
	// Audio
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> onMeshLossSound = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> onBossDeathSound = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> onBossAggroSound = nullptr;
	UPROPERTY(EditAnywhere)
	bool hasPlayedAggroSound = false;

public:
	ABossEnemy();

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Init();
	void InitAI();
	void SetInitialRotation();
	UStaticMeshComponent* GetThirdMesh() { return thirdMesh; }
	void SetAllMeshes(); 
	TArray<UStaticMeshComponent*> GetAllMeshes() { return allMeshes; }
	void RemoveMesh(int _index);

	//Audio
	UFUNCTION()
	void PlayMeshLossSound();
	UFUNCTION()
	void PlayDeathSound();
	UFUNCTION()
	void PlayAggroSound();

	FLoseMeshEvent& GetOnMeshLoss() { return onMeshLoss; }
	//Events
	void CheckAllMeshes();
	UFUNCTION()
	void UpdateSpawnPointLocation();
	UFUNCTION()
	void ManageAllMeshesOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OverlapEventManager();
	UFUNCTION()
	void OnSecondMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnThirdMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnFourthMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnFifthMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void ManageDeathEvent();
	UFUNCTION()
	void ApplyDeathMeshes();
	UFUNCTION()
	void ManageDestructionEvent(AActor* _actor);
	UFUNCTION()
	void HandleMeshOverlap(AActor* _otherActor, int _meshIndex);

	void ApplyMaterialToMatchingMesh(UMaterialInterface* _matToApply);
	
	// AI
	FVector GetInitialLocation() { return initialLocation; }
	virtual void Chase() override;
	UFUNCTION()
	void Detect();
	UFUNCTION()
	void SetTarget(APawn* _pawn);
	void ChasePlayer();
	void ReturnToInitialLocation();
	void CheckReturnedToInitialLocation();
	void RotateToPlayer();
	void CheckMinRange();
	void CheckIsInRangeToAttack();
	UFUNCTION()
	void StopMove();
	UFUNCTION()
	void SetCanAttack();
	UFUNCTION()
	void Attack();
	
	// Boss Logic
	void BossEnemyGameLogic();
	void AIBehaviourLogic();
	
	//Other interactions
	UFUNCTION()
	void HandleReveal();
	
};
