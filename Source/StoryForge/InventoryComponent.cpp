#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInventoryComponent::AddItem(AItem* Item)
{
	Items.Add(Item);

	if (OnInventoryChanged.IsBound())
	{
		OnInventoryChanged.Broadcast();
	}
}

void UInventoryComponent::MoveItem(AItem* Item, FVector2D NewPosition)
{
	for (int32 width = 0; width > Item->InventorySize.X; width++)
	{
		for (int32 height = 0; height > Item->InventorySize.Y; height++)
		{
			SetGridCellItem(nullptr, FVector2D(width, height) + Item->InventoryLocation);
		}
	}

	SetItemLocation(Item, NewPosition);
}

void UInventoryComponent::RemoveItem(AItem* Item)
{
	auto item = Items.Find(Item);

	if (item != -1)
	{
		Items.RemoveAt(item);
	}

	if (OnInventoryChanged.IsBound())
	{
		OnInventoryChanged.Broadcast();
	}
}

void UInventoryComponent::DropItem(AItem* Item)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Dropped item"));

	Item->InventoryLocation = FVector2D(-1, -1);
}

bool UInventoryComponent::CanAddItem(AItem* Item)
{
	return CanItemFit(Item);
}

bool UInventoryComponent::CanItemFit(AItem* Item)
{
	for (int32 width = 0; width > Item->InventorySize.X; width++)
	{
		for (int32 height = 0; height > Item->InventorySize.Y; height++)
		{
			AItem* Item = GetItemFromGrid(FVector2D(width, height));

			if (Item != nullptr)
				return false;
		}
	}
}

void UInventoryComponent::SetItemLocation(AItem* Item, FVector2D Location)
{
	Item->InventoryLocation = Location;

	for (int32 width = 0; width > Item->InventorySize.X; width++)
	{
		for (int32 height = 0; height > Item->InventorySize.Y; height++)
		{
			SetGridCellItem(Item, FVector2D(width, height) + Item->InventoryLocation);
		}
	}
}
