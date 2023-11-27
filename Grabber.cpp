// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include <DrawDebugHelpers.h>


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
	Hold();
}



bool UGrabber::FindTargetInReach(FHitResult& _outHitResult)   //maybe transform into bool
{
	FVector _ownerLocation = GetOwner()->GetActorLocation();
	//DrawDebugSphere(GetWorld(), _ownerLocation, sphereRadius, 12, FColor::Blue);
	FVector _cameraNormalDirection =  GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation().Vector();
	FVector _targetLocation = _ownerLocation + _cameraNormalDirection * maxGrabDistance;

	//DrawDebugSphere(GetWorld(), _targetLocation,
	//	sphereRadius, 12, FColor::Red, true, -1, 0, 3);	// ...
	FQuat _ownerQuat = GetOwner()->GetActorQuat();
	FRotator _ownerRotation = GetOwner()->GetActorRotation();
	FCollisionShape _sphere = FCollisionShape::MakeSphere(20);
	DrawDebugSphere(GetWorld(), _targetLocation,
		_sphere.GetSphereRadius(), 12, FColor::Green, false, 1, 0, 3);


	FCollisionQueryParams _customParams;
	_customParams.AddIgnoredActor(GetOwner());
	

	bool _hit =  GetWorld()->SweepSingleByChannel(_outHitResult, _ownerLocation, // might need to change for more accurate grabbing linetrace
		_targetLocation,
		FQuat::Identity, ECC_GameTraceChannel2,
		_sphere, _customParams);
	if (!_hit)return false;
	DrawDebugPoint(GetWorld(), _outHitResult.ImpactPoint, 20, FColor::Cyan, false, 5, 0);
	UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *_outHitResult.GetActor()->GetName());

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
	hitResult = _hitResult;
	if (!_hasHit)
	{
		Release();

		return;
	}
	UPrimitiveComponent* _hitComponent = _hitResult.GetComponent();
	hitComponent = _hitComponent;
	_hitComponent->WakeAllRigidBodies();
	_hitComponent->SetSimulatePhysics(true);   // might need to be actor
	if (!_hitResult.GetActor()->ActorHasTag("Grabbed"))
	{
	_hitResult.GetActor()->Tags.Add("Grabbed");
	}
	SetIsGrabbing();
	_hitResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	physicsHandle->GrabComponentAtLocationWithRotation(
		_hitComponent, NAME_None,		// might need to be actor
		_hitResult.ImpactPoint,
		_hitComponent->GetComponentRotation());
	



}

void UGrabber::Hold()
{
	if (!isGrabbing)return;
	if(physicsHandle && physicsHandle->GetGrabbedComponent())
	{
		
			FVector _targetLocation = GetOwner()->GetActorLocation() +  // SELF  BOOSTING RETRO
			GetOwner()->GetActorForwardVector() * holdDistance;
			physicsHandle->SetTargetLocationAndRotation(_targetLocation,
				GetOwner()->GetActorRotation());
		DrawDebugSphere(GetWorld(), _targetLocation, 50, 10, FColor::Emerald);
	}
		
}

void UGrabber::Release()
{

	if (physicsHandle && physicsHandle->GetGrabbedComponent() && isGrabbing == true)
	{
		physicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		AActor* _heldActor = physicsHandle->GetGrabbedComponent()->GetOwner();
		_heldActor->Tags.Remove("Grabbed");
		physicsHandle->ReleaseComponent();
		SetIsGrabbing();
	}

}

void UGrabber::SetIsGrabbing()
{
	isGrabbing = !isGrabbing;
}


void UGrabber::test()
{
	
	/*if (FindTargetInReach(_hitResult))
		UE_LOG(LogTemp, Warning, TEXT("Called test"));*/
}


