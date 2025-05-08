#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/Delegate.h"

#include "StoryForge/Item/Item.h"
#include "StoryForge/Item/ItemSlot.h"

#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FItemSlotColumn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<UItemSlot*> SlotsColumn;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChangedSignature);

/**
 * """""Basic""""" inventory component for storing items
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STORYFORGE_API UInventoryComponent : public UActorComponent
{

	GENERATED_BODY()

public:	

	UInventoryComponent();

public:
	
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChangedSignature OnInventoryChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 InventoryWidth = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 InventoryHeight = 6;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<AItem*> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FItemSlotColumn> Grid;

protected:

	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void MoveItem(AItem* Item, FIntPoint NewPosition);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropItem(AItem* Item);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool CanAddItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	AItem* GetItemFromGrid(FIntPoint Coordinates) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	FIntPoint GetInventorySize() const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool DoesItemExistAtLocation(FIntPoint Coordinates);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool IsValidSlot(FIntPoint Coordinates) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool CanItemFit(AItem* Item, FIntPoint& OutFoundLocation);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool CanItemFitAtLocation(AItem* Item, FIntPoint Location);

private:

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemLocation(AItem* Item, FIntPoint Location);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetGridCellItem(AItem* Item, FIntPoint Coordinates);

};
