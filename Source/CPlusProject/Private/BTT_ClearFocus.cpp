#include "BTT_ClearFocus.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"


EBTNodeResult::Type UBTT_ClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	if (controller)
	{
		controller->ClearFocus(EAIRequestPriority::Lowest);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}