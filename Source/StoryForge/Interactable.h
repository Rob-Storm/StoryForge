#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interactable.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()	
};

class IInteractable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void Interact(AActor* CallingActor);

};