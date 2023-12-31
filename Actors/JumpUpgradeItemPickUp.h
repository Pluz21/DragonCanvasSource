// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DragonCanvas/Actors/UpgradePickUpItem.h"
#include <Sound/AmbientSound.h>
#include "JumpUpgradeItemPickUp.generated.h"

UCLASS()
class DRAGONCANVAS_API AJumpUpgradeItemPickUp : public AUpgradePickUpItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpUpgradeItemPickUp();

	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void JumpUpgradeInit();
	void ManageOverlap(AActor* _overlapped, AActor* _overlap) override;
	UFUNCTION() void StopPlayAudio();
	UFUNCTION() void PlayAudio();
};
