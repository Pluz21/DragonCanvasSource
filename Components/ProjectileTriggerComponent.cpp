//Copyright © 2023 Pluz21(TVL).All rights reserved.

#include "ProjectileTriggerComponent.h"

#include "Grabber.h"
#include "DragonCanvas/Actors/Spawner.h"
#include "DragonCanvas/World/CustomGameMode.h"
#include "DragonCanvas/Actors/Enemy.h"
#include "DragonCanvas/Actors/ColorActivator.h"
#include "DragonCanvas/Actors/Dragon.h"

#include <Kismet/GameplayStatics.h>

UProjectileTriggerComponent::UProjectileTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}


void UProjectileTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UProjectileTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
	
}

void UProjectileTriggerComponent::Init()
{
	gameMode = GetWorld()->GetAuthGameMode<ACustomGameMode>();
	if (!gameMode)
		{
			UE_LOG(LogTemp, Error, TEXT("Game mode not found."));
			return;
		}
	onSnap.AddDynamic(this, &UProjectileTriggerComponent::HandleSnap);

	/*snapManager = gameMode->GetSnapManager();
	if (!snapManager)
		{
			UE_LOG(LogTemp, Error, TEXT("Snap manager not found."));
			return;
		}*/

	//snapManager->OnSnap().AddUniqueDynamic(this, &UProjectileTriggerComponent::HandleSnap);
	
	ADragon* _dragonRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
	dragonRef = _dragonRef;
}

void UProjectileTriggerComponent::Test(AActor* _snappedActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Snapped actor : %s"), *_snappedActor->GetName());
}


void UProjectileTriggerComponent::SnapTarget(AActor* _targetActor) // Target Actor is Actor to Snap
{
	if (!_targetActor)return;

	UPrimitiveComponent* _primitiveCompo = _targetActor->
		GetComponentByClass<UPrimitiveComponent>();

	if (!_primitiveCompo)return;

	FAttachmentTransformRules _worldTransform = FAttachmentTransformRules::KeepWorldTransform;
	FAttachmentTransformRules _snap = FAttachmentTransformRules::SnapToTargetNotIncludingScale;

	if (!MaterialChecker(_targetActor))return; // Check if the material is the same 

	_primitiveCompo->SetSimulatePhysics(false);				//Snap
	_targetActor->AttachToComponent(GetOwner()->
		GetComponentByClass<UStaticMeshComponent>(), _snap);

	//snapManager->NotifySnap(_targetActor); // Broadcast through the manager
	// The grabber is on the player not on the actor to snap
	onSnap.Broadcast(_targetActor);
	if (!dragonRef) 
	{
		ADragon* _dragonRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
		dragonRef = _dragonRef;
	} // Adding this security if the dragonRef came to change during play. 

	UGrabber* _grabberCompo = dragonRef->GetComponentByClass<UGrabber>();

	if (!_grabberCompo)return;

	_grabberCompo->Release();
	


}

void UProjectileTriggerComponent::HandleSnap(AActor* _actorToSnap)
{
	UE_LOG(LogTemp, Warning, TEXT("HandleSnap Call"));

	AColorActivator* _vessel = Cast<AColorActivator>(GetOwner()); //vessel with triggercompo
	if (_vessel)
	{
		UE_LOG(LogTemp, Warning, TEXT("Vessel Name: %s, IsSpawner: %d"), *_vessel->GetName(), _vessel->GetIsSpawner());
		allVessels.Add(_vessel);

	}
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), vesselToFind, allVessels);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), spawnerToFind, allSpawners);


	int _sizeAllSpawners = allSpawners.Num();
	for (int i = 0; i < _sizeAllSpawners; i++)
	{
		ASpawner* _spawnerRef = Cast<ASpawner>(allSpawners[i]);

		if (_spawnerRef)
		{
			AActor* _spawnedEnemy = _spawnerRef->Spawn();
			allSpawnedFromSnap.Add(_spawnedEnemy);
		}


	}

}

bool UProjectileTriggerComponent::MaterialChecker(AActor*& _targetToCheck)
{

	AActor* _owner = GetOwner(); 

	if (!_owner)return false; 
	UStaticMeshComponent* _ownerMesh =
		_owner->GetComponentByClass<UStaticMeshComponent>();
	if(UMaterialInterface* _currentMaterial = _ownerMesh->GetMaterial(0))
	mat = _currentMaterial;
	UMaterialInterface* _currentMaterial = _ownerMesh->GetMaterial(0);
	// not sure
	UStaticMeshComponent* _targetMesh = _targetToCheck->
		GetComponentByClass<UStaticMeshComponent>();
	UMaterialInterface* _targetMaterial = _targetMesh->GetMaterial(0);
	targetMat = _targetMaterial;
	if (_targetMaterial != _currentMaterial)
	{
		return false;
	}
	return true;
}