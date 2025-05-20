#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DamageHelper.generated.h"

/**
 * 
 */
UCLASS()
class STORYFORGE_API UDamageHelper : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "Damage")
	static int32 GetDamageVelocity(const FVector& Velocity, float DamageThreshold = 0.f, float DamageScale = 1.0, int32 MaxDamage = 999);
};
