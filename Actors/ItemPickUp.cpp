// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "DragonCanvas/Actors/ItemPickUp.h"
#include "DragonCanvas/Actors//Dragon.h"
#include "Kismet/GameplayStatics.h"




// Sets default values
AItemPickUp::AItemPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void AItemPickUp::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
}

// Called every frame
void AItemPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
	UpdateCurrentLocation();
	Move();
}

void AItemPickUp::Init()
{
	OnActorBeginOverlap.AddDynamic(this, &AItemPickUp::ManageOverlap);
	randFloat = FMath::RandRange(0.5f, 2.f);
	GetInitialLocation();
	currentLocation = initialLocation;
	targetLocation = initialLocation + FVector(0, 0, 50);

}

void AItemPickUp::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{

	if (!_overlapped || !_overlap)return;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), pickUpSound,GetActorLocation());
	_overlapped->Destroy();

}

void AItemPickUp::Rotate()
{
	if (!canRotate) return;


	float _rotateValue = rotateSpeed * GetWorld()->DeltaTimeSeconds * randFloat;
	FRotator _currentRotation = GetActorRotation();
	FRotator _newRotation = FRotator(0, _rotateValue, 0);

	if (randFloat < 1.2f)
	{
		_newRotation *= -1;
	}

	SetActorRotation(_currentRotation + _newRotation);
}

void AItemPickUp::Move()
{
	DistanceCheck();
	float _speed = moveSpeed * randFloat * GetWorld()->DeltaTimeSeconds;
	FVector _moveDir = (targetLocation - currentLocation).GetSafeNormal();
	FVector _newLocation = GetActorLocation() + _moveDir * _speed;
	SetActorLocation(_newLocation);

}

void AItemPickUp::DistanceCheck()
{
	float _distance = FVector::Dist(initialLocation, currentLocation);
	if (_distance >= maxDistanceToTravel)
	{
		FVector _newTargetLocation = initialLocation;
		initialLocation = currentLocation;
		targetLocation = _newTargetLocation;
	}

	//if (_distance <= maxDistanceToTravel)
		//UE_LOG(LogTemp, Warning, TEXT("NOT REACHED"));
}





