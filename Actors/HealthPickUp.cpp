// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "HealthPickUp.h"
#include "DragonCanvas/Actors/Dragon.h"
#include "DragonCanvas/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AHealthPickUp::AHealthPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHealthPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
}

void AHealthPickUp::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	Super::ManageOverlap(_overlapped, _overlap);

	ADragon* _dragonRef = Cast<ADragon>(_overlap);
	if (!_dragonRef)return;
	_dragonRef->healthCompo->AddHealth(healthToAdd);
}



