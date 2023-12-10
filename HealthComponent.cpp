//Copyright © 2023 Pluz21(TVL).All rights reserved.

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
	SetHealthColor();
}

void UHealthComponent::AddHealth(int _value)
{
	if (currentHealth <= 0)
	{
		SetHealthColor();   // has to be called in other places too.
		SetIsDead(true);
		

		// To Do : Add Death Menu
		return;
	}
	currentHealth += _value;
	SetHealthColor();
	UE_LOG(LogTemp, Error, TEXT("Current Health = %i"), currentHealth);

	
}

void UHealthComponent::SetIsDead(bool _value)
{

		isDead = _value;
		
		UE_LOG(LogTemp, Error, TEXT("You are dead"));


}

void UHealthComponent::SetHealthColor()
{

	if (currentHealth == maxHealth)
	{
		UE_LOG(LogTemp, Error, TEXT("Called HealthColor INIT"));

		currentColor = highHealthColor;
	}
	float maxHealthFraction = 1.2f;
	float midHealthFraction = 1.9f;
	float lowHealthFraction = 3.5f;

	float maxHealthThreshHold = maxHealth / maxHealthFraction;
	float midHealthThreshHold = maxHealth / midHealthFraction;
	float lowHealthThreshHold = maxHealth / lowHealthFraction;
	UE_LOG(LogTemp, Error, TEXT("MaxHealththreshold = %f"), maxHealthThreshHold);
	UE_LOG(LogTemp, Error, TEXT("MidHealththreshold = %f"), midHealthThreshHold);
	UE_LOG(LogTemp, Error, TEXT("LowHealththreshold = %f"), lowHealthThreshHold);

	if (currentHealth > maxHealthThreshHold)
		currentColor = highHealthColor;

	if (currentHealth > midHealthThreshHold && currentHealth < maxHealthThreshHold)
		currentColor = midHealthColor;
	
	if (currentHealth > lowHealthThreshHold && currentHealth < midHealthThreshHold)
		currentColor = lowHealthColor;
}



