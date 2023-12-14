// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemPickUp.generated.h"

 class USoundComponent;

UCLASS(Abstract)
class DRAGONCANVAS_API AItemPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPickUp();
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundComponent> soundCompo; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
