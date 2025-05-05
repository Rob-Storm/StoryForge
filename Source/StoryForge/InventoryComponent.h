#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/Delegate.h"

#include "Item.h"
#include "ItemSlot.h"

#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FItemSlotColumn
{
	GENERATED_BODY()

	TArray<UItemSlot*> SlotsColumn;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChangedSignature);

/**
 * Basic inventory component for storing items
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STORYFORGE_API UInventoryComponent : public UActorComponent
{

	GENERATED_BODY()

public:	

	UInventoryComponent();

public:
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnInventoryChangedSignature OnInventoryChanged;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<AItem*> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FItemSlotColumn> Grid;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void MoveItem(AItem* Item, FVector2D NewPosition);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropItem(AItem* Item);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool CanAddItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	AItem* GetItemFromGrid(FVector2D Coordinates) const 
	{
		return Grid[Coordinates.X].SlotsColumn[Coordinates.Y]->SlotItem;

		/* What is effectively happening here:
		* 
		*	const FItemSlotColumn ItemColumn = Grid[Coordinates.X];
		*	const TArray<UItemSlot*> ItemRow = ItemColumn.SlotsColumn;
		*	AItem* Item = ItemRow[Coordinates.Y]->SlotItem;
		*
		*	return Item;
		*/
	}

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool DoesItemExistAtLocation(FVector2D Coordinates) { if (GetItemFromGrid(Coordinates)) return true; else return false; }

private:

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool CanItemFit(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetItemLocation(AItem* Item, FVector2D Location);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetGridCellItem(AItem* Item, FVector2D Coordinates)
	{
		Grid[Coordinates.X].SlotsColumn[Coordinates.Y]->SlotItem = Item;
	}

};
