// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUps.generated.h"

UCLASS()
class DRAGONCANVAS_API APickUps : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> meshCompo;
	
public:	
	// Sets default values for this actor's properties
	APickUps();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
