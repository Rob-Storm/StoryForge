#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Grid.Empty();
	Grid.SetNum(InventoryHeight);

	for (int32 columnIndex = 0; columnIndex < InventoryHeight; columnIndex++)
	{
		FItemSlotColumn& Column = Grid[columnIndex];
		Column.SlotsColumn.SetNum(InventoryWidth);

		for (int32 rowIndex = 0; rowIndex < InventoryWidth; rowIndex++)
		{
			Column.SlotsColumn[rowIndex] = NewObject<UItemSlot>(this);
		}
	}
}

void UInventoryComponent::AddItem(AItem* Item)
{
	Items.Add(Item);

	if (OnInventoryChanged.IsBound())
	{
		OnInventoryChanged.Broadcast();
	}
}

void UInventoryComponent::MoveItem(AItem* Item, FIntPoint NewPosition)
{
	// -RCB 
	// if we don't check for the {-1,-1} Item->InventoryLocation variable
	// we will end up overwriting the inventory data at {0,0} with nullptr 

	if (Item->InventoryLocation != FIntPoint(-1, -1))
	{
		FIntPoint OldLocation = Item->InventoryLocation;

		for (int32 y = 0; y < Item->InventorySize.Y; y++)
		{
			for (int32 x = 0; x < Item->InventorySize.X; x++)
			{
				FIntPoint SlotPosition = OldLocation + FIntPoint(x, y);
				if (GetItemFromGrid(SlotPosition))
				{
					SetGridCellItem(nullptr, SlotPosition);
				}
			}
		}
	}

	SetItemLocation(Item, NewPosition);

	if (OnInventoryChanged.IsBound())
	{
		OnInventoryChanged.Broadcast();
	}
}

void UInventoryComponent::RemoveItem(AItem* Item)
{
	int32 itemIndex = Items.Find(Item);

	if (itemIndex != -1)
	{
		Items.RemoveAt(itemIndex);
	}

	if (OnInventoryChanged.IsBound())
	{
		OnInventoryChanged.Broadcast();
	}
}

void UInventoryComponent::DropItem(AItem* Item)
{
	Item->InventoryLocation = FIntPoint(-1, -1);
}

bool UInventoryComponent::CanAddItem(AItem* Item)
{
	FIntPoint Point = FIntPoint(0, 0);

	return CanItemFit(Item, Point);
}

AItem* UInventoryComponent::GetItemFromGrid(FIntPoint Coordinates) const
{
	if(!IsValidSlot(Coordinates))
	{
		return nullptr;
	}
	else
	{
		return Grid[Coordinates.Y].SlotsColumn[Coordinates.X]->SlotItem;

		/*  -RCB 
		*	What is effectively happening here:
		*
		*	const FItemSlotColumn ItemColumn = Grid[Coordinates.Y];
		*	const TArray<UItemSlot*> ItemRow = ItemColumn.SlotsColumn;
		*	AItem* Item = ItemRow[Coordinates.X]->SlotItem;
		*
		*	return Item;
		*/
	}
}

FIntPoint UInventoryComponent::GetInventorySize() const
{
	return FIntPoint(Grid.Num(), Grid[0].SlotsColumn.Num());
}

bool UInventoryComponent::DoesItemExistAtLocation(FIntPoint Coordinates)
{
	if (GetItemFromGrid(Coordinates)) return true; else return false;
}

bool UInventoryComponent::IsValidSlot(FIntPoint Coordinates) const
{
	return Grid.IsValidIndex(Coordinates.Y) && Grid[0].SlotsColumn.IsValidIndex(Coordinates.X);
}

bool UInventoryComponent::CanItemFit(AItem* Item, FIntPoint& OutFirstValidLocation)
{
	FIntPoint CheckBounds = Item->InventorySize == FIntPoint(1, 1) ? GetInventorySize() : GetInventorySize() - Item->InventorySize;

	bool canItemFit = false;

	for (int32 CheckBoundsY = 0; CheckBoundsY < CheckBounds.Y; CheckBoundsY++)
	{
		for (int32 CheckBoundsX = 0; CheckBoundsX < CheckBounds.X; CheckBoundsX++)
		{
			if (CanItemFitAtLocation(Item, FIntPoint(CheckBoundsX, CheckBoundsY)))
			{
				OutFirstValidLocation = FIntPoint(CheckBoundsX, CheckBoundsY);
				return true;
			}
		}
	}
	
	return false;
}

// CanItemFitAtLocation rewrite number 4294967295
bool UInventoryComponent::CanItemFitAtLocation(AItem* Item, FIntPoint Location)
{
	for (int32 itemBoundsY = 0; itemBoundsY < Item->InventorySize.Y; itemBoundsY++)
	{
		for (int32 itemBoundsX = 0; itemBoundsX < Item->InventorySize.X; itemBoundsX++)
		{
			FIntPoint inventoryLocation = Location + FIntPoint(itemBoundsX, itemBoundsY);

			if (GetItemFromGrid(inventoryLocation) == Item)
			{
				continue;
			}

			if(!IsValidSlot(inventoryLocation))
			{
				return false;
			}

			if (GetItemFromGrid(inventoryLocation))
			{
				return false;
			}
		}
	}

	return true;
}

void UInventoryComponent::SetItemLocation(AItem* Item, FIntPoint Location)
{
	Item->InventoryLocation = Location;

	if (!IsValidSlot(Location)) return;

	for (int32 height = 0; height < Item->InventorySize.Y; height++)
	{
		for (int32 width = 0; width < Item->InventorySize.X; width++)
		{
			SetGridCellItem(Item, FIntPoint(width, height) + Item->InventoryLocation);
		}
	}
}

void UInventoryComponent::SetGridCellItem(AItem* Item, FIntPoint Location)
{
	if (!IsValidSlot(Location)) return;

	Grid[Location.Y].SlotsColumn[Location.X]->SlotItem = Item;
}