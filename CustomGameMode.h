// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameMode.generated.h"

/**
 * 
 */
class AProjectileManager;
UCLASS()
class DRAGONCANVAS_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectileManager> projectileManagerToSpawn;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AProjectileManager> projectileManager = nullptr;
	
public :

	TObjectPtr<AProjectileManager> GetProjectileManager() { return projectileManager; }

protected:

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	void InitManager();

};
