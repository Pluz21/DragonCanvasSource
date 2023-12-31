// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "DragonCanvas/Components/RevealHiddenComponent.h"
#include "DragonCanvas/Actors/HiddenActors.h"
#include "RevealHiddenComponent.h"

// Sets default values for this component's properties
URevealHiddenComponent::URevealHiddenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URevealHiddenComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
}


// Called every frame
void URevealHiddenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URevealHiddenComponent::Init()
{
	onConditionToRevealIsMet.AddDynamic(this, &URevealHiddenComponent::RevealHidden);
}

void URevealHiddenComponent::RevealHidden()
{
	int _size = allHiddenActors.Num();
	for (int i = 0; i < _size; i++)
	{
		if (allHiddenActors[i] == nullptr)return;
		allHiddenActors[i]->GetComponentByClass<UStaticMeshComponent>()->
			SetVisibility(true, true);

	}
	
}

