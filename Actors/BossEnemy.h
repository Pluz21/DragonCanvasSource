// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DragonCanvas/Actors/Enemy.h"
#include "BossEnemy.generated.h"

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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoseMeshEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLostAllMeshesEvent);
	UPROPERTY()
	FLoseMeshEvent onMeshLoss;
	UPROPERTY()
	FLostAllMeshesEvent onAllMeshesLost;
	GENERATED_BODY()

	//UPROPERTY(EditAnywhere)
	//TObjectPtr<UMaterialCheckerComponent> materialCheckerCompo2;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> thirdMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> fourthMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> fifthMesh;
	UPROPERTY(EditAnywhere)
	TArray<UStaticMeshComponent*> allMeshes;


	UPROPERTY(EditAnywhere)
	TArray<FMeshData> allMeshData;
	UPROPERTY(EditAnywhere)
	bool canDestroyThirdMesh = false;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> onMeshLossSound;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> onBossDeathSound;

public:
	// Sets default values for this actor's properties
	ABossEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Init();
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
	void HandleMeshOverlap(AActor* _otherActor, int _meshIndex);
	void ApplyMaterialToMatchingMesh(UMaterialInterface* _matToApply);

	//bool GetCanDestroyThirdMesh() { return canDestroyThirdMesh; }
};
