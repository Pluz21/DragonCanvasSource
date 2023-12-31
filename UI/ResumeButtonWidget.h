// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "ResumeButtonWidget.generated.h"

/**
 * 
 */
class UMainMenuWidget;

UCLASS()
class DRAGONCANVAS_API UResumeButtonWidget : public UUserWidget
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameResumeEvent);
	UPROPERTY(EditAnywhere)
	FGameResumeEvent onGameResumed;
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere)
	TSubclassOf<UButton> resumeButton = nullptr;


	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainMenuWidget> widgetToClose = nullptr;

	virtual void NativeConstruct() override;

	void Init();
	UFUNCTION() void ResumeGame();
	UFUNCTION() void CloseMenu();
};
