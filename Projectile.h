// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class AProjectileManager;
class ACustomGameMode;
class ADragon;
class UMoveComponent;
UCLASS()
class DRAGONCANVAS_API AProjectile : public AActor
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTargetReached);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTargetAcquired);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FProjectileCreated);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCanStartMoving);

	UPROPERTY(EditAnywhere)
	FCanStartMoving onCanMove;

	UPROPERTY(EditAnywhere)
	FTargetAcquired onTargetAcquired;

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
	TObjectPtr<ACustomGameMode> gameMode;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AProjectileManager> projectileManager;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMoveComponent> moveCompo;
	//UPROPERTY()
	//TObjectPtr<UConeLineTrace> coneLineTraceCompo;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> ownerRef;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ADragon> dragonRef;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> playerRef;


	UPROPERTY(VisibleAnywhere)
	UWorld* myWorld;
	UPROPERTY(VisibleAnywhere)
	float deltaSeconds;
	
	UPROPERTY(VisibleAnywhere)
	float lifeSpan = 5;
	UPROPERTY(VisibleAnywhere)
	float moveSpeed;
	UPROPERTY(VisibleAnywhere)
	bool canMove = false;
	UPROPERTY(VisibleAnywhere)
	bool canActivateLineTraceEffect = false;
	UPROPERTY(VisibleAnywhere)
	float launchTime;
	UPROPERTY(VisibleAnywhere)
	FVector forwardVector = FVector(0);
	UPROPERTY(EditAnywhere)
	FVector targetLocation = FVector(0);
	UPROPERTY(VisibleAnywhere)
	FVector actorSpawnLocation = FVector(0);

	UPROPERTY(EditAnywhere)
	float maxDistance = 100000;
	
	UPROPERTY(EditAnywhere)
	float lineTraceDistance;
	UPROPERTY(EditAnywhere)
	float minDistanceToSelfDestruct = 150; // equal to radius of our linetrace/2
	
	UPROPERTY(EditAnywhere)
	float targetDistanceMultiplier = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init();
	UFUNCTION()
	void ManageOverlap(AActor* _overlapped, AActor* _overlap);
	void SelfMove(const FVector& _actorForwardVector);
	void SetCanMove(bool _value);
	void SetForwardVector(const FVector& _ownerVector) { forwardVector = _ownerVector; }
	void SetTargetLocation(const FVector& _newTargetLocation) { targetLocation = _newTargetLocation; }
	//void SetTargetLocation(const FVector& _targetLocation) { targetLocation = _targetLocation; }
	UMoveComponent* GetMoveCompo() { return moveCompo; }
	FVector GetInitialLocation() { return actorSpawnLocation; }
	float GetLaunchTime() { return launchTime; }

	UFUNCTION() void SetLaunchTime() {launchTime = GetWorld()->GetTimeSeconds();}
	UFUNCTION() void CheckTravelledDistance(const float& _maxDistance);
	UFUNCTION() void SetMaxDistance(const float& _maxDistance) { maxDistance = _maxDistance; }
	UFUNCTION() void FindEndLocation();
	UFUNCTION() void CheckDistance(FVector& _targetLocation);
	UFUNCTION() void CallLineTraceDisplacement();

	


	UFUNCTION() void SelfDestruct();

};
