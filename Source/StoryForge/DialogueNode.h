#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeEvent.h"
#include "DialogueNode.generated.h"

/**
 * Basic Dialogue node
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class STORYFORGE_API UDialogueNode : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
	TArray<UDialogueNodeEvent*> PreEvents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
	TArray<UDialogueNodeEvent*> PostEvents;
};
