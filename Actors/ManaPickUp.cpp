// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "ManaPickUp.h"
#include "DragonCanvas/Actors//Dragon.h"
#include "DragonCanvas/Components//ManaComponent.h"

#include "Components/CapsuleComponent.h"


// Sets default values
AManaPickUp::AManaPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AManaPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AManaPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();

}


void AManaPickUp::ManageOverlap(AActor* _overlapped, AActor* _overlap)
{
	Super::ManageOverlap(_overlapped, _overlap); 
	
	ADragon* _dragonRef = Cast<ADragon>(_overlap);
	if (!_dragonRef)return;
	_dragonRef->manaCompo->AddMana(manaToAdd);
	
	

}



