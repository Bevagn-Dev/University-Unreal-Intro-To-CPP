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
	_ProjectileMovement->InitialSpeed = _InitSpeed;
	_ProjectileMovement->MaxSpeed = _MaxSpeed;
	_ProjectileMovement->bRotationFollowsVelocity = true;
	_ProjectileMovement->bShouldBounce = true;

	_BounceCount = 0;
}

void AProjectile_Base::Handle_Hit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), _ImpactSound, GetActorLocation(), 1.0f, 1.0f, 0.0f);
		
		UGameplayStatics::ApplyDamage(OtherActor, _Damage, GetInstigatorController(), this, UDamageType::StaticClass());

		if(OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddForceAtLocation(GetVelocity() * 100.0f, GetActorLocation());

			Destroy();
		}
	}
	
	_BounceCount++;
	if (_BounceCount >= 2)
	{
		Destroy();
	}
}

void AProjectile_Base::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(_LifeSpanHandle, this, &AProjectile_Base::OnTimer, 1.0f, true);
}

void AProjectile_Base::OnTimer()
{
	++_TimerCounter;
	
	if (_TimerCounter >= _LifeSpan)
	{
		Destroy();
		
		GetWorld()->GetTimerManager().ClearTimer(_LifeSpanHandle);
	}
}

void AProjectile_Base::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(_LifeSpanHandle);
}





