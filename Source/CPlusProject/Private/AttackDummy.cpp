#include "AttackDummy.h"

#include "HealthComponent.h"
#include "TargetComponent.h"
#include "P_FPS.h"


AAttackDummy::AAttackDummy()
{
	PrimaryActorTick.bCanEverTick = false;

	_SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = _SkeletalMesh;

	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	_Target = CreateDefaultSubobject<UTargetComponent>(TEXT("Target"));
	

}

void AAttackDummy::BeginPlay()
{
	Super::BeginPlay();

	_Health->OnDamaged.AddUniqueDynamic(this, &AAttackDummy::Handle_Damaged);
	_Health->OnDeath.AddUniqueDynamic(this, &AAttackDummy::Handle_HealthDead);
}

void AAttackDummy::Handle_HealthDead(AController* causer)
{
	UE_LOG(LogTemp, Display, TEXT("You DIED........."));
	
}

void AAttackDummy::Handle_Damaged(float current, float max, float change)
{
	UE_LOG(LogTemp, Display, TEXT("Damaged........."));
	
}



