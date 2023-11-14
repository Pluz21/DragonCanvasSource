// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Dragon.h"

#include "MoveComponent.h"
#include "ConeLineTrace.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("Projectile Constructor!"));

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
	//SetOwner(GetOwner());
	onTargetReached.AddDynamic(this, &AProjectile::SelfDestruct);
	targetLocation = GetActorLocation() + (GetActorForwardVector() * targetDistanceMultiplier);
	SetLifeSpan(lifeSpan);
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
	//CheckDistance(targetLocation);
	//CheckIfHit();
	deltaSeconds = GetWorld()->DeltaTimeSeconds;
	SelfMove(forwardVector);
	moveCompo->Rotate();
	// or call 
	//moveCompo->Move();

}

void AProjectile::SelfMove(const FVector& _actorForwardVector)
{
	if (canMove)
	{

	FVector _direction = GetActorLocation() + _actorForwardVector * moveSpeed * deltaSeconds;
	SetActorLocation(_direction);
	}
}

void AProjectile::SetCanMove(bool _value)
{
	canMove = _value;
}

void AProjectile::SelfDestruct()
{
	Destroy();
	
	UE_LOG(LogTemp, Warning, TEXT("DESTRUCTION"));

}

void AProjectile::CheckDistance(FVector& _targetLocation)
{
	float _distanceToLineTraceEnd = FVector::Dist(GetActorLocation(), _targetLocation);
	/*UE_LOG(LogTemp, Warning, TEXT("targetLocation : %s"), *targetLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("distance : %f"), _distanceToLineTraceEnd);*/
	if (distanceToSelfDestruct < _distanceToLineTraceEnd)
		onTargetReached.Broadcast();
}



