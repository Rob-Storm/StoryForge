#pragma once

#include "CoreMinimal.h"
#include "ClientMessage.generated.h"

UENUM(BlueprintType)
enum class EClientMessageUrgency : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Positive UMETA(DisplayName = "Positive"),
	Negative UMETA(DisplayName = "Negative")
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FClientMessage
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Message;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Lifetime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EClientMessageUrgency Type;

};
