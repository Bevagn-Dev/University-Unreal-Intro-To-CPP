#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Widget_HUD.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS(Abstract, BlueprintType)
class CPLUSPROJECT_API UWidget_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void UpdateHealth(float newHealthRatio);
	void UpdateStamina(float newStaminaRatio);
	void UpdateScore(int newScore);
	void SetHealthPercent(float progress);
	void SetStaminaPercent(float progress);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> HealthBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> StaminaBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMaterialInstanceDynamic> RadialHealthBarMaterial;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMaterialInstanceDynamic> RadialStaminaBarMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* RadialHealthBarMaterialInterface;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* RadialStaminaBarMaterialInterface;
};
