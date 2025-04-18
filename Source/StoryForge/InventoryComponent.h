#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "InventoryComponent.generated.h"

/**
 * Basic inventory component for storing items
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChangedSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STORYFORGE_API UInventoryComponent : public UActorComponent
{

	GENERATED_BODY()

public:	

	UInventoryComponent();

public:
	
	UPROPERTY(BlueprintAssignable)
	FOnInventoryChangedSignature OnInventoryChangedDelegate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<AItem*> Items;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(AItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropItem(AItem* Item);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool CanAddItem(AItem* Item);

	// Delegate Function Signature
	void OnInventoryChanged();
};
