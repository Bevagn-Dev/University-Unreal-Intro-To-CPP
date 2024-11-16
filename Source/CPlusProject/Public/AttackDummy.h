#pragma once

#include "CoreMinimal.h"
#include "TargetComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "AttackDummy.generated.h"

UCLASS()
class CPLUSPROJECT_API AAttackDummy : public AActor
{
	GENERATED_BODY()

public:
	AAttackDummy();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> _Collider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UTargetComponent> _Target;
	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
	UFUNCTION()
	void Handle_Damaged(float current, float max, float change);
};
