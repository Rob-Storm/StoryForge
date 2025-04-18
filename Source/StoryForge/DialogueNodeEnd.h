

#pragma once

#include "CoreMinimal.h"
#include "DialogueNode.h"
#include "DialogueNodeEnd.generated.h"

/**
 * Ends the current conversation. 
 * DO NOT PUT EVENTS ON THIS NODE TYPE
 */
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class STORYFORGE_API UDialogueNodeEnd : public UDialogueNode
{
	GENERATED_BODY()
	
};
