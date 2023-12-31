// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "HiddenActors.h"

// Sets default values
AHiddenActors::AHiddenActors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("mymesh");
	meshCompo->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHiddenActors::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

// Called every frame
void AHiddenActors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHiddenActors::Init()
{
	meshCompo->SetVisibility(false,true);
	UE_LOG(LogTemp, Warning, TEXT("called init inside HIDDEN ACTOR"));
	meshCompo->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

