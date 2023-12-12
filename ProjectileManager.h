//Copyright © 2023 Pluz21(TVL).All rights reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileManager.generated.h"
class AProjectile;

UCLASS()
class DRAGONCANVAS_API AProjectileManager : public AActor
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMaterialAcquired, UMaterialInterface*, mat);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FMaterialAcquired onMatAcquired;

	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TArray<AProjectile*> allProjectiles;
	
	UPROPERTY(EditAnywhere)
	TArray<UMaterialInstance*> allCollectedMats;
	
public:	
	// Sets default values for this actor's properties
	AProjectileManager();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddItem(TObjectPtr<AProjectile> _item);
	void RemoveItem(TObjectPtr<AProjectile> _item);
	bool Exists(TObjectPtr<AProjectile> _item);
	bool Exists(const int& _index);
	TObjectPtr<AProjectile> GetItem(const int& _index); //we need the index. 
	TArray<AProjectile*> GetAllProjectiles() { return allProjectiles; }
	int GetAllProjectilesSize() { return GetAllProjectiles().Num(); }

	void AddMaterial(TObjectPtr<UMaterialInstance> _mat);
	void RemoveMaterial(TObjectPtr<UMaterialInstance> _mat);
	bool MatExists(TObjectPtr <UMaterialInstance> _mat);
	bool MatExists(const int& _index);
	TObjectPtr<UMaterialInstance> GetMaterialInstance(const int& _index);
	TArray<UMaterialInstance*> GetAllCollectedMaterialInstances() { return allCollectedMats; }
	int GetAllCollectedMaterialInstancesSize() { return allCollectedMats.Num(); }

	UFUNCTION()
	FMaterialAcquired& OnMatAcquired() { return onMatAcquired; }
};
