#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	_MaxHealth = 100.f;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	_CurrentHealth = _MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* causer)
{
	UE_LOG(LogTemp, Display, TEXT("Damage: %f"), damage);
	const float change = FMath::Min(_CurrentHealth, damage);
	_CurrentHealth -= change;
	OnDamaged.Broadcast(_CurrentHealth, _MaxHealth, change);
	if(_CurrentHealth == 0.0f){OnDeath.Broadcast(instigator);}
}