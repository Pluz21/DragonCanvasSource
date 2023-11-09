// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UMoveComponent;
UCLASS()
class DRAGONCANVAS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> meshCompo;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMoveComponent> moveCompo;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> ownerRef;

	UPROPERTY(VisibleAnywhere)
	UWorld* myWorld;
	UPROPERTY(VisibleAnywhere)
	float deltaSeconds;
	
	UPROPERTY(VisibleAnywhere)
	float lifeSpan = 2;
	UPROPERTY(VisibleAnywhere)
	float moveSpeed = 2000;
	UPROPERTY(VisibleAnywhere)
	bool canMove = false;
	UPROPERTY(VisibleAnywhere)
	FVector forwardVector = FVector(0);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GetInitialForwardVector();

	void SelfMove(const FVector& _actorForwardVector);
	void SetCanMove(bool _value);
	void SetForwardVector(const FVector& _ownerVector) { forwardVector = _ownerVector; }

};
