// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorActivatorProjectile.h"
#include "ColorActivator.h"

// Sets default values
AColorActivatorProjectile::AColorActivatorProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AColorActivatorProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AColorActivatorProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColorActivatorProjectile::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	//Super::ManageOverlap(_overlapped, _overlap);
	if (!_overlap || !_overlapped) return;
	GiveColor();
}


