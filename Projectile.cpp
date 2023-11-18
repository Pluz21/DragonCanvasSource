// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Dragon.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "MoveComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("Projectile Constructor!"));

	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("mymesh");
	meshCompo->SetupAttachment(RootComponent);
	moveCompo = CreateDefaultSubobject<UMoveComponent>("moveCompo");
	//coneLineTraceCompo = CreateDefaultSubobject<UConeLineTrace>("coneTraceCompohere");
	AddOwnedComponent(moveCompo);
	//AddOwnedComponent(coneLineTraceCompo);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ADragon* _dragonRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
	_dragonRef->GetOnProjectileReachedTarget().AddDynamic(_dragonRef, &ADragon::StartLineTraceAction);
	onCanMove.AddDynamic(this, &AProjectile::FindEndLocation);
	onTargetAcquired.AddDynamic(this, &AProjectile::SetCanCheckDistance);
	onTargetReached.AddDynamic(this, &AProjectile::SelfDestruct);
	actorSpawnLocation = GetActorLocation();
	//SetLifeSpan(lifeSpan);
	moveSpeed = moveCompo->GetMoveSpeed(); // MoveSpeed will always be set through the component

}

void AProjectile::CheckIfHit()
{
	/*if (coneLineTraceCompo->GetCanSelfDestruct())
	{
		UE_LOG(LogTemp, Warning, TEXT("CanSelfDestruct!"));
		onTargetReached.Broadcast();
	}*/
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaSeconds = GetWorld()->DeltaTimeSeconds;
	CheckDistance(targetLocation);
	SelfMove(forwardVector);
	moveCompo->Rotate();
	CheckTravelledDistance(maxDistance);
	//SetCanActivateLineTraceEffect();
	// or call 
	//moveCompo->Move();

}

void AProjectile::SelfMove(const FVector& _actorForwardVector)
{
	if (canMove)
	{
	moveCompo->SelfMove(forwardVector);
	onCanMove.Broadcast();
	}

	/*if (canMove)
	{

	FVector _direction = GetActorLocation() + _actorForwardVector * moveSpeed * deltaSeconds;
	SetActorLocation(_direction);
	onCanMove.Broadcast();
	}*/
}

void AProjectile::SetCanMove(bool _value)
{
	canMove = _value;
}

void AProjectile::SelfDestruct()
{
	Destroy();
	ADragon* _dragonRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
	TArray<AProjectile*> _allProjectilesToRemove = _dragonRef->GetAllProjectiles();
	float _size = _allProjectilesToRemove.Num();
	if (_size > 0)
	{
		for (int i = 0; i < _size; i++)
	{
		_allProjectilesToRemove.RemoveAt(_allProjectilesToRemove.Num() - 1);
		

	}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("DESTRUCTION"));

}

void AProjectile::CheckTravelledDistance(const float& _maxDistance)
{

	FVector _currentLocation = GetActorLocation();
	float travelledDistance = FVector::Dist(_currentLocation, actorSpawnLocation);
	//UE_LOG(LogTemp, Warning, TEXT("TRAVELLED %f CM"), travelledDistance);

	if (travelledDistance > _maxDistance)
	{
		canActivateLineTraceEffect = true;
		UE_LOG(LogTemp, Warning, TEXT("canActivateLineTraceEffect TRUE"));
		ADragon* _dragonRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
		_dragonRef->GetOnProjectileReachedTarget().Broadcast();
		
	}
	canActivateLineTraceEffect = false;
}

void AProjectile::SetCanActivateLineTraceEffect()
{
	/*if (CheckTravelledDistance(true))
	{

		canActivateLineTraceEffect = true;
		UE_LOG(LogTemp, Warning, TEXT("CANACTIVATECALLED"));
	}*/
}

void AProjectile::FindEndLocation()
{
	ADragon* _dragonRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
	//targetLocation = _dragonRef->GetProjectileTargetLocation();
	lineTraceDistance = _dragonRef->GetSphereTraceDistance();
	minDistanceToSelfDestruct = _dragonRef->GetMinDistanceToSelfDestruct();
	//UE_LOG(LogTemp, Warning, TEXT("targetlocaiton is %s"), *targetLocation.ToString());
	onTargetAcquired.Broadcast();

}

void AProjectile::CheckDistance(FVector& _targetLocation)
{
	if (hasTarget) 
	{

	float _distanceToLineTraceEndLocation = FVector::Dist(GetActorLocation(), _targetLocation);
	//UE_LOG(LogTemp, Warning, TEXT("targetLocation : %s"), *targetLocation.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("distance : %f"), _distanceToLineTraceEndLocation);
	//UE_LOG(LogTemp, Error, TEXT("lineTraceDistance : %f"), lineTraceDistance);
	if (_distanceToLineTraceEndLocation <= minDistanceToSelfDestruct)
		onTargetReached.Broadcast(); // Calling destruct
	}
}



