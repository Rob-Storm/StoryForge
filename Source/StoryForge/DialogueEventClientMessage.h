#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeEvent.h"
#include "ClientMessage.h"
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