#include "StaminaComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

UStaminaComponent::UStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentStamina = MaxStamina;
}

void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStaminaComponent::StartSprinting()
{
	GetWorld()->GetTimerManager().ClearTimer(RegenTimerHandle);
}

void UStaminaComponent::StopSprinting()
{
	GetWorld()->GetTimerManager().ClearTimer(DrainTimerHandle);
}

void UStaminaComponent::StartStaminaDrain()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(DrainTimerHandle)) return;
	GetWorld()->GetTimerManager().SetTimer(DrainTimerHandle, this, &UStaminaComponent::DrainStamina, StaminaDrainTime, true);
}

void UStaminaComponent::StartStaminaRegen()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(DrainTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(DrainTimerHandle);
	}

	if (!GetWorld()->GetTimerManager().IsTimerActive(RegenTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(RegenTimerHandle, this, &UStaminaComponent::RegenStamina, StaminaRegenTime, true);
	}
}

void UStaminaComponent::DrainStamina()
{
	if (CurrentStamina <= 0.f)
	{
		StopSprinting();
		GetWorld()->GetTimerManager().ClearTimer(DrainTimerHandle);
		return;
	}

	CurrentStamina = FMath::Clamp(CurrentStamina - StaminaDrainAmount, 0.f, MaxStamina);
	OnStaminaChanged.Broadcast(CurrentStamina);
}

void UStaminaComponent::RegenStamina()
{
	if (CurrentStamina >= MaxStamina)
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenTimerHandle);
		return;
	}

	CurrentStamina = FMath::Clamp(CurrentStamina + StaminaRegenAmount, 0.f, MaxStamina);
	OnStaminaChanged.Broadcast(CurrentStamina);
}