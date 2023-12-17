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
		AActor* _owner = GetOwner();
		if (!_owner)return false;
		UStaticMeshComponent* _ownerMesh =
			_owner->GetComponentByClass<UStaticMeshComponent>();
		UMaterialInterface* _currentMaterial = _ownerMesh->GetMaterial(0);
		UStaticMeshComponent* _targetMesh = _targetToCheck->
			GetComponentByClass<UStaticMeshComponent>();
		UMaterialInterface* _targetMaterial = _targetMesh->GetMaterial(0);
		if (_targetMaterial != _currentMaterial)
		{
			return false;
		}
		else
		{
			mat = _currentMaterial;
			targetMat = _targetMaterial;
			//projectileManager->AddMaterial(UMaterialInstanceDynamic::Create(_currentMaterial, _ownerMesh));
			return true;
		}}

bool UMaterialCheckerComponent::ActorMaterialCheck(UMaterialInterface* _materialToCheck, AActor*& _targetToCheck)
{
		AActor* _owner = GetOwner();

		if (!_owner)return false;
		UStaticMeshComponent* _ownerMesh =
			_owner->GetComponentByClass<UStaticMeshComponent>();
		//if(UMaterialInterface* _currentMaterial = _ownerMesh->GetMaterial(0))
		//mat = _currentMaterial;
		UMaterialInterface* _currentMaterial = _ownerMesh->GetMaterial(0);
		UStaticMeshComponent* _targetMesh = _targetToCheck->
			GetComponentByClass<UStaticMeshComponent>();
		UMaterialInterface* _targetMaterial = _targetMesh->GetMaterial(0);
		//targetMat = _targetMaterial;
		if (_targetMaterial == _currentMaterial)
		{

			//targetMat = _targetMaterial;
			//mat = _currentMaterial;
			return true;
		}
		else
		{

			//projectileManager->AddMaterial(UMaterialInstanceDynamic::Create(_currentMaterial, _ownerMesh));
			return false;
		}}

bool UMaterialCheckerComponent::MaterialCheck(UMaterialInterface* _materialToCheck)
{
	AActor* _owner = GetOwner();
	if (!_owner)return false;
	UStaticMeshComponent* _ownerMesh =
		_owner->GetComponentByClass<UStaticMeshComponent>();
	//if(UMaterialInterface* _currentMaterial = _ownerMesh->GetMaterial(0))
	//mat = _currentMaterial;
	UMaterialInterface* _currentMaterial = _ownerMesh->GetMaterial(0);
	
	//targetMat = _targetMaterial;
	if (_materialToCheck != _currentMaterial)
	{
		return false;
	}
	else
	{
		return true;

		//mat = _currentMaterial;
		//targetMat = _materialToCheck;
		//projectileManager->AddMaterial(UMaterialInstanceDynamic::Create(_currentMaterial, _ownerMesh));
	}
}


