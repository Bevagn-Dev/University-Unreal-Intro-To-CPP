 #pragma once

#include "CoreMinimal.h"
#include "WeaponType.h"
#include "GameFramework/Actor.h"
#include "Weapon_Base.generated.h"

class UArrowComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFireSignature);

UCLASS()
class CPLUSPROJECT_API AWeapon_Base : public AActor
{
	GENERATED_BODY()

public:
	AWeapon_Base();

	UPROPERTY(BlueprintAssignable)
	FWeaponFireSignature OnFire;

	void StartFire();
	void StopFire();

	void Init(UWeaponType* type);

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> _Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _Muzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWeaponType> _TypeData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _FireDelay;
	FTimerHandle _FireDelayTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* _FireSound;
	
	UFUNCTION()
	virtual void Fire();
	
	
};
