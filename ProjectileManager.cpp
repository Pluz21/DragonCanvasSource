//Copyright © 2023 Pluz21(TVL).All rights reserved.

#include "ProjectileManager.h"
#include "Projectile.h"

// Sets default values
AProjectileManager::AProjectileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProjectileManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// PROJECTILES

void AProjectileManager::AddItem(TObjectPtr<AProjectile> _item)
{
	if (!_item || Exists(_item))return; // check if item is !valid and if he has already been added to array

	allProjectiles.Add(_item);
}

void AProjectileManager::RemoveItem(TObjectPtr<AProjectile> _item)
{
	if (!Exists(_item))return; //check if item exists in array.
	allProjectiles.Remove(_item);
}

TObjectPtr<AProjectile> AProjectileManager::GetItem(const int& _index)
{
	int _size = allProjectiles.Num();
	//	if (_size < 1 && _index < 0 && _index >= _size)return nullptr; // check if array not empty, check if the index is not nul,then check if the index is inferior to array length.
	if (_size >= 0 && _index >= 0 && _index < _size) // check if array not empty, check if the index is not nul,then check if the index is inferior to array length.
		return allProjectiles[_index];						// all the checks are to avoid out of bounds.
	return nullptr;						// all the checks are to avoid out of bounds.

}

bool AProjectileManager::Exists(TObjectPtr<AProjectile> _item)
{
	int _size = allProjectiles.Num();
	for (int i = 0; i < _size; i++)
	{
		AProjectile* _projectile = allProjectiles[i];
		if (!_projectile)continue;
		if (_projectile == _item)
			return true;
	}
	return false;
}

bool AProjectileManager::Exists(const int& _index)
{
	int _size = allProjectiles.Num();
	if (_index < 0 || _index >= _size)return false; // check out of the bounds of array
	AProjectile* _projectile = allProjectiles[_index];
	if (!_projectile)return false;
	return true;
}

// MATS 

void AProjectileManager::AddMaterial(TObjectPtr<UMaterialInstance> _mat)
{
	//exists check
	allCollectedMats.Add(_mat);
}

void AProjectileManager::RemoveMaterial(TObjectPtr<UMaterialInstance> _mat)
{
	//exists check
	allCollectedMats.Remove(_mat);


}

bool AProjectileManager::MatExists(TObjectPtr<UMaterialInstance> _mat)
{
	int _size = allCollectedMats.Num();
	for (int i = 0; i < _size; i++)
	{
		UMaterialInstance* _matInstance = allCollectedMats[i];
		if (!_matInstance)continue;
		if (_matInstance == _mat)
			return true;
	}
	return false;
}

bool AProjectileManager::MatExists(const int& _index)
{
	int _size = allCollectedMats.Num();
	if (_index < 0 || _index >= _size)return false; // check out of the bounds of array
	UMaterialInstance* _matInstance = allCollectedMats[_index];
	if (!_matInstance)return false;
	return true;
}

TObjectPtr<UMaterialInstance> AProjectileManager::GetMaterialInstance(const int& _index)
{
	int _size = allCollectedMats.Num();
	if (_size >= 0 && _index >= 0 && _index < _size) 
		return allCollectedMats[_index];					
	return nullptr;
}







