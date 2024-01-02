// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "DragonCanvas/Actors/ProjectileBossEnemy.h"

#include "DragonCanvas/Actors/Dragon.h"
#include "DragonCanvas/Actors/ProjectileManager.h"

#include "DragonCanvas/Components/HealthComponent.h"

#include "ProjectileBossEnemy.h"

AProjectileBossEnemy::AProjectileBossEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AProjectileBossEnemy::BeginPlay()
{
	Super::BeginPlay();
	onPlayerHit.AddDynamic(this, &AProjectileBossEnemy::HandlePlayerHit);

	
}

void AProjectileBossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBossEnemy::CheckDistanceToPlayer()
{
	if (!GetWorld()->GetFirstPlayerController()) return;
	ADragon* _playerRef = Cast<ADragon>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!_playerRef) return;
	FVector _playerLocation = _playerRef->GetActorLocation();
	float _distance = FVector::Dist(GetActorLocation(), _playerLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Distance to player %f"), _distance);

	if (_distance <= minDistanceToHitPlayer)
	{
		onPlayerHit.Broadcast(_playerRef);
		projectileManager->RemoveItem(this);
		SelfDestruct();
	}
}


void AProjectileBossEnemy::HandlePlayerHit(ADragon* _playerRef)
{

	if (!_playerRef)return;
	_playerRef->healthCompo->RemoveHealth(damage);
	UE_LOG(LogTemp, Warning, TEXT("Finished event handleplayer"));
}
