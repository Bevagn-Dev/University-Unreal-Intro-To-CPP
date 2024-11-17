#pragma once

#include "CoreMinimal.h"

#include "Pawnable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPawnDamagedSignature, float, currentHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPawnStaminaSignature, float, currentStamina);

UINTERFACE()
class UPawnable : public UInterface
{
	GENERATED_BODY()
};

class CPLUSPROJECT_API IPawnable
{
	GENERATED_BODY()

public:
	FPawnDamagedSignature OnPawnDamaged;
	FPawnStaminaSignature OnPawnStamina;
};
