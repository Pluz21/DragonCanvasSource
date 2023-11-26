// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	physicsHandle = GetPhysicsHandleComponent();
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}



bool UGrabber::FindTargetInReach(FHitResult& _outHitResult)   //maybe transform into bool
{
	FVector _ownerLocation = GetOwner()->GetActorLocation();
	//DrawDebugSphere(GetWorld(), _ownerLocation, sphereRadius, 12, FColor::Blue);
	FVector _targetLocation = _ownerLocation + GetOwner()->GetActorForwardVector() * maxGrabDistance;

	//DrawDebugSphere(GetWorld(), _targetLocation,
	//	sphereRadius, 12, FColor::Red, false, -1, 0, 3);	// ...
	FQuat _ownerQuat = GetOwner()->GetActorQuat();
	FRotator _ownerRotation = GetOwner()->GetActorRotation();
	FCollisionShape _sphere = FCollisionShape::MakeSphere(sphereRadius);

	bool _hit =  GetWorld()->SweepSingleByChannel(_outHitResult, _ownerLocation, // might need to change for more accurate grabbing linetrace
		_targetLocation,
		FQuat::Identity, ECC_EngineTraceChannel1,
		_sphere);
	targetLocation = _targetLocation;
	return _hit;
	
		
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandleComponent()
{
	UPhysicsHandleComponent* _physicsHandleComponent = GetOwner()->
		GetComponentByClass<UPhysicsHandleComponent>();
	return _physicsHandleComponent;
}

void UGrabber::Grab()
{

	FHitResult _hitResult;
	
	bool _hasHit = FindTargetInReach(_hitResult);
	if (!_hasHit) return;
	UPrimitiveComponent* _hitComponent = _hitResult.GetComponent();
	_hitComponent->WakeAllRigidBodies();
	_hitComponent->SetSimulatePhysics(true);   // might need to be actor
	_hitResult.GetActor()->Tags.Add("Grabbed");
	_hitResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	physicsHandle->GrabComponentAtLocationWithRotation(
		_hitComponent, NAME_None,		// might need to be actor
		_hitResult.ImpactPoint,
		_hitComponent->GetComponentRotation());
}

void UGrabber::test()
{
	
	/*if (FindTargetInReach(_hitResult))
		UE_LOG(LogTemp, Warning, TEXT("Called test"));*/
}


