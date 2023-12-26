// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DragonCanvas/Actors/Enemy.h"
#include "BossEnemy.generated.h"

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
};
