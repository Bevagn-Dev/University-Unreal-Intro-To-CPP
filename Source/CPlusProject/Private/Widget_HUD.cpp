#include "Widget_HUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidget_HUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (HealthBar)
	{
		if (RadialHealthBarMaterial == nullptr)
		{
			if (HealthBar)
			{
				RadialHealthBarMaterial = UMaterialInstanceDynamic::Create(RadialHealthBarMaterialInterface, this);
				HealthBar->SetBrushFromMaterial(RadialHealthBarMaterial);
			}
		}
		SetHealthPercent(0.0f);
	}

	if (StaminaBar)
	{
		if (RadialStaminaBarMaterial == nullptr)
		{
			if (StaminaBar)
			{
				RadialStaminaBarMaterial = UMaterialInstanceDynamic::Create(RadialStaminaBarMaterialInterface, this);
				StaminaBar->SetBrushFromMaterial(RadialStaminaBarMaterial);
			}
		}
		SetStaminaPercent(0.0f);
	}
	
	if (ScoreText)
	{
		ScoreText->SetText(FText::FromString("Score: Null"));
	}
}

void UWidget_HUD::UpdateHealth(float newHealthRatio)
{
	if(HealthBar) {SetHealthPercent(newHealthRatio);}
}

void UWidget_HUD::UpdateStamina(float newStaminaRatio)
{
	if(StaminaBar) {SetStaminaPercent(newStaminaRatio);}
}

void UWidget_HUD::UpdateScore(int newScore)
{
	if(ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), newScore)));
	}
}

void UWidget_HUD::SetHealthPercent(float progress)
{
	if (RadialHealthBarMaterial)
	{
		RadialHealthBarMaterial->SetScalarParameterValue("Progress", progress);
	}	
}

void UWidget_HUD::SetStaminaPercent(float progress)
{
	if (RadialStaminaBarMaterial)
	{
		RadialStaminaBarMaterial->SetScalarParameterValue("Progress", progress);
	}	
}
