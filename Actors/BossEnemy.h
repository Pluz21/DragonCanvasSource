// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIController.h"
#include "DragonCanvas/Actors/Enemy.h"
#include "BossEnemy.generated.h"

class UPawnSensingComponent;
class AAIController;
class AProjectile;
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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnteredRangeEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoseMeshEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLostAllMeshesEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetSetEvent, bool, value);


	UPROPERTY()
	FEnteredRangeEvent onEnterRange;
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
	float range = 700.f;
	UPROPERTY(EditAnywhere)
	bool canAttack = false;
	UPROPERTY(EditAnywhere)
	float projectileSpeed = 750;


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
	

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> onMeshLossSound = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> onBossDeathSound = nullptr;

public:
	// Sets default values for this actor's properties
	ABossEnemy();

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Init();
	void InitAI();
	UStaticMeshComponent* GetThirdMesh() { return thirdMesh; }
	//UMaterialCheckerComponent* GetMaterialCheckerComponent2() { return materialCheckerCompo2; }
	void SetAllMeshes(); 
	TArray<UStaticMeshComponent*> GetAllMeshes() { return allMeshes; }
	void RemoveMesh(int _index);
	UFUNCTION()
	void PlayMeshLossSound();
	UFUNCTION()
	void PlayDeathSound();
	FLoseMeshEvent& GetOnMeshLoss() { return onMeshLoss; }
	UFUNCTION()
	void ManageDeathEvent();
	UFUNCTION()
	void SpawnItem(AActor* _actor);
	UFUNCTION()
	void ApplyDeathMeshes();
	void CheckAllMeshes();
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
	void UpdateSpawnPointLocation();

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
	void CheckIsInRange();
	void StopMove();
	void AIBehaviourLogic();
	UFUNCTION()
	void SetCanAttack();
	UFUNCTION()
	void Attack();
	

	void BossEnemyGameLogic();

	
};
