// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "MudSpawner.h"

// Sets default values
AMudSpawner::AMudSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMudSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMudSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

