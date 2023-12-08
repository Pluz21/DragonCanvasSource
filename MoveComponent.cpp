//Copyright © 2023 Pluz21(TVL).All rights reserved.

#include "MoveComponent.h"
#include "Dragon.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


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
	Init();

	// ...
	
}


void UMoveComponent::Init()
{
	ownerRef = GetOwner();
	if(!ownerRef)
		UE_LOG(LogTemp, Warning, TEXT("No owner found"));

	if (playerRef = Cast<ADragon>(GetWorld()->
		GetFirstPlayerController()->GetCharacter()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast succeeded to get player in movecomp"));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cast failed to get player in movecomp"));

	}

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
	if (!ownerRef)return;
	ownerRef->SetActorLocation(_direction);
	
}

void UMoveComponent::SelfMove(const FVector& _actorForwardVector)
{
	FVector _direction = GetOwner()->GetActorLocation() + _actorForwardVector * moveSpeed * deltaSeconds;
	GetOwner()->SetActorLocation(_direction);
	//OnCanMove.Broadcast();
}

void UMoveComponent::ChasePlayer()
{
	if (!playerRef || !ownerRef)
	{
		return;
	}
	FVector _direction = playerRef->GetActorLocation() - ownerRef->GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("Direction from Enemy is : %s"), *_direction.ToString());
	FVector _normalizedDirection = _direction.GetSafeNormal();
	FRotator _newRotate = _normalizedDirection.Rotation();
	FVector _targetLocation = ownerRef->GetActorLocation() + _direction * chaseSpeed * GetWorld()->DeltaTimeSeconds;
	ownerRef->SetActorRotation(_newRotate);
	ownerRef->SetActorLocation(_targetLocation);

		// UKismetMathLibrary::MakeRotFromXZ(_direction, FVector::UpVector);
	
}

void UMoveComponent::Rotate()
{
	float _speed = rotateSpeed * deltaSeconds;
	FRotator _newRotation = ownerRef->GetActorRotation() + FRotator(0, _speed, 0);
	ownerRef->SetActorRotation(_newRotation);
}

