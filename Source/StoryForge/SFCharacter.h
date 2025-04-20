#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InventoryComponent.h"
#include "SFCharacter.generated.h"

UCLASS()
class STORYFORGE_API ASFCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ASFCharacter();

public:

	// Fields



	// Components

	// Make sure you use VisbleAnywhere for components!!
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UInventoryComponent* InventoryComponent;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
