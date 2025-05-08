#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "StoryForge/Item/Item.h"

#include "ItemSlot.generated.h"

/**
 * Basis for storing inventory items in a tetris-style
 */
UCLASS()
class STORYFORGE_API UItemSlot : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TObjectPtr<AItem> SlotItem;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool IsCellEmpty() const { if (SlotItem == nullptr) return false; else return true; }
	
};
