#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Sound/SoundBase.h"
#include "LevelMusicTracks.generated.h"

/**
 * Music tracks for each level
 */
UCLASS()
class STORYFORGE_API ULevelMusicTracks : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TObjectPtr<USoundBase>  AmbientTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TObjectPtr<USoundBase> DeathTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TObjectPtr<USoundBase> CombatTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TObjectPtr<USoundBase> ConversationTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TObjectPtr<USoundBase> OutroTrack;
};
