#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthDeadSignature, AController*, causer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthDamagedSignature, float, newHealth,
	float, maxHealth, float, changeInHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CPLUSPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	UPROPERTY(BlueprintAssignable)
	FHealthDeadSignature OnDeath;
	UPROPERTY(BlueprintAssignable)
	FHealthDamagedSignature OnDamaged;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float _CurrentHealth;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _MaxHealth;

	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float damage, const UDamageType* damageType,
		AController* instigator, AActor* causer);
};
