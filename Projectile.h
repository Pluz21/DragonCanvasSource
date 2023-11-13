// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UConeLineTrace;
class UMoveComponent;

UCLASS()
class DRAGONCANVAS_API AProjectile : public AActor
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTargetReached);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FProjectileCreated);

	UPROPERTY(EditAnywhere)
	FTargetReached onTargetReached;

	UPROPERTY(EditAnywhere)
	FProjectileCreated onProjectileCreated;
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> meshCompo;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMoveComponent> moveCompo;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UConeLineTrace> coneLineTraceCompo;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> ownerRef;

	UPROPERTY(VisibleAnywhere)
	UWorld* myWorld;
	UPROPERTY(VisibleAnywhere)
	float deltaSeconds;
	
	UPROPERTY(VisibleAnywhere)
	float lifeSpan = 2;
	UPROPERTY(VisibleAnywhere)
	float moveSpeed;
	UPROPERTY(VisibleAnywhere)
	bool canMove = false;
	UPROPERTY(VisibleAnywhere)
	FVector forwardVector = FVector(0);
	UPROPERTY(EditAnywhere)
	FVector targetLocation = FVector(0);
	UPROPERTY(VisibleAnywhere)
	FVector actorSpawnLocation = FVector(0);

	UPROPERTY(EditAnywhere)
	float distanceToSelfDestruct = 1000;
	UPROPERTY(EditAnywhere)
	float targetDistanceMultiplier = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SelfMove(const FVector& _actorForwardVector);
	void SetCanMove(bool _value);
	void SetForwardVector(const FVector& _ownerVector) { forwardVector = _ownerVector; }
	//void SetTargetLocation(const FVector& _targetLocation) { targetLocation = _targetLocation; }
	UMoveComponent* GetMoveCompo() { return moveCompo; }

	void CheckDistance();
	UFUNCTION() void SelfDestruct();


};
