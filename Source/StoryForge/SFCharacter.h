#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InventoryComponent.h"
#include "SFCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDieSignature);

UCLASS()
class STORYFORGE_API ASFCharacter : public ACharacter
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
	UAnimationAsset* DeathAnimation;


	// Components

	// Make sure you use VisbleAnywhere for components!!
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UInventoryComponent* InventoryComponent;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health")
	void Die();

	void Die_Implementation();
};
