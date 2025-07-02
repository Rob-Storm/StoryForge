
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "StoryForge/Dialogue/DialogueAsset.h"
#include "StoryForge/Dialogue/Nodes/DialogueNode.h"

#include "StoryForge/StoryForgeGameModeBase.h"

#include "DialogueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STORYFORGE_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	float AutoProgressDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool InDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TObjectPtr<UDialogueAsset> CurrentConversation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TObjectPtr<UDialogueNode> CurrentNode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 CurrentDialogueIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	AStoryForgeGameModeBase GameModeRef;

	//TODO: Convert BP_DialogueCamera to C++
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	//UDialogueCamera DialogueCamera;


public:	
	UDialogueComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
