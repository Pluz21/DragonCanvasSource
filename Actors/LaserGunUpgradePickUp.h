// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UpgradePickUpItem.h"

#include "LaserGunUpgradePickUp.generated.h"


UCLASS()
class DRAGONCANVAS_API ALaserGunUpgradePickUp : public AUpgradePickUpItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserGunUpgradePickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() void TriggerPlayerGunSwap();
	void ItemAction() override;
};
