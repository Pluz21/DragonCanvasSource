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

	// ...
	
}


// Called every frame
void UProjectileTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UProjectileTriggerComponent::SnapTarget(AActor*& _targetActor) // Target Actor is Actor to Snap
{
	UE_LOG(LogTemp, Warning, TEXT("ENTERING SNATTARGET FUNCTION"), *_targetActor->GetName());
	if (!_targetActor)return;
	UE_LOG(LogTemp, Warning, TEXT("SECONDPHASE SNATTARGET FUNCTION"), *_targetActor->GetName());
	UPrimitiveComponent* _primitiveCompo = _targetActor->
		GetComponentByClass<UPrimitiveComponent>();
	if (!_primitiveCompo)return;
	FAttachmentTransformRules _worldTransform = FAttachmentTransformRules::KeepWorldTransform;
	FAttachmentTransformRules _snap = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	UE_LOG(LogTemp, Warning, TEXT("THIRD SNATTARGET FUNCTION"), *_targetActor->GetName());
	_primitiveCompo->SetSimulatePhysics(false);
	/*_targetActor->AttachToComponent(GetOwner()->
		GetRootComponent(), _worldTransform);
	UE_LOG(LogTemp, Warning, TEXT("EXIT FUNCTION SNATTARGET FUNCTION"), *_targetActor->GetName());
	*/
	_targetActor->AttachToComponent(GetOwner()->
		GetComponentByClass<UStaticMeshComponent>(), _snap);
	// The grabber is on the player not on the actor to snap

	ADragon* _dragonRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
	if (!_dragonRef)return;
	UGrabber* _grabberCompo = _dragonRef->GetComponentByClass<UGrabber>();
	if (!_grabberCompo)return;
	_grabberCompo->Release();
	/*_grabberCompo->SetIsGrabbing();
	_grabberCompo->SetHitComponent();
	_grabberCompo->SetHitResult();*/
	//todo SetIsGrabbing = false _grabberCompo->
	//Remove hold / Grab 

}

