// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileManager.generated.h"
class AProjectile;

UCLASS()
class DRAGONCANVAS_API AProjectileManager : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TArray<AProjectile*> allProjectiles;
	
public:	
	// Sets default values for this actor's properties
	AProjectileManager();
	TArray<AProjectile*> GetAllProjectiles() { return allProjectiles; }
	int GetAllProjectilesSize() { return GetAllProjectiles().Num(); }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AddItem(TObjectPtr<AProjectile> _item);
	void RemoveItem(TObjectPtr<AProjectile> _item);
	TObjectPtr<AProjectile> GetItem(const int& _index); //we need the index. 
	bool Exists(TObjectPtr<AProjectile> _item);
	bool Exists(const int& _index);

};
