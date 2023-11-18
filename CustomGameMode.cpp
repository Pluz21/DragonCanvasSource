// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"
#include "ProjectileManager.h"

void ACustomGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	InitManager();
}

void ACustomGameMode::InitManager()
{
	if (projectileManager)return; // SINGLETON 
	projectileManager = GetWorld()->SpawnActor<AProjectileManager>(projectileManagerToSpawn);
	if (!projectileManager)
	{
		UE_LOG(LogTemp, Warning, TEXT(" Failed to spawn CubeManager"));
	}
}