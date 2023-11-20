// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorActivator.h"
#include "ColorActivatorProjectile.generated.h"

UCLASS()
class DRAGONCANVAS_API AColorActivatorProjectile : public AColorActivator
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColorActivatorProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ManageOverlap(AActor* _overlap, AActor* _overlapped) override;
};
