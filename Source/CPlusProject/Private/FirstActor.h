#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstActor.generated.h"
#include "Components/ArrowComponent.h"

UCLASS(Abstract)
class CPLUSPROJECT_API AFirstActor : public AActor
{
	GENERATED_BODY()

public:
	AFirstActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _Arrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<URotatingMovementComponent> _Rotater;
};
