// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "DragonCanvas/Components/SoundComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
USoundComponent::USoundComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USoundComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USoundComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USoundComponent::PlaySound(USoundBase* _soundToPlay)
{
	if (!_soundToPlay)return;
	UGameplayStatics::PlaySound2D(GetWorld(), _soundToPlay);
}


