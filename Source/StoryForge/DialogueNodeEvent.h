#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogueNodeEvent.generated.h"

/**
 * Stand in for those special nodes that ConEdit has
 * 
 * We are using the array indices instead of direct
 * references to each node so this lets us save
 * the designers some time and spare them headaches 
 * from using the simple one-off events
 */

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class STORYFORGE_API UDialogueNodeEvent : public UObject
{
	GENERATED_BODY()
};
