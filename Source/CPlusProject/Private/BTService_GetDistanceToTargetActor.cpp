#include "BTService_GetDistanceToTargetActor.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_GetDistanceToTargetActor::UBTService_GetDistanceToTargetActor()
{
	bNotifyTick = true;
	bNotifyBecomeRelevant = false;
	bNotifyCeaseRelevant = false;

	key_Pawn.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_GetDistanceToTargetActor, key_Pawn), APawn::StaticClass());
	key_TargetActor.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_GetDistanceToTargetActor, key_TargetActor), AActor::StaticClass());
	key_Distance.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_GetDistanceToTargetActor, key_Distance));
}

void UBTService_GetDistanceToTargetActor::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();
	if(ensure(BBAsset))
	{
		key_Pawn.ResolveSelectedKey(*BBAsset);
		key_TargetActor.ResolveSelectedKey(*BBAsset);
		key_Distance.ResolveSelectedKey(*BBAsset);
	}
}

void UBTService_GetDistanceToTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	float dist = (Cast<AActor>(BBComp->GetValueAsObject(key_Pawn.SelectedKeyName))->GetActorLocation() - Cast<AActor>(BBComp
		->GetValueAsObject(key_TargetActor.SelectedKeyName))->GetActorLocation()).Length();
	BBComp->SetValueAsFloat(key_Distance.SelectedKeyName, dist);	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
