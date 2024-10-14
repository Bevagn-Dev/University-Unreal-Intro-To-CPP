#include "Projectile_Base.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AProjectile_Base::AProjectile_Base()
{
	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = _Collider;
	_Collider->SetCollisionProfileName("Projectile");
	_Collider->OnComponentHit.AddUniqueDynamic(this, &AProjectile_Base::Handle_Hit);

	_ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	_ProjectileMovement->UpdatedComponent = _Collider;
	_ProjectileMovement->InitialSpeed = 3000.f;
	_ProjectileMovement->MaxSpeed = 3000.f;
	_ProjectileMovement->bRotationFollowsVelocity = true;
	_ProjectileMovement->bShouldBounce = true;
}

void AProjectile_Base::Handle_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UGameplayStatics::ApplyDamage(OtherActor, _Damage, GetInstigatorController(), this, UDamageType::StaticClass());

		if(OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddForceAtLocation(GetVelocity() * 100.0f, GetActorLocation());

			Destroy();
		}
	}
}



