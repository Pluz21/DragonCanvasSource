//Copyright © 2023 Pluz21(TVL).All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

class UMoveComponent;
class ADragon;
class UMaterialCheckerComponent;

UCLASS()
class DRAGONCANVAS_API AEnemy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemy();
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> root;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> baseMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> secondMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMoveComponent> moveCompo;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialCheckerComponent> materialCheckerCompo;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> soundToPlay;

	UPROPERTY(EditAnywhere)
	TObjectPtr<ADragon> playerRef;
	
	UPROPERTY(EditAnywhere)
	float lifeSpan = 20;
	UPROPERTY(EditAnywhere)
	float minDistanceAllowed = 150.f;
	UPROPERTY(EditAnywhere)
	int damageToApply = 1;

	// Timer
	UPROPERTY(EditAnywhere)
	float currentTime = 0;
	UPROPERTY(EditAnywhere)
	float maxTime = 4;
	UPROPERTY(EditAnywhere)
	bool canStartDestroytimer = false;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Init();

	bool CheckDistance();

	UFUNCTION(BlueprintCallable)
	void SelfDestroy();

	UFUNCTION(BlueprintCallable)
	void ApplyDamage();
	UFUNCTION(BlueprintCallable)
	void PlaySound(USoundBase* _audioToPlay);

	// Timer functions
	void StartDestroyTimer();
	float IncreaseTime(float _current, float _max);
	void SetCanStartDestroyTimer(bool _value);

	UStaticMeshComponent* GetBaseMesh() { return baseMesh; }
	UStaticMeshComponent* GetSecondMesh() { return secondMesh; }
	void SetEnemyMaterial(UMaterialInterface* _newMat) { baseMesh->SetMaterial(0,_newMat) ; }
	UMaterialCheckerComponent* GetMaterialCheckerComponent() { return materialCheckerCompo; }


};
