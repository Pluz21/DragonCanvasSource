// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Dragon.h"
#include "MoveComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("mymesh");
	meshCompo->SetupAttachment(RootComponent);
	moveCompo = CreateDefaultSubobject<UMoveComponent>("moveCompo");
	AddOwnedComponent(moveCompo);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(lifeSpan);

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	deltaSeconds = GetWorld()->DeltaTimeSeconds;
	//ADragon* _dragonOwner = Cast<ADragon>(ownerRef);
	SelfMove(forwardVector);
	//moveCompo->Move();

}

void AProjectile::SelfMove(const FVector& _actorForwardVector)
{
	if (canMove)
	{

	//FVector _actorForwardVector = GetOwner()->GetActorForwardVector();
	FVector _direction = GetActorLocation() + _actorForwardVector * moveSpeed * deltaSeconds;
	SetActorLocation(_direction);
	}
}

void AProjectile::SetCanMove(bool _value)
{
	canMove = _value;
}



