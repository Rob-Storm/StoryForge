#pragma once

#include "CoreMinimal.h"
#include "SFCharacter.h"

#include "ClientMessage.h"

#include "SFPlayer.generated.h"

UCLASS()
class STORYFORGE_API ASFPlayer : public ASFCharacter
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Logging")
	void AddClientMessage(FClientMessage ClientMessage);
};
