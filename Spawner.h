// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"
	
class UBillboardComponent;
UCLASS()
class DRAGONCANVAS_API ASpawner : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<AActor> actorToSpawn;
	UPROPERTY(VisibleAnywhere, Category = "Spawner")
	TArray<AActor*> allSpawned;
	UPROPERTY(EditAnywhere, Category = "Spawner")
	TObjectPtr<UBillboardComponent> billboardComponent;
	UPROPERTY()
	TObjectPtr<USceneComponent> root;
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(CallInEditor, Category = "Spawner")
	AActor* Spawn();
	UFUNCTION(CallInEditor, Category = "Spawner")
	void Remove();
	UFUNCTION(CallInEditor, Category = "Spawner")
	void RemoveAll();

};
