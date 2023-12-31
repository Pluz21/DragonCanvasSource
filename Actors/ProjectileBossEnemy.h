// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DragonCanvas/Actors/BaseProjectile.h"

#include "ProjectileBossEnemy.generated.h"

class ADragon;

UCLASS()
class DRAGONCANVAS_API AProjectileBossEnemy : public ABaseProjectile
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerHitEvent, ADragon*, playerRef);

	UPROPERTY(EditAnywhere)
	FPlayerHitEvent onPlayerHit;

	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBossEnemy();

	UPROPERTY(EditAnywhere)
	float minDistanceToHitPlayer = 200;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION() void CheckDistanceToPlayer();
	UFUNCTION() void HandlePlayerHit(ADragon* _playerRef);

	FPlayerHitEvent& GetOnPlayerHitEvent() { return onPlayerHit; }

};
