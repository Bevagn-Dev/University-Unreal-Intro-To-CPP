#pragma once
 
#include "CoreMinimal.h"
#include "Inputable.h"
#include "Pawnable.h"
#include "WeaponType.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "P_FPS.generated.h"

class AWeapon_Base;
class UInputMappingContext;
class UHealthComponent;
class UCharacterMovementComponent;
class UCameraComponent;
class UCapsuleComponent;
class UBehaviorTree;


UCLASS(Abstract)
class CPLUSPROJECT_API AP_FPS : public ACharacter, public IInputable , public IPawnable
{
	GENERATED_BODY()
 
public:
	AP_FPS();
 
	virtual void Input_FirePressed_Implementation() override;
	virtual void Input_FireReleased_Implementation() override;
	virtual void Input_InteractPressed_Implementation() override;
	virtual void Input_InteractReleased_Implementation() override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_CrouchPressed_Implementation() override;
	virtual void Input_CrouchReleased_Implementation() override;
	virtual void Input_SprintPressed_Implementation() override;
	virtual void Input_SprintReleased_Implementation() override;
	virtual  void Input_Explode_Implementation() override;

	virtual void Input_Look_Implementation(FVector2D value) override;
	virtual void Input_Move_Implementation(FVector2D value) override;
    
	virtual UInputMappingContext* GetMappingContext_Implementation() override;
	virtual UBehaviorTree* GetBehaviourTree_Implementation() override;

	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaminaComponent> _Stamina;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<USceneComponent> _WeaponAttachPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AWeapon_Base> _DefaultWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<AWeapon_Base> _WeaponRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TObjectPtr<UInputMappingContext> _InputMapping;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TObjectPtr<UBehaviorTree> _BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TObjectPtr<UParticleSystem> _ExplosionSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed;
		
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
	UFUNCTION()
	void Handle_Damaged(float current, float max, float change);
	
	FTimerHandle _DrainTimeHandle;
	FTimerHandle _RegenTimeHandle;
	int32 _TimerCounter = 0;
	
};