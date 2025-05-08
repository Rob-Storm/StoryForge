#pragma once

#include "CoreMinimal.h"
#include "StoryForge/Dialogue/Events/DialogueNodeEvent.h"
#include "StoryForge/Character/ClientMessage.h"
#include "DialogueEventClientMessage.generated.h"

/**
 * Test event class
 */
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class STORYFORGE_API UDialogueEventClientMessage : public UDialogueNodeEvent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ClientMessage")
	FClientMessage ClientMessage;
};