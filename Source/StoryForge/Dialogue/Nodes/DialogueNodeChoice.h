#pragma once

#include "CoreMinimal.h"
#include "StoryForge/Dialogue/Nodes/DialogueNode.h"
#include "StoryForge/Dialogue/Nodes/DialogueNodeSpeech.h"
#include "DialogueNodeChoice.generated.h"

/**
 * Node representing X amount of choices
 */
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class STORYFORGE_API UDialogueNodeChoice : public UDialogueNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> ChoiceIndexMap;
};
