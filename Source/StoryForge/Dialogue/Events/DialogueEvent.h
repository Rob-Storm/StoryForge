#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogueEvent.generated.h"

/**
 * Trigger events before or after a conversation happens
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class STORYFORGE_API UDialogueEvent : public UObject
{
	GENERATED_BODY()
	
};
