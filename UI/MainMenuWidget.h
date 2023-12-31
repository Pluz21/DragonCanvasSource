// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class ADragon;

enum class GameState
{
	NONE,
	PLAYING,
	PAUSED
};

UCLASS()
class DRAGONCANVAS_API UMainMenuWidget : public UUserWidget
{

	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInitEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMenuIsVisibleEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGamePausedEvent);
	UPROPERTY()
	FInitEvent onInit;
	UPROPERTY(BlueprintAssignable)
	FMenuIsVisibleEvent onMenuIsVisible;
	UPROPERTY()
	FGamePausedEvent onGamePaused;

	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<ADragon> playerRef = nullptr;
	UPROPERTY()
	TObjectPtr<APlayerController> playerController = nullptr;
	//UPROPERTY()
	//TObjectPtr<UInputMappingContext> mappingContext;
public:
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* widgetToHide;
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UUserWidget> widgetToHideref;
 	
	GameState currentState = GameState::NONE;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Init();
	UFUNCTION()
	void InitInput();

	UFUNCTION(BlueprintCallable)
	void SetActive();
	UFUNCTION(BlueprintCallable)
	void PauseGame();
	UFUNCTION(BlueprintCallable)
	void DisplayCursor();
	UMainMenuWidget* GetMainMenuWidget() { return this; }
	UFUNCTION(BlueprintCallable)
	void SetPlayerInputMode();
	UFUNCTION(BlueprintCallable)
	void HideOtherCurrentWidgets();
	
};
