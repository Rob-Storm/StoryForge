#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Damageable.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UDamageable : public UInterface
{
	GENERATED_BODY()	
};

class IDamageable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
	void Damage(AActor* CallingActor, int32 Damage);

};