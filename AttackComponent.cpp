// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "Projectile.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttackComponent::Attack()
{
}

AProjectile* UAttackComponent::SpawnProjectile(const FVector& _spawnLocation,AActor* _owner)
{
	
	AProjectile* _spawned = GetWorld()->SpawnActor<AProjectile>(projectileRef,  _spawnLocation, FRotator::ZeroRotator);
	if (_spawned && _owner)
	{
		_spawned->SetOwner(_owner);
		UE_LOG(LogTemp, Warning, TEXT("Spawned Projectile Owner: %s"), *_owner->GetName());

	}
	return _spawned;
}

