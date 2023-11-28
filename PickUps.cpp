// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUps.h"

// Sets default values
APickUps::APickUps()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("meshCompo");
	meshCompo->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickUps::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UPrimitiveComponent* _compo = GetComponentByClass<UPrimitiveComponent>();
	//_compo->SetSimulatePhysics(true);
}

