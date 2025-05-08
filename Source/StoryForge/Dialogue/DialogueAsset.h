#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StoryForge/Dialogue/Nodes/DialogueNode.h"
#include "StoryForge/Dialogue/Events/DialogueEventCameraAngle.h"
#include "StoryForge/Dialogue/Events/DialogueEvent.h"

#include "DialogueAsset.generated.h"

/**
 * Equivalent to Deus Ex's .con files
 */
UCLASS()
class STORYFORGE_API UDialogueAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TSoftObjectPtr<ACharacter> Target;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Dialogue")
	UDialogueEventCameraAngle* InitialCameraAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="Dialogue")
	TArray<UDialogueNode*> DialogueNodes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Dialogue")
	TArray<UDialogueEvent*> PreDialogueEvents;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Dialogue")
	TArray<UDialogueEvent*> PostDialogueEvents;
};
