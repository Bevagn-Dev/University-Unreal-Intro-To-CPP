#include "P_FPS.h"
 
#include "HealthComponent.h"
#include "Weapon_Base.h"
#include "Camera/CameraComponent.h"

AP_FPS::AP_FPS()
{
	PrimaryActorTick.bCanEverTick = true;
 
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);
 
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Attach"));
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

void AP_FPS::BeginPlay()
{
	Super::BeginPlay();

	_Health->OnDeath.AddUniqueDynamic(this, &AP_FPS::Handle_HealthDead);
	_Health->OnDamaged.AddUniqueDynamic(this, &AP_FPS::Handle_Damaged);

	if(_DefaultWeapon)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = this;
		_WeaponRef = GetWorld()->SpawnActor<AWeapon_Base>(_DefaultWeapon, _WeaponAttachPoint->GetComponentTransform(), spawnParams);
		_WeaponRef->AttachToComponent(_WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

void AP_FPS::Handle_HealthDead(AController* causer)
{
	
}

void AP_FPS::Handle_Damaged(float current, float max, float change)
{
	
}
