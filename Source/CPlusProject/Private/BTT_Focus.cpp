#include "BTT_Focus.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTT_Focus::UBTT_Focus()
{
	NodeName = TEXT("Focus");
}

void UBTT_Focus::InitializeFromAsset(UBehaviorTree& Asset)
{
	UBlackboardData* BBAsset = GetBlackboardAsset();
	if(ensure(BBAsset))
	{
		Focus_Target.ResolveSelectedKey(*BBAsset);
	}
}

EBTNodeResult::Type UBTT_Focus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	AAIController* controller = OwnerComp.GetAIOwner();
	
	UObject* target = BBComp->GetValueAsObject(Focus_Target.SelectedKeyName);
	AActor* actorTarget = Cast<AActor>(target);
	FVector pos = BBComp->GetValueAsVector(Focus_Target.SelectedKeyName);

	if (actorTarget == nullptr)
	{
		controller->SetFocus(actorTarget);
		return EBTNodeResult::Succeeded;
	}
	else if (!pos.IsZero() && !pos.ContainsNaN())
	{
		controller->SetFocalPoint(pos);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}


FString UBTT_Focus::GetStaticDescription() const
{
	return FString::Printf(TEXT("Focussed Target: %s"), *Focus_Target.SelectedKeyName.ToString());
}
