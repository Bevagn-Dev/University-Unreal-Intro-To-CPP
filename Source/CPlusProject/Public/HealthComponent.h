#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CPLUSPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float _CurrentHealth;
	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* causer);
};
