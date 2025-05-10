#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "StoryForge/Interactable.h"
#include "StoryForge/Item/InventoryComponent.h"
#include "StoryForge/Dialogue/DialogueAsset.h"

#include "SFCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDieSignature);

UCLASS()
class STORYFORGE_API ASFCharacter : public ACharacter, public IInteractable
{
	GENERATED_BODY()

public:

	ASFCharacter();

public:

	//Delegates

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDieSignature OnDie;


	// Fields

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RunSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	TObjectPtr<UAnimationAsset> DeathAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<AItem> CurrentItem;


	// Conversations and Dialogue

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TObjectPtr<UDialogueAsset> Conversation;

	// Barks

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barks")
	TObjectPtr<USoundBase> BarkPlayerInteraction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barks")
	TObjectPtr<USoundBase> BarkPlayerSight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barks")
	TObjectPtr<USoundBase> BarkInjured;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Barks")
	TObjectPtr<USoundBase> BarkFlee;


	// Components

	// Make sure you use VisbleAnywhere for components!!
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UInventoryComponent* InventoryComponent;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Interact_Implementation(AActor* CallingActor) override;

	UFUNCTION(BlueprintPure, Category = "Dialogue")
	bool CanTalk();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
	void SetCurrentItem(AItem* Item);

	void SetCurrentItem_Implementation(AItem* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health")
	void Die();

	void Die_Implementation();
};
