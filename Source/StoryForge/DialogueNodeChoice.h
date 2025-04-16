#pragma once

#include "CoreMinimal.h"
#include "DialogueNode.h"
#include "DialogueNodeSpeech.h"
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
