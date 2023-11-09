// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
	ownerRef = GetOwner();

	// ...
	
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	deltaSeconds = GetWorld()->DeltaTimeSeconds;
	// ...
}

void UMoveComponent::Move()
{
	FVector _actorForwardVector = ownerRef->GetActorForwardVector();
	FVector _direction = GetOwner()->GetActorLocation() + _actorForwardVector * moveSpeed * deltaSeconds;
	ownerRef->SetActorLocation(_direction);
}

void UMoveComponent::Rotate()
{
}

