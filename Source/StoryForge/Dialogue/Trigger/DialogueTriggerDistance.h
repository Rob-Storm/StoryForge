#pragma once

#include "CoreMinimal.h"
#include "StoryForge/Dialogue/Trigger/DialogueTrigger.h"
#include "DialogueTriggerDistance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class STORYFORGE_API UDialogueTriggerDistance : public UDialogueTrigger
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	float TriggerDistance = 200.f;
};
