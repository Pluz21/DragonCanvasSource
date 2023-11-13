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
	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("mymesh");
	meshCompo->SetupAttachment(RootComponent);
	moveCompo = CreateDefaultSubobject<UMoveComponent>("moveCompo");
	coneLineTraceCompo = CreateDefaultSubobject<UConeLineTrace>("coneTraceCompo");
	AddOwnedComponent(moveCompo);
	AddOwnedComponent(coneLineTraceCompo);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	onTargetReached.AddDynamic(this, &AProjectile::SelfDestruct);
	actorSpawnLocation = GetActorLocation();
	SetLifeSpan(lifeSpan);
	moveSpeed = moveCompo->GetMoveSpeed(); // MoveSpeed will always be set through the component
	endLocation = coneLineTraceCompo->GetLineTraceEnd();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckDistance();
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
}

void AProjectile::CheckDistance()
{
	//FVector targetLocation = coneLineTraceCompo->GetLineTraceEnd();
	float _distanceToLineTraceEnd = FVector::Dist(actorSpawnLocation, endLocation);
	UE_LOG(LogTemp, Warning, TEXT("distanceToTarget : %f"), _distanceToLineTraceEnd);
	UE_LOG(LogTemp, Warning, TEXT("actorspawnLocation : %f"), *actorSpawnLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("endLocation : %f"), *endLocation.ToString());
	if (_distanceToLineTraceEnd <= 100)
		onTargetReached.Broadcast();
}



