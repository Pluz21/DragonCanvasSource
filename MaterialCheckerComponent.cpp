// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "MaterialCheckerComponent.h"
#include "DragonCanvas/Actors/ProjectileManager.h"

// Sets default values for this component's properties
UMaterialCheckerComponent::UMaterialCheckerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMaterialCheckerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMaterialCheckerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


bool UMaterialCheckerComponent::ActorMaterialCheck(AActor*& _targetToCheck)
{
	int _size = allMatsToCheck.Num();
	for (int i = 0; i < _size; i++)
	{
		if (_targetToCheck->GetComponentByClass<UStaticMeshComponent>()->
			GetMaterial(0) == GetAllMatsToCheck()[i])
			return true;
	}
		return false;
}




