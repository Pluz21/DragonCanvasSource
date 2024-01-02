// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "DragonCanvas/Actors/Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	gunMesh = CreateDefaultSubobject<UStaticMeshComponent>("gunMesh");
	gunSubMesh = CreateDefaultSubobject<UStaticMeshComponent>("gunSubMesh");
	
	gunMesh->SetupAttachment(RootComponent);
	gunSubMesh->SetupAttachment(gunMesh);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

