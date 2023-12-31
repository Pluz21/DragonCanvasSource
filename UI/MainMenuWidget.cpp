// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "MainMenuWidget.h"
#include "DragonCanvas/Actors/Dragon.h"
#include <Kismet/GameplayStatics.h>
#include <EnhancedInputSubsystems.h>

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Init();


}

void UMainMenuWidget::Init()
{
	playerRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
	if (!playerRef)return;
	if (playerRef->GetOnMenuOpened().IsBound()) 
	{
		return;
	}
	playerRef->GetOnMenuOpened().AddDynamic(this, &UMainMenuWidget::SetActive);
	playerController = GetWorld()->GetFirstPlayerController();
	UE_LOG(LogTemp, Warning, TEXT("WidgetConstructorCalled"));
	onMenuIsVisible.AddDynamic(this, &UMainMenuWidget::PauseGame);
	//onGamePaused.AddDynamic(this, &UMainMenuWidget::InitInput);
	onGamePaused.AddDynamic(this, &UMainMenuWidget::DisplayCursor);

	onInit.Broadcast();

}
	//playerController = GetWorld()->GetFirstPlayerController();

void UMainMenuWidget::SetActive()
{
	
	SetVisibility(ESlateVisibility::Visible);
	onMenuIsVisible.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Called event in widget"));

}

void UMainMenuWidget::PauseGame()
{

	SetPlayerInputMode();
	playerController->Pause();
	currentState = GameState::PAUSED;

	onGamePaused.Broadcast();

}

void UMainMenuWidget::DisplayCursor()
{
	playerController->SetShowMouseCursor(true);
}

void UMainMenuWidget::SetPlayerInputMode()
{
	FInputModeGameAndUI _inputMode;
	_inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	playerController->SetInputMode(_inputMode);
}

void UMainMenuWidget::HideOtherCurrentWidgets()
{
	

}



void UMainMenuWidget::InitInput()
{
	//ULocalPlayer* _myPlayer = GetWorld()->GetFirstPlayerController()->GetLocalPlayer();
	//if (!_myPlayer)return;
	//UEnhancedInputLocalPlayerSubsystem* _inputSystem = _myPlayer->
	//	GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	//if (!_inputSystem)return;
	//_inputSystem->AddMappingContext(mappingContext, 0);
	//UE_LOG(LogTemp, Warning, TEXT("Swapping IMC"));

}



