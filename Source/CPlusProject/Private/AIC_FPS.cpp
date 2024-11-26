#include "AIC_FPS.h"

#include "Inputable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"



AAIC_FPS::AAIC_FPS()
{
	PrimaryActorTick.bCanEverTick = true;

	_AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));

	_AISense_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseSight"));
	_AISense_Sight->SightRadius = 2000.0f;
	_AISense_Sight->LoseSightRadius = 2500.0f;
	_AISense_Sight->PeripheralVisionAngleDegrees = 90.0f;
	_AISense_Sight->DetectionByAffiliation.bDetectEnemies = true;
	_AISense_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	_AISense_Sight->DetectionByAffiliation.bDetectNeutrals = false;

	_AIPerception->ConfigureSense(*_AISense_Sight);
	_AIPerception->SetDominantSense(UAISenseConfig_Sight::StaticClass());

	AAIController::SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AAIC_FPS::GetTeamAttitudeTowards(const AActor& Other) const
{
	FGenericTeamId TeamId(FGenericTeamId::GetTeamIdentifier(&Other));
	
	if(TeamId == FGenericTeamId(1))
	{
		return  ETeamAttitude::Friendly;
	}
	if(TeamId == FGenericTeamId(2))
	{
		return  ETeamAttitude::Hostile;
	}
	return  ETeamAttitude::Neutral;
	
}

void AAIC_FPS::BeginPlay()
{
	Super::BeginPlay();
	_AIPerception->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AAIC_FPS::Handle_TargetPerceptionUpdated);
}

void AAIC_FPS::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UInputable::StaticClass()))
	{
		RunBehaviorTree(IInputable::Execute_GetBehaviourTree(InPawn));
	}

	BlackboardComponent = GetBlackboardComponent();
	
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsObject(TargetActorKey, nullptr); 
	}
}

void AAIC_FPS::Handle_TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	switch (Stimulus.Type)
	{
	case 0:
		if (BlackboardComponent)
		{
			BlackboardComponent->SetValueAsObject(TargetActorKey, Actor);
		}
		return;
	default:
		return;
	}
}


