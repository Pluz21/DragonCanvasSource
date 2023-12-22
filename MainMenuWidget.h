// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class ADragon;
UCLASS()
class DRAGONCANVAS_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<ADragon> playerRef = nullptr;

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetActive();
	
	
	
};
