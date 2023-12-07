// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UHealthComponent::Init()
{
	currentHealth = maxHealth;
}

void UHealthComponent::AddHealth(int _value)
{
	if (currentHealth <= 0)
	{
		SetIsDead(true);
		return;
	}
	
	currentHealth += _value;
	UE_LOG(LogTemp, Error, TEXT("Current Health = %i"), currentHealth);

	
}

void UHealthComponent::SetIsDead(bool _value)
{

		isDead = _value;
		
		UE_LOG(LogTemp, Error, TEXT("You are dead"));


}

