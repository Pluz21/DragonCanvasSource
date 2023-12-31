// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "DragonCanvas/Components/UpgradeComponent.h"

// Sets default values for this component's properties
UUpgradeComponent::UUpgradeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}


void UUpgradeComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}


void UUpgradeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UUpgradeComponent::SetHasJumpUpgrade(bool _value)
{
	hasJumpUpgrade = _value;
	onJumpUpgradeAcquired.Broadcast(_value);
}

