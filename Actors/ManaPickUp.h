// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemPickUp.h"
#include "ManaPickUp.generated.h"

class ADragon;
class UManaComponent;
class UCapsuleComponent;

UCLASS()
class DRAGONCANVAS_API AManaPickUp : public AItemPickUp
{
	GENERATED_BODY()

	


public:	
	// Sets default values for this actor's properties
	AManaPickUp();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float manaToAdd = 50;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ManageOverlap(AActor* _overlapped, AActor* _overlap) override;
	void SetManaToAdd(float _value) { manaToAdd = _value; }

	
};
