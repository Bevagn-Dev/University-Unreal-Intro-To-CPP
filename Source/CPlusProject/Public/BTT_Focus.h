#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Focus.generated.h"


UCLASS()
class CPLUSPROJECT_API UBTT_Focus : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_Focus();
	
	virtual  void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Focus_Target;
};
