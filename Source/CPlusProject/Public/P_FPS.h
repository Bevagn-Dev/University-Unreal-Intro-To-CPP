#pragma once
 
#include "CoreMinimal.h"
#include "Inputable.h"
#include "GameFramework/Character.h"

#include "P_FPS.generated.h"
 
class UHealthComponent;
class UCharacterMovementComponent;
class UCameraComponent;
class UCapsuleComponent;
 
UCLASS(Abstract)
class CPLUSPROJECT_API AP_FPS : public ACharacter, public IInputable
{
	GENERATED_BODY()
 
public:
	AP_FPS();
 
	virtual void Input_FirePressed_Implementation() override;
	virtual void Input_FireReleased_Implementation() override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_Look_Implementation(FVector2D value) override;
	virtual void Input_Move_Implementation(FVector2D value) override;
    
	virtual UInputMappingContext* GetMappingContext_Implementation() override;
 
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;
};