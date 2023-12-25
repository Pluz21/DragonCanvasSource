// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DragonCanvas/Actors/Enemy.h"
#include "BossEnemy.generated.h"

UCLASS()
class DRAGONCANVAS_API ABossEnemy : public AEnemy
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialCheckerComponent> materialCheckerCompo2;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> thirdMesh;
public:	
	// Sets default values for this actor's properties
	ABossEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UStaticMeshComponent* GetThirdMesh() { return thirdMesh; }
	UMaterialCheckerComponent* GetMaterialCheckerComponent2() { return materialCheckerCompo2; }


};
