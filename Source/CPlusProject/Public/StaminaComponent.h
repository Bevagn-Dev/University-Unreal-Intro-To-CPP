#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, CurrentStamina);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPLUSPROJECT_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStaminaComponent();

	UPROPERTY(BlueprintAssignable)
	FOnStaminaChanged OnStaminaChanged;

	void StartSprinting();
	void StopSprinting();
	void StartStaminaDrain();
	void StartStaminaRegen();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Stamina Settings")
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, Category = "Stamina Settings")
	float StaminaDrainAmount = 10.f;

	UPROPERTY(EditAnywhere, Category = "Stamina Settings")
	float StaminaDrainTime = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Stamina Settings")
	float StaminaRegenAmount = 5.f;

	UPROPERTY(EditAnywhere, Category = "Stamina Settings")
	float StaminaRegenTime = 1.f;

	float CurrentStamina;

	FTimerHandle DrainTimerHandle;
	FTimerHandle RegenTimerHandle;

	void DrainStamina();
	void RegenStamina();
};