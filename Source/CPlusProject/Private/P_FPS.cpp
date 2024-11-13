#include "P_FPS.h"
 
#include "HealthComponent.h"
#include "Interactable.h"
#include "Weapon_Base.h"
#include "Camera/CameraComponent.h"
#include "Engine/HitResult.h"
#include "Kismet/KismetSystemLibrary.h"


AP_FPS::AP_FPS()
{
	PrimaryActorTick.bCanEverTick = true;
 
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);
 
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	_WeaponAttachPoint = CreateDefaultSubobject<USpringArmComponent>(TEXT("Weapon Attach"));
	_WeaponAttachPoint->SetupAttachment(_Camera);
}
 
void AP_FPS::Input_FirePressed_Implementation()
{
	if(_WeaponRef)
	{
		_WeaponRef->StartFire();
	}
}
 
void AP_FPS::Input_FireReleased_Implementation()
{
	if(_WeaponRef)
	{
		_WeaponRef->StopFire();
	}
}

void AP_FPS::Input_InteractPressed_Implementation()
{
	UWorld* const world = GetWorld();
	if (world == nullptr) { return; }

	FHitResult hit(ForceInit);
	FVector start = _Camera->GetComponentLocation();
	FVector end = start + (_Camera->GetForwardVector() * 500);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	
	if (UKismetSystemLibrary::SphereTraceSingle(
		world, start, end, 20,UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2),
		false, ActorsToIgnore, EDrawDebugTrace::ForDuration, hit, true,
		FLinearColor::Red, FLinearColor::Green, 5))
	{
		AActor* hitActor = hit.GetActor();
		if (hitActor)
		{
			if (UKismetSystemLibrary::DoesImplementInterface(hitActor, UInteractable::StaticClass()))
			{
				IInteractable::Execute_Interact(hitActor);
			}
		}
	}
}

void AP_FPS::Input_InteractReleased_Implementation()
{
	
}

void AP_FPS::Input_JumpPressed_Implementation()
{
	ACharacter::Jump();
}
 
void AP_FPS::Input_JumpReleased_Implementation()
{
	ACharacter::StopJumping();
}

void AP_FPS::Input_CrouchPressed_Implementation()
{
	ACharacter::Crouch();
}

void AP_FPS::Input_CrouchReleased_Implementation()
{
	ACharacter::UnCrouch();
}

void AP_FPS::Input_Look_Implementation(FVector2D value)
{
	FRotator currentRotation = _Camera->GetRelativeRotation();
	float newPitch = FMath::Clamp(currentRotation.Pitch + value.Y,-89.0f, 89.0f);
	
	AddActorWorldRotation(FRotator(0.0f, value.X, 0.0f));
	_Camera->SetRelativeRotation(FRotator(newPitch, 0.0f, 0.0f));
}
 
void AP_FPS::Input_Move_Implementation(FVector2D value)
{
	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(),
		FVector::UpVector).GetSafeNormal(), value.Y);
	AddMovementInput(_Camera->GetRightVector(), value.X);
}
 
UInputMappingContext* AP_FPS::GetMappingContext_Implementation()
{
	return _InputMapping;
}

UBehaviorTree* AP_FPS::GetBehaviourTree_Implementation()
{
	return _BehaviorTree;
}

void AP_FPS::BeginPlay()
{
	Super::BeginPlay();
	
	_Health->OnDamaged.AddUniqueDynamic(this, &AP_FPS::Handle_Damaged);
	_Health->OnDeath.AddUniqueDynamic(this, &AP_FPS::Handle_HealthDead);


	if(_DefaultWeapon)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = this;
		TObjectPtr<AWeapon_Base> spawnedGun = GetWorld()->SpawnActor<AWeapon_Base>(_DefaultWeapon, _WeaponAttachPoint->GetComponentTransform(), spawnParams);
		spawnedGun->AttachToComponent(_WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

void AP_FPS::Handle_HealthDead(AController* causer)
{
	UE_LOG(LogTemp, Display, TEXT("You DIED........."));
}

void AP_FPS::Handle_Damaged(float current, float max, float change)
{
	UE_LOG(LogTemp, Display, TEXT("Damaged Pawn"));
	OnPawnDamaged.Broadcast(current, max, change);
}
