#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoryForge/Interactable.h"
#include "Item.generated.h"

UCLASS(Abstract)
class STORYFORGE_API AItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AItem();

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

public:

	// Fields

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UStaticMesh* WorldModel;

	/** Where the top-leftmost cell of the item is stored. Use -1,-1 if not in inventory */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FIntPoint InventoryLocation = FIntPoint(-1,-1);

	/** Size of the item in cells */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FIntPoint InventorySize = FIntPoint(1,1);

	/** Image that shows up in the inventory screen */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* InventoryImage;

	/** Image that shows up on the hotbar */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* HotbarImage;

	// Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AActor* CallingActor) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
	void UseItem();

	void UseItem_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Visibility")
	void SetItemEnabled(bool ItemEnabled);

	UFUNCTION(BlueprintPure, Category = "Appearance")
	FVector2D GetImageSize() const;

};
