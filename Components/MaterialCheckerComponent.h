// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MaterialCheckerComponent.generated.h"

class AProjectileManager;
class AEnemy;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONCANVAS_API UMaterialCheckerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMaterialCheckerComponent();
	UPROPERTY(EditAnywhere)
	TObjectPtr<AProjectileManager> projectileManager;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInterface*> allMatsToCheck;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/**
* Returns true if targetToCheck has same material as component owner.
*/
	UFUNCTION(BlueprintCallable)
	bool ActorMaterialCheck(AActor*& _targetToCheck);
	bool EnemyMaterialCheck(AEnemy*& _enemyToCheck);

	UMaterialInterface* FindActorMaterial(AActor*& _actor);
	UMaterialInterface* FindEnemyMaterial(AEnemy*& _enemyToCheck);
	TArray<UMaterialInterface*> GetAllMatsToCheck() { return allMatsToCheck; }
	float GetAllMatsSize() { return allMatsToCheck.Num(); }
	void RemoveMaterialAtIndex(int _index);
};
