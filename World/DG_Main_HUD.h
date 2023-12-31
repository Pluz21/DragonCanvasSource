// Copyright © 2023 Pluz21 (TVL). All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "DG_Main_HUD.generated.h"

/**
 * 
 */
UCLASS()
class DRAGONCANVAS_API ADG_Main_HUD : public AHUD
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UMaterialInstance> mat = nullptr;
	UPROPERTY(BlueprintReadWrite)
	FText text;

public:
	
	UFUNCTION(BlueprintCallable)
	void UpdateWidgetVisibility(UUserWidget* _widgetToUpdate, bool _value);
	
	UFUNCTION(BlueprintCallable)
	void SetNewWidget(UMaterialInstance* _targetMat, FText& _targetText);  //Maybe need UMaterial
	void SetRenderTarget();
	
};
