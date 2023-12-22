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
	playerRef->GetOnMenuOpened().AddDynamic(this, &UMainMenuWidget::SetActive);
	if (!playerRef)return;
	playerController = GetWorld()->GetFirstPlayerController();
	UE_LOG(LogTemp, Warning, TEXT("WidgetConstructorCalled"));
	onMenuIsVisible.AddDynamic(this, &UMainMenuWidget::PauseGame);
	onGamePaused.AddDynamic(this, &UMainMenuWidget::InitInput);

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
	playerController->Pause();
	currentState = GameState::PAUSED;

	onGamePaused.Broadcast();

}

void UMainMenuWidget::test()
{

}

void UMainMenuWidget::InitInput()
{
	ULocalPlayer* _myPlayer = GetWorld()->GetFirstPlayerController()->GetLocalPlayer();
	if (!_myPlayer)return;
	UEnhancedInputLocalPlayerSubsystem* _inputSystem = _myPlayer->
		GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!_inputSystem)return;
	_inputSystem->AddMappingContext(mappingContext, 0);
	UE_LOG(LogTemp, Warning, TEXT("Swapping IMC"));

}



