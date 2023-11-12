// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConeLineTrace.generated.h"

UCLASS()
class DRAGONCANVAS_API UConeLineTrace : public UActorComponent
{
	GENERATED_BODY()
	
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> ownerRef;
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> _coneTraceChannel;

	UPROPERTY(EditAnywhere)
	float distance = 100;
	
	UPROPERTY(EditAnywhere)
	float coneTraceRadius = 300;

public:	
	// Sets default values for this actor's properties
	UConeLineTrace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ConeTrace();

};
