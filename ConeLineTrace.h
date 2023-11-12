// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConeLineTrace.generated.h"

UCLASS()
class DRAGONCANVAS_API AConeLineTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConeLineTrace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
