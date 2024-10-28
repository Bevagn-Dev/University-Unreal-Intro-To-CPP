#include "TargetComponent.h"

#include "HealthComponent.h"
#include "GameRule_Target.h"

UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	_PointsValue = 1;
}


void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* owner = GetOwner();
	_Health = owner->FindComponentByClass<UHealthComponent>();
	if(_Health == nullptr)
	{
		_Health = NewObject<UHealthComponent>(owner, TEXT("Health"));
		owner->AddInstanceComponent(_Health);
		_Health->RegisterComponent();
		owner->Modify();
	}

	_Health->OnDeath.AddUniqueDynamic(this, &UTargetComponent::Handle_HealthDead);

	UGameRule_Target::OnRequestTargets.AddUniqueDynamic(this, &UTargetComponent::Handle_GameRuleRequestedTargets);

	OnTargetRegister.Broadcast(this);
}

void UTargetComponent::Handle_HealthDead(AController* causer)
{
	UE_LOG(LogTemp, Display, TEXT("DEAD!!!!!!!!!!!"));
	OnDestroyed.Broadcast(this, causer, _PointsValue);
	GetOwner()->Destroy();
}

void UTargetComponent::Handle_GameRuleRequestedTargets()
{
	OnTargetRegister.Broadcast(this);
}
