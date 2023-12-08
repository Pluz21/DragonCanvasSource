//Copyright © 2023 Pluz21(TVL).All rights reserved.

#include "SnapManager.h"

// Sets default values
ASnapManager::ASnapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASnapManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnapManager::NotifySnap(AActor* _snappedActor)
{
	onSnap.Broadcast(_snappedActor);
	UE_LOG(LogTemp, Error, TEXT("DEBUG FROM SNAPMANAGER : %s"), *_snappedActor->GetName());

}

