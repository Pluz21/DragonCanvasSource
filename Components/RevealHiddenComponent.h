// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RevealHiddenComponent.generated.h"

class AHiddenActors;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRAGONCANVAS_API URevealHiddenComponent : public UActorComponent
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConditionToRevealIsMet);

	UPROPERTY()
	FConditionToRevealIsMet onConditionToRevealIsMet;
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URevealHiddenComponent();

	UPROPERTY(EditAnywhere)
	TArray<AHiddenActors*> allHiddenActors;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Init();
	UFUNCTION()
	void RevealHidden();

	FConditionToRevealIsMet& GetOnConditionToRevealIsMet() { return onConditionToRevealIsMet;}
		
};
