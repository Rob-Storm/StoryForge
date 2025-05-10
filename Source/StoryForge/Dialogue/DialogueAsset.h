#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "StoryForge/Dialogue/Nodes/DialogueNode.h"
#include "StoryForge/Dialogue/Events/DialogueEventCameraAngle.h"
#include "StoryForge/Dialogue/Events/DialogueEvent.h"
#include "StoryForge/Dialogue/Trigger/DialogueTrigger.h"

#include "DialogueAsset.generated.h"

/**
 * Equivalent to Deus Ex's .con files
 */
UCLASS()
class STORYFORGE_API UDialogueAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Options")
	UDialogueTrigger* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")
	TSoftObjectPtr<ACharacter> Target;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Options")
	UDialogueEventCameraAngle* InitialCameraAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="Dialogue")
	TArray<UDialogueNode*> DialogueNodes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Events")
	TArray<UDialogueEvent*> PreDialogueEvents;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Events")
	TArray<UDialogueEvent*> PostDialogueEvents;
};
