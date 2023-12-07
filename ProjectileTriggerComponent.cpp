// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileTriggerComponent.h"

#include "Grabber.h"
#include "Spawner.h"
#include "FireSpawner.h"
#include "CustomGameMode.h"
#include "SnapManager.h"
#include "Enemy.h"
#include "ColorActivator.h"
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
	gameMode = GetWorld()->GetAuthGameMode<ACustomGameMode>();
	if (!gameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("Game mode not found."));
		return;
	}

	snapManager = gameMode->GetSnapManager();
	if (!snapManager)
	{
		UE_LOG(LogTemp, Error, TEXT("Snap manager not found."));
		return;
	}

	snapManager->OnSnap().AddUniqueDynamic(this, &UProjectileTriggerComponent::HandleSnap);
	
	ADragon* _dragonRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
	dragonRef = _dragonRef;
}

void UProjectileTriggerComponent::Test(AActor* _snappedActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Snapped actor : %s"), *_snappedActor->GetName());
}




// Called every frame
void UProjectileTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
	_primitiveCompo->SetSimulatePhysics(false);
	_targetActor->AttachToComponent(GetOwner()->
		GetComponentByClass<UStaticMeshComponent>(), _snap);

	snapManager->NotifySnap(_targetActor); // Broadcast through the manager
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
void UProjectileTriggerComponent::HandleSnap(AActor* _actorToSnap)
{
	if (!snapManager)return;

	AColorActivator* _vessel = Cast<AColorActivator>(GetOwner()); //vessel with triggercompo
	if (_vessel)
	{
		UE_LOG(LogTemp, Warning, TEXT("Vessel Name: %s, IsSpawner: %d"), *_vessel->GetName(), _vessel->GetIsSpawner());
		allVessels.Add(_vessel);


	}


	UGameplayStatics::GetAllActorsOfClass(GetWorld(), vesselToFind, allVessels);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), spawnerToFind, allSpawners);

	int _sizeAllVessels = allVessels.Num();
	for (int i = 0; i < _sizeAllVessels; i++)
	{

		AColorActivator* _vesselRef = Cast<AColorActivator>(allVessels[i]);
		//UE_LOG(LogTemp, Warning, TEXT("Vessel Name: %s, IsSpawner: %d"), *_vesselRef->GetName(), _vesselRef->GetIsSpawner());

		{
			int _sizeAllSpawners = allSpawners.Num();
			for (int j = 0; j < _sizeAllSpawners; j++)
			{
				AFireSpawner* _fireSpawnerRef = Cast<AFireSpawner>(allSpawners[j]);

				if (_fireSpawnerRef)
				{
					AActor* _spawnedEnemy = _fireSpawnerRef->Spawn();
					allSpawnedFromSnap.Add(_spawnedEnemy);
					UE_LOG(LogTemp, Error, TEXT("Final loop"));
				}
			}
			// specific exit loop because we check vesselref = vessel.
			//break;
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