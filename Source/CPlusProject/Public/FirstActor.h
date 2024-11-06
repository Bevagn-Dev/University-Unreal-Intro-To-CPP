#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"

#include "FirstActor.generated.h"

class UBoxComponent;
class UArrowComponent;

UCLASS(Abstract)
class CPLUSPROJECT_API AFirstActor : public AActor , public IInteractable
{
	GENERATED_BODY()

public:
	AFirstActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> _Collider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _Arrow;

	UFUNCTION()
	void Handle_ColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void BeginPlay() override;

	virtual void Interact_Implementation() override;
};


