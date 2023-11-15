// Fill out your copyright notice in the Description page of Project Settings.


#include "ConeLineTrace.h"
#include "Kismet/KismetSystemLibrary.h"
#include <DrawDebugHelpers.h>


// Sets default values
UConeLineTrace::UConeLineTrace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
<<<<<<< Updated upstream
=======
	//UE_LOG(LogTemp, Warning, TEXT("ConeLineTrace Constructor!"));
>>>>>>> Stashed changes

}

// Called when the game starts or when spawned
void UConeLineTrace::BeginPlay()
{
	Super::BeginPlay();
	ownerRef = GetOwner();
<<<<<<< Updated upstream
	
=======

	if (GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner initialized: %s"), *ownerRef->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find owner"));
	}
>>>>>>> Stashed changes
}

// Called every frame
void UConeLineTrace::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UConeLineTrace::ConeTrace()
{
<<<<<<< Updated upstream
	if (!ownerRef) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find owner"));
	}
	FVector _startLocation = ownerRef->GetActorLocation();
	FVector _endLocation = ownerRef->GetActorLocation() + ownerRef->GetActorForwardVector() * distance;
	FCollisionQueryParams _ignoreSelfParam;     
	_ignoreSelfParam.AddIgnoredActor(ownerRef);

	TArray<FHitResult> _allHits;
	FQuat _quat = FQuat(ownerRef->GetActorRotation());
=======
	UE_LOG(LogTemp, Warning, TEXT("ConeTraceCalled"));

	if (!IsValid(ownerRef))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find owner"));
		return;
	}
	FVector _startLocation = ownerRef->GetActorLocation();
	FRotator _ownerRotation = ownerRef->GetActorRotation();
	FVector _forwardVector = ownerRef->GetActorForwardVector();
>>>>>>> Stashed changes

	bool _hit = GetWorld()->SweepMultiByChannel(_allHits, _startLocation,
		_endLocation, _quat, 
		_coneTraceChannel, FCollisionShape::MakeSphere(coneTraceRadius),
		_ignoreSelfParam);
	if (_hit)
	{
		for (int i = 0; i < _allHits.Num(); i++)

<<<<<<< Updated upstream
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
=======

	//UE_LOG(LogTemp, Error, TEXT("startLocation %s "),*_startLocation.ToString());

	FVector _endLocation = _startLocation + (_forwardVector * (sphereTracedistance + coneTraceRadius));
	lineTraceEnd = _endLocation;
	//UE_LOG(LogTemp, Error, TEXT("DRAGON ENDLOCATION %s "), *_endLocation.ToString());
	DrawDebugSphere(GetWorld(), _endLocation,
		200, 25, FColor::Black, false, -1, 0, 3);
	FCollisionQueryParams _collisionParams;
	_collisionParams.AddIgnoredActor(ownerRef);
	//_collisionParams.bTraceComplex;

	TArray<FHitResult> _allHits;
	FQuat _quat = FQuat(_ownerRotation);

	bool _hit = GetWorld()->SweepMultiByChannel(_allHits, _startLocation,
		_endLocation, _quat,
		_coneTraceChannel, FCollisionShape::MakeSphere(coneTraceRadius),
		_collisionParams);
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

	DrawDebugSphere(GetWorld(), _startLocation,
		coneTraceRadius + sphereTracedistance, 25, FColor::Orange, false, -1, 0, 3);
	UE_LOG(LogTemp, Warning, TEXT("Conetracefinished"));


>>>>>>> Stashed changes
}


