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
	SetItemLocation(Item, NewPosition);

	FString DebugMessage = FString::Printf(TEXT("Item: %s new location: %d,%d"), *(Item->ItemName.ToString()), NewPosition.X, NewPosition.Y);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, DebugMessage);
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Dropped item"));

	Item->InventoryLocation = FIntPoint(-1, -1);
}

bool UInventoryComponent::CanAddItem(AItem* Item)
{
	FIntPoint Point = FIntPoint(0, 0);

	return CanItemFit(Item, Point);
}

bool UInventoryComponent::CanItemFit(AItem* Item, FIntPoint& OutFoundLocation)
{
	FIntPoint CheckBounds = Item->InventorySize == FIntPoint(1, 1) ? GetInventorySize() : GetInventorySize() - Item->InventorySize;

	return CanItemFitAtLocation(Item, CheckBounds, OutFoundLocation);
}

bool UInventoryComponent::CanItemFitAtLocation(AItem* Item, FIntPoint Location, FIntPoint& OutFoundLocation)
{
	FIntPoint CheckBounds;

	CheckBounds = Location;

	for (int32 y = 0; y <= CheckBounds.Y; y++)
	{
		for (int32 x = 0; x <= CheckBounds.X; x++)
		{
			bool canPlace = true;

			for (int32 boundsY = 0; boundsY < Item->InventorySize.Y; boundsY++)
			{
				for (int32 boundsX = 0; boundsX < Item->InventorySize.X; boundsX++)
				{
					AItem* ExistingItem = GetItemFromGrid(FIntPoint(x + boundsX, y + boundsY));
					if (ExistingItem != nullptr)
					{
						canPlace = false;

						FString DebugMessage = FString::Printf(TEXT("%d,%d is occupied"), x + boundsX, y + boundsY);

						GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, DebugMessage);

						break;
					}
				}
				if (!canPlace) break;
			}

			if (canPlace)
			{
				OutFoundLocation = FIntPoint(x, y);
				return true;
			}
		}
	}

	return false;
}

void UInventoryComponent::SetItemLocation(AItem* Item, FIntPoint Location)
{
	Item->InventoryLocation = Location;

	for (int32 height = 0; height < Item->InventorySize.Y; height++)
	{
		for (int32 width = 0; width < Item->InventorySize.X; width++)
		{
			SetGridCellItem(Item, FIntPoint(width, height) + Item->InventoryLocation);
		}
	}
}
