// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "MaterialCheckerComponent.h"
#include "DragonCanvas/Actors/ProjectileManager.h"

// Sets default values for this component's properties
UMaterialCheckerComponent::UMaterialCheckerComponent()
{

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




