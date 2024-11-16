#pragma once

#include "CoreMinimal.h"
#include "Weapon_Base.h"
#include "Weapon_Projectile.generated.h"

class AProjectile_Base;

UCLASS(Abstract)
class CPLUSPROJECT_API AWeapon_Projectile : public AWeapon_Base
{
	GENERATED_BODY()

public:
	virtual void Fire() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectile_Base> _ProjectileClass;
};


