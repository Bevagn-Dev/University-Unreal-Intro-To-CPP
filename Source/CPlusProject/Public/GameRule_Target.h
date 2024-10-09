#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameRule_Target.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGRTargetRequestSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CPLUSPROJECT_API UGameRule_Target : public UGameRule
{
	GENERATED_BODY()

public:
	UGameRule_Target();

	static  inline  FGameRuleCompleteSignature OnRequestTargets;

	virtual  void Init() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UTargetComponent>> _Targets;

	int _AmountRemaining;

private:
	UFUNCTION()
	void Handle_TargetRegistered(UTargetComponent* target);
	UFUNCTION()
	void Handle_TargetDestroyed(UTargetComponent* target, AController* causer, int targetValue);
	
};
