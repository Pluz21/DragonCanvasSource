// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "MainMenuWidget.h"
#include "DragonCanvas/Actors/Dragon.h"
#include <Kismet/GameplayStatics.h>

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	playerRef = Cast<ADragon>(UGameplayStatics::GetActorOfClass(GetWorld(), ADragon::StaticClass()));
	playerRef->GetOnMenuOpened().AddDynamic(this, &UMainMenuWidget::SetActive);
	UE_LOG(LogTemp, Warning, TEXT("WidgetConstructorCalled"));

}

void UMainMenuWidget::SetActive()
{
	
	SetVisibility(ESlateVisibility::Visible);
	UE_LOG(LogTemp, Warning, TEXT("Called event in widget"));
}



