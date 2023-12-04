// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameMode.generated.h"

/**
 * 
 */
class ASnapManager;
class AProjectileManager;

UCLASS()
class DRAGONCANVAS_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectileManager> projectileManagerToSpawn;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASnapManager> snapManagerToSpawn;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AProjectileManager> projectileManager = nullptr;
	UPROPERTY(EditAnywhere)
	TObjectPtr<ASnapManager> snapManager = nullptr;

	
public :

	TObjectPtr<AProjectileManager> GetProjectileManager() { return projectileManager; }
	TObjectPtr<ASnapManager> GetSnapManager() { return snapManager; }

protected:

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	void InitProjectileManager();
	void InitSnapManager();

};
