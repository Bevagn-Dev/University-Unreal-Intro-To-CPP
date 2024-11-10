#pragma once

#include "CoreMinimal.h"

#include "Pawnable.generated.h"

UINTERFACE()
class UPawnable : public UInterface
{
	GENERATED_BODY()
};

class CPLUSPROJECT_API IPawnable
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FPawnDamagedSignature, float, newHealth,
		float, maxHealth, float, changeInHealth);
};
