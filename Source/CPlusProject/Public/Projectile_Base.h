#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile_Base.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS(Abstract)
class CPLUSPROJECT_API AProjectile_Base : public AActor
{
	GENERATED_BODY()

public:
	AProjectile_Base();
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> _Collider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> _ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _Damage;

private:
	UFUNCTION()
	void Handle_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};