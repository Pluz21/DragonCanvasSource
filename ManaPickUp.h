// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ManaPickUp.generated.h"

class ADragon;
class UManaComponent;
class UCapsuleComponent;

UCLASS()
class DRAGONCANVAS_API AManaPickUp : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> meshCompo;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCapsuleComponent> capsuleCollider;

public:	
	// Sets default values for this actor's properties
	AManaPickUp();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float manaToAdd = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool canRotate = true;
	float rotateSpeed = 60;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init();
	UFUNCTION()
	void ManageOverlap(AActor* _overlapped, AActor* _overlap);
	void SetManaToAdd(float _value) { manaToAdd = _value; }

	void Rotate();
};
