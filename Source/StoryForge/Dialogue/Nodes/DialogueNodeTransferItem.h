#pragma once

#include "CoreMinimal.h"

#include "StoryForge/Dialogue/Events/DialogueNodeEvent.h"
#include "StoryForge/Character/SFCharacter.h"
#include "StoryForge/Item/Item.h"

#include "DialogueNodeTransferItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class STORYFORGE_API UDialogueNodeTransferItem: public UDialogueNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trade", meta = (EditCondition = "!TransferToPlayer", EditConditionHides))
	TSoftObjectPtr<ACharacter> TransferTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trade", meta = (EditCondition = "!TransferFromPlayer", EditConditionHides))
	TSoftObjectPtr<ACharacter> TransferFrom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trade")
	bool TransferToPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trade")
	bool TransferFromPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trade")
	TSubclassOf<AItem> Item;

	/** If the player does not have the item, jump to this node*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trade", meta = (EditCondition = "TargetFromPlayer", EditConditionHides))
	int32 HasItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trade", meta = (EditCondition = "TargetFromPlayer", EditConditionHides))
	int32 NoItemIndex;

};