#include "BTT_Attack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTT_Attack::UBTT_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller {OwnerComp.GetAIOwner()};
	const APawn* AIPawn = {Controller->GetPawn()};
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTT_Attack::GetStaticDescription() const
{
	return FString::Printf(TEXT("Attack Task"));
}
