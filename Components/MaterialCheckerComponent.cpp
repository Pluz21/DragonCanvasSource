// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "MaterialCheckerComponent.h"
#include "DragonCanvas/Actors/Enemy.h"

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

bool UMaterialCheckerComponent::EnemyMaterialCheck(AEnemy*& _enemyToCheck)
{
	int _size = allMatsToCheck.Num();
	for (int i = 0; i < _size; i++)
	{
		if (_enemyToCheck->GetComponentByClass<UStaticMeshComponent>()->
			GetMaterial(0) == GetAllMatsToCheck()[i])
			return true;
	}
	return false;
}

UMaterialInterface* UMaterialCheckerComponent::FindActorMaterial(AActor*& _actor)
{
	int _size = allMatsToCheck.Num();
	for (int i = 0; i < _size; i++)
	{
		if (_actor->GetComponentByClass<UStaticMeshComponent>()->
			GetMaterial(0) == GetAllMatsToCheck()[i])
		{
			return GetAllMatsToCheck()[i];
		}
	}
	return nullptr;
}

UMaterialInterface* UMaterialCheckerComponent::FindEnemyMaterial(AEnemy*& _enemyToCheck)
{
	int _size = allMatsToCheck.Num();
	for (int i = 0; i < _size; i++)
	{
		UMaterialInterface* CurrentMaterial = _enemyToCheck->GetComponentByClass<UStaticMeshComponent>()->GetMaterial(0);
		UMaterialInterface* TargetMaterial = GetAllMatsToCheck()[i];

		UE_LOG(LogTemp, Warning, TEXT("Comparing materials: %s vs %s"),
			CurrentMaterial ? *CurrentMaterial->GetName() : TEXT("nullptr"),
			TargetMaterial ? *TargetMaterial->GetName() : TEXT("nullptr"));

		if (CurrentMaterial == TargetMaterial)
		{
			UE_LOG(LogTemp, Warning, TEXT("Match found! Material: %s"), *CurrentMaterial->GetName());
			return TargetMaterial;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No matching material found"));
	return nullptr;
}

void UMaterialCheckerComponent::RemoveMaterialAtIndex(int _index)
{
	if(_index >= 0 && _index < allMatsToCheck.Num())
		allMatsToCheck.RemoveAt(_index);
}






