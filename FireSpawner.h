// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.h"
#include "FireSpawner.generated.h"

UCLASS()
class DRAGONCANVAS_API AFireSpawner : public ASpawner
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
