// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "DragonCanvas/UI/ResumeButtonWidget.h"
#include "DragonCanvas/UI/MainMenuWidget.h"
#include <DragonCanvas/World/CustomGameMode.h>

void UResumeButtonWidget::NativeConstruct()
{
	Init();
}

void UResumeButtonWidget::Init()
{
	/*if (!resumeButton)
	{
		GEngine->AddOnScreenDebugMessage(1, 0.5, FColor::Black, TEXT(" Failed to find button"));

		return;
	}
	resumeButton->OnClicked.AddDynamic(this, &UResumeButtonWidget::ResumeGame);
	onGameResumed.AddDynamic(this, &UResumeButtonWidget::CloseMenu);
	if (!widgetToClose)return;*/
	//widgetToClose.GetMainMenuWidget();

}

void UResumeButtonWidget::ResumeGame()
{
	//APlayerController* _controller = GetWorld()->GetFirstPlayerController();
	/*AGameModeBase* _gameMode = GetWorld()->GetAuthGameMode<ACustomGameMode>();
	_gameMode->ClearPause();
	onGameResumed.Broadcast();
	GEngine->AddOnScreenDebugMessage(1, 0.5, FColor::Black, TEXT("RESUME GAME"));*/

}

void UResumeButtonWidget::CloseMenu()
{
	//widgetToClose->SetVisibility(ESlateVisibility::Hidden);
}
