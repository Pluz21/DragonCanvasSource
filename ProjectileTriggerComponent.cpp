// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileTriggerComponent.h"
#include "Grabber.h"
#include "Dragon.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UProjectileTriggerComponent::UProjectileTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProjectileTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
	// ...
	
}

void UProjectileTriggerComponent::Init()
{
	ADragon* _dragonRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
	dragonRef = _dragonRef;
}




// Called every frame
void UProjectileTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UProjectileTriggerComponent::SnapTarget(AActor*& _targetActor) // Target Actor is Actor to Snap
{
	if (!_targetActor)return;
	UPrimitiveComponent* _primitiveCompo = _targetActor->
		GetComponentByClass<UPrimitiveComponent>();
	if (!_primitiveCompo)return;
	FAttachmentTransformRules _worldTransform = FAttachmentTransformRules::KeepWorldTransform;
	FAttachmentTransformRules _snap = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

	if (!MaterialChecker(_targetActor))return; // Check if the material is the same 
	_primitiveCompo->SetSimulatePhysics(false);
	_targetActor->AttachToComponent(GetOwner()->
		GetComponentByClass<UStaticMeshComponent>(), _snap);

	// The grabber is on the player not on the actor to snap
	if (!dragonRef) 
	{
		ADragon* _dragonRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
		dragonRef = _dragonRef;
	} // Adding this security if the dragonRef came to change during play. 
	UGrabber* _grabberCompo = dragonRef->GetComponentByClass<UGrabber>();
	if (!_grabberCompo)return;
	_grabberCompo->Release();


}

bool UProjectileTriggerComponent::MaterialChecker(AActor*& _targetToCheck)
{

	/*AActor* _owner = GetOwner(); 

	if (!_owner)return false; 
	
	UStaticMeshComponent* _ownerMesh =
		_owner->GetComponentByClass<UStaticMeshComponent>();

	UMaterial* _currentMaterial = _ownerMesh->GetMaterial(0)->GetMaterial();
	mat = _currentMaterial;*/
	return true;
}


