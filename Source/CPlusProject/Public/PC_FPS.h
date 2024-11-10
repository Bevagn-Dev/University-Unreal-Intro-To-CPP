#pragma once

#include "CoreMinimal.h"
#include "Controllable.h"
#include "Pawnable.h"
#include "GameFramework/Playercontroller.h"

#include "PC_FPS.generated.h"


class AP_FPS;
class UWidget_HUD;
struct FInputActionValue;
class UInputAction;


UCLASS(abstract)
class CPLUSPROJECT_API APC_FPS : public APlayerController , public  IControllable , public IPawnable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _LookAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _MoveAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _JumpAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _FireAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _InteractAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _CrouchAction;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_HUD> _HUDWidgetClass;
	TObjectPtr<UWidget_HUD> _HUDWidget;
	
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	void Look(const FInputActionValue& value);
	void Move(const FInputActionValue& value);
	void JumpPressed();
	void JumpReleased();
	void FirePressed();
	void FireReleased();
	void InteractPressed();
	void InteractReleased();
	void CrouchPressed();
	void CrouchReleased();

	virtual void OnPossess(APawn* InPawn) override;
	virtual  void AddPoints_Implementation(int points) override;

	void UpdateHealthUI(float NewHealth, float MaxHealth, float ChangeInHealth);
};


