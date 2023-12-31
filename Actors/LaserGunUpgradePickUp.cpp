// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "DragonCanvas/Actors/LaserGunUpgradePickUp.h"
#include "Dragon.h"

// Sets default values
ALaserGunUpgradePickUp::ALaserGunUpgradePickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALaserGunUpgradePickUp::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALaserGunUpgradePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALaserGunUpgradePickUp::TriggerPlayerGunSwap()
{
	UE_LOG(LogTemp, Warning, TEXT("GunSwap triggered"));

	APawn* _pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!_pawn)return;

	ADragon* _player = Cast<ADragon>(_pawn);
	_player->AttachGun(_player->laserGunRef, _player->gunSpawnPoint);
}

void ALaserGunUpgradePickUp::ItemAction()
{
	TriggerPlayerGunSwap();
}



