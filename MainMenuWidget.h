// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class ADragon;
UCLASS()
class DRAGONCANVAS_API UMainMenuWidget : public UUserWidget
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuIsVisibleEvent);
	UPROPERTY()
	FMenuIsVisibleEvent onMenuIsVisible;

	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<ADragon> playerRef = nullptr;
	UPROPERTY()
	TObjectPtr<APlayerController> playerController = nullptr;

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetActive();
	UFUNCTION(BlueprintCallable)
	void PauseGame();
	
	
	
};
