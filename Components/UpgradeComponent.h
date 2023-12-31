// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UpgradeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONCANVAS_API UUpgradeComponent : public UActorComponent
{

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FJumpUpgradeEvent, bool, hasJumpUpgrade);
	
	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FJumpUpgradeEvent onJumpUpgradeAcquired;

	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUpgradeComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool hasJumpUpgrade = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetHasJumpUpgrade(bool _value); 

	// Event
	FJumpUpgradeEvent& GetOnJumpUpgradeAcquired() {return onJumpUpgradeAcquired;}
		
};
