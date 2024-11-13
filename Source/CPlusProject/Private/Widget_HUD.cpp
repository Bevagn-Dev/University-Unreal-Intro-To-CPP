#include "Widget_HUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidget_HUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (HealthBar)
	{
		if (RadialBarMaterial == nullptr)
		{
			if (HealthBar)
			{
				RadialBarMaterial = UMaterialInstanceDynamic::Create(RadialBarMaterialInterface, this);
				HealthBar->SetBrushFromMaterial(RadialBarMaterial);
			}
		}
		SetRadialPercent(0.0f);
	}

	if (ScoreText)
	{
		ScoreText->SetText(FText::FromString("Score: Null"));
	}
}

void UWidget_HUD::UpdateHealth(float newHealthRatio)
{
	if(HealthBar) {SetRadialPercent(newHealthRatio);}
}

void UWidget_HUD::UpdateScore(int newScore)
{
	if(ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), newScore)));
	}
}

void UWidget_HUD::SetRadialPercent(float progress)
{
	if (RadialBarMaterial)
	{
		RadialBarMaterial->SetScalarParameterValue("Progress", progress);
	}	
}
