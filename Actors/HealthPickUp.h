// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemPickUp.h"
#include "HealthPickUp.generated.h"

class ADragon;
class UHealthComponent;

UCLASS()
class DRAGONCANVAS_API AHealthPickUp : public AItemPickUp
{
	GENERATED_BODY()	

	


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float healthToAdd = 5;

	

public:
	// Sets default values for this actor's properties
	AHealthPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ManageOverlap(AActor* _overlapped, AActor* _overlap) override;



};
