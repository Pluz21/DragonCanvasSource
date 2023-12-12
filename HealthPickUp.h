// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPickUp.generated.h"

class ADragon;
class UHealthComponent;
class UCapsuleComponent;

UCLASS()
class DRAGONCANVAS_API AHealthPickUp : public AActor
{
	GENERATED_BODY()	

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> meshCompo;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCapsuleComponent> capsuleCollider;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float healthToAdd = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool canRotate = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float rotateSpeed = 60;

public:
	// Sets default values for this actor's properties
	AHealthPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init();
	UFUNCTION()
	void ManageOverlap(AActor* _overlapped, AActor* _overlap);


	void Rotate();
};
