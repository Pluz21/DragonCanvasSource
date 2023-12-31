// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "DragonCanvas/Components/HiddenComponent.h"

// Sets default values for this component's properties
UHiddenComponent::UHiddenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHiddenComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
	// ...
	
}


// Called every frame
void UHiddenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHiddenComponent::Init()
{
	if (!GetOwner() || GetOwner()->GetComponentByClass<UStaticMeshComponent>() == nullptr)return;
	GetOwner()->GetComponentByClass<UStaticMeshComponent>()->SetVisibility(false, true);
	UE_LOG(LogTemp, Warning, TEXT("called init inside HIDDEN ACTOR"));
	GetOwner()->GetComponentByClass<UStaticMeshComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

