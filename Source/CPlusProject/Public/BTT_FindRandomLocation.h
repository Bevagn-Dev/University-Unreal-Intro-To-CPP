#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_FindRandomLocation.generated.h"

UCLASS()
class CPLUSPROJECT_API UBTT_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTT_FindRandomLocation();

	private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float SearchRadius;
	
};
