#pragma once

#include "CoreMinimal.h"
#include "DialogueNode.h"
#include "DialogueNodeSpeech.generated.h"

/**
 * Basic speech 
 */
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class STORYFORGE_API UDialogueNodeSpeech : public UDialogueNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SpeakerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SpeechText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* VoiceLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextNodeId;
};
