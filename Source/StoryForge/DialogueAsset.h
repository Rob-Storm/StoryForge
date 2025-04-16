#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogueNode.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="Dialogue")
	TArray<UDialogueNode*> DialogueNodes;	
};
