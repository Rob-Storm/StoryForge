#pragma once

#include "CoreMinimal.h"
#include "MusicTrack.generated.h"

/**
 * Enums in one place for your development convienence
 */
UENUM(BlueprintType)
enum class EMusicTrack : uint8
{
	Ambient UMETA(DisplayName = "Ambient"),
	Death UMETA(DisplayName = "Death"),
	Combat UMETA(DisplayName = "Combat"),
	Conversation UMETA(DisplayName = "Conversation"),
	Outro UMETA(DisplayName = "Outro"),
};
