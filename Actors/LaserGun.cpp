// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "LaserGun.h"

// Sets default values
ALaserGun::ALaserGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALaserGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaserGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALaserGun::Rotate(UStaticMeshComponent* _meshToRotate)
{
	return;
	// Avoid rotation since there are childs of the materialChanger mesh
}

