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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int _LifeSpan;

	FTimerHandle _LifeSpanHandle;
	int32 _TimerCounter = 0;


private:
	UFUNCTION()
	void Handle_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void BeginPlay() override;
	
	void OnTimer();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};