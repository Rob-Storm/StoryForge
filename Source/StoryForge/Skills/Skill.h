#pragma once

#include "CoreMinimal.h"

#include "Skill.generated.h"

UENUM(BlueprintType)
enum class ESkillLevel : uint8
{
	Untrained UMETA(DisplayName = "Untrained"),
	Trained UMETA(DisplayName = "Trained"),
	Advanced UMETA(DisplayName = "Advanced"),
	Master UMETA(DisplayName = "Master"),
};

/**
 * Base skill class
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class STORYFORGE_API USkill : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	ESkillLevel SkillLevel;

};