// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"
#include "ProjectileManager.h"
#include "SnapManager.h"

void ACustomGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	InitProjectileManager();
	InitSnapManager();
}

void ACustomGameMode::InitProjectileManager()
{
	if (projectileManager)return; // SINGLETON 
	projectileManager = GetWorld()->SpawnActor<AProjectileManager>(projectileManagerToSpawn);
	if (!projectileManager)
	{
		UE_LOG(LogTemp, Warning, TEXT(" Failed to spawn CubeManager"));
	}
}

void ACustomGameMode::InitSnapManager()
{
	if (snapManager)return;
	snapManager = GetWorld()->
		SpawnActor<ASnapManager>(snapManagerToSpawn);
	if (!snapManager)
	{
		UE_LOG(LogTemp, Warning, TEXT(" Failed to spawn SnapManager"));

	}
	
}
