// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "MoveComponent.h"
#include "Dragon.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>("root");
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>("baseMesh");
	secondMesh = CreateDefaultSubobject<UStaticMeshComponent>("secondMesh");
	moveCompo = CreateDefaultSubobject<UMoveComponent>("moveCompo");
	baseMesh->SetupAttachment(root);
	secondMesh->SetupAttachment(baseMesh);
	AddOwnedComponent(moveCompo);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Init();
}



void AEnemy::Init()
{
	SetLifeSpan(20);
	playerRef = moveCompo->GetChaseTarget();
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!moveCompo)return;
	moveCompo->ChasePlayer();
	SelfDestroy();

}

bool AEnemy::CheckDistance()
{
	if (!playerRef)return false;
	float _distance = FVector::Dist(playerRef->GetActorLocation(), GetActorLocation());
	if(_distance < minDistanceAllowed)
		return true;
	return false;
}

void AEnemy::SelfDestroy()
{
	if (CheckDistance())
	{
		Destroy();
		UE_LOG(LogTemp, Warning, TEXT("You got hit by a Flamito!"));

	}
	// TO DO 
	// Add explosion effect
	// Add health loss to player
}



