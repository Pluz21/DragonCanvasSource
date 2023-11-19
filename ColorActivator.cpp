// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorActivator.h"

// Sets default values
AColorActivator::AColorActivator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	meshCompo = CreateDefaultSubobject<UStaticMeshComponent>("meshCompo");

	meshCompo->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AColorActivator::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AColorActivator::ManageOverlap);
	
}

// Called every frame
void AColorActivator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColorActivator::ManageOverlap(AActor* _overlap, AActor* _overlapped)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapping"));

}

