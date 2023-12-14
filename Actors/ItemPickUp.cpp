// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "DragonCanvas/Actors/ItemPickUp.h"
#include "DragonCanvas/Components/SoundComponent.h"

// Sets default values
AItemPickUp::AItemPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	soundCompo = CreateDefaultSubobject<USoundComponent>("SoundCompo");


}

// Called when the game starts or when spawned
void AItemPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

