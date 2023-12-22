// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "MainMenuWidget.h"
#include "DragonCanvas/Actors/Dragon.h"
#include <Kismet/GameplayStatics.h>

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	playerRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
	playerRef->GetOnMenuOpened().AddDynamic(this, &UMainMenuWidget::SetActive);
	if (!playerRef)return;
	playerController = GetWorld()->GetFirstPlayerController();
	UE_LOG(LogTemp, Warning, TEXT("WidgetConstructorCalled"));
	onMenuIsVisible.AddDynamic(this, &UMainMenuWidget::PauseGame);

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
	UE_LOG(LogTemp, Warning, TEXT("Paused"));
	playerController->Pause();

}



