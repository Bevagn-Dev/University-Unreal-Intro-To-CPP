#pragma once

#include "CoreMinimal.h

#include "Engine/DataAsset.h"
#include "WeaponType.generated.h"

UCLASS(BlueprintType)
class CPLUSPROJECT_API UWeaponType : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> _WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _damage;
};
