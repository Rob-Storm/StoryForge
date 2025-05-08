#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeEvent.h"
#include "GameFramework/Actor.h"
#include "DialogueEventCameraAngle.generated.h"

/**
 * Changes the camera angle based on an enum value
 */

UENUM(BlueprintType)
enum class ECameraAngle : uint8
{
	SideTight UMETA(DisplayName = "SideTight"),
	SideMid UMETA(DisplayName = "SideMid"),
	AboveDown UMETA(DisplayName = "AboveDown"),
	BelowUp UMETA(DisplayName = "BelowUp"),
	HeadTight UMETA(DisplayName = "HeadTight"),
	HeadMid UMETA(DisplayName = "HeadMid")
};

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class STORYFORGE_API UDialogueEventCameraAngle : public UDialogueNodeEvent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Angle")
	ECameraAngle CameraAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Angle", meta = (EditCondition = "!TargetIsPlayer", EditConditionHides))
	TSoftObjectPtr<AActor> Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Angle")
	bool TargetIsPlayer;
};