// Copyright © 2023 Pluz21 (TVL). All rights reserved.


#include "DG_Main_HUD.h"
#include "Blueprint/UserWidget.h"


void ADG_Main_HUD::UpdateWidgetVisibility(UUserWidget* _widgetToUpdate, bool _value)
{
	{
		ESlateVisibility _visibility;
		if (_value)
		{
			_visibility = ESlateVisibility::Visible;
		}
		else
		{
			_visibility = ESlateVisibility::Hidden;
		}
		_widgetToUpdate->SetVisibility(_visibility);

	}

}

void ADG_Main_HUD::SetNewWidget(UMaterialInstance* _targetMat, FText& _targetText)
{
	mat = _targetMat;
	text = _targetText;
}

void ADG_Main_HUD::SetRenderTarget()
{
	
}
