#pragma once

#include "CoreMinimal.h"

#include "StoryForge/Character/SFCharacter.h"
#include "StoryForge/Character/ClientMessage.h"
#include "StoryForge/SFDecoration.h"

#include "SFPlayer.generated.h"

UCLASS()
class STORYFORGE_API ASFPlayer : public ASFCharacter
{
	GENERATED_BODY()

	ASFPlayer();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decoration")
	TObjectPtr<ASFDecoration> HeldDecoration;
	
protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Logging")
	void AddClientMessage(FClientMessage ClientMessage);

	UFUNCTION(BlueprintPure, Category = "Item")
	bool CanEquipItem();

	UFUNCTION(BlueprintPure, Category = "Decoration")
	bool CanPickupDecoration();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Decoration")
	void PickupDecoration(ASFDecoration* DecorationActor);

	void PickupDecoration_Implementation(ASFDecoration* DecorationActor);

	UFUNCTION(BlueprintCallable, Category = "Decoration")
	TArray<FVector> GetActorBoundingBoxCorners(const AActor* Actor, float Padding);

	UFUNCTION(BlueprintCallable, Category = "Decoration")
	bool GetActorBoundsAsScreenCoords(AActor* Actor, APlayerController* PlayerController, float Padding, FVector2D& OutScreenPosition, FVector2D& OutScreenSize);

};
