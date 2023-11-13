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
	FVector _startLocation = ownerRef->GetActorLocation();
	FVector _endLocation = ownerRef->GetActorLocation() + ownerRef->GetActorForwardVector() * distance;
	lineTraceEnd = _endLocation;
	FCollisionQueryParams _ignoreSelfParam;     
	_ignoreSelfParam.AddIgnoredActor(ownerRef);

	TArray<FHitResult> _allHits;
	FQuat _quat = FQuat(ownerRef->GetActorRotation());

	bool _hit = GetWorld()->SweepMultiByChannel(_allHits, _startLocation,
		_endLocation, _quat, 
		_coneTraceChannel, FCollisionShape::MakeSphere(coneTraceRadius),
		_ignoreSelfParam);
	if (_hit)
	{
		for (int i = 0; i < _allHits.Num(); i++)

		{
			UE_LOG(LogTemp, Warning, TEXT("The FireBreath hit: %s"), *_allHits[i].GetActor()->GetName());

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nothing hit by FireBreath")); 

	}

	DrawDebugSphere(GetWorld(), _endLocation,
		coneTraceRadius + distance, 25, FColor::Orange, false, -1, 0, 3);
}


