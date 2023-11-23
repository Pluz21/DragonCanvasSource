// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "Dragon.h"
#include "Projectile.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("MoveConstructor Constructor!"));


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

void UMoveComponent::MoveAndFollow()
{
	
	FVector _actorForwardVector = GetOwner()->GetActorForwardVector();
	FVector _direction = GetOwner()->GetActorLocation() + _actorForwardVector * moveSpeed * deltaSeconds;
	ownerRef->SetActorLocation(_direction);
	
}

void UMoveComponent::SelfMove(const FVector& _actorForwardVector)
{
	FVector Direction = GetOwner()->GetActorLocation() + _actorForwardVector * moveSpeed * deltaSeconds;
	GetOwner()->SetActorLocation(Direction);
	//OnCanMove.Broadcast();
}

void UMoveComponent::Rotate()
{
	float _speed = rotateSpeed * deltaSeconds;
	FRotator _newRotation = ownerRef->GetActorRotation() + FRotator(0, _speed, 0);
	ownerRef->SetActorRotation(_newRotation);
}

