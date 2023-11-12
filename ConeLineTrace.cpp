// Fill out your copyright notice in the Description page of Project Settings.


#include "ConeLineTrace.h"
#include "Kismet/KismetSystemLibrary.h"
#include <DrawDebugHelpers.h>


// Sets default values
UConeLineTrace::UConeLineTrace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void UConeLineTrace::BeginPlay()
{
	Super::BeginPlay();
	ownerRef = GetOwner();
	
}

// Called every frame
void UConeLineTrace::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UConeLineTrace::ConeTrace()
{
	if (!ownerRef) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find owner"));
	}
	FVector _endLocation = ownerRef->GetActorLocation() + ownerRef->GetActorForwardVector() * distance;
	TArray<FHitResult> _hits;
	FQuat _quat = FQuat(ownerRef->GetActorRotation());

	GetWorld()->SweepMultiByChannel(_hits, ownerRef->GetActorLocation(),
		_endLocation, _quat,
		_coneTraceChannel, FCollisionShape::MakeSphere(coneTraceRadius));

	DrawDebugSphere(GetWorld(), ownerRef->GetActorLocation(),
		coneTraceRadius, 12, FColor::Magenta, true, -1, 0, 3);
}


