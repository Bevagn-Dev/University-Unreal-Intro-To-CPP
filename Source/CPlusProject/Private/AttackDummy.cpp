#include "AttackDummy.h"

#include "HealthComponent.h"
#include "TargetComponent.h"
#include "P_FPS.h"


AAttackDummy::AAttackDummy()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = _Collider;

	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	_Target = CreateDefaultSubobject<UTargetComponent>(TEXT("Target"));
	
	_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);
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



