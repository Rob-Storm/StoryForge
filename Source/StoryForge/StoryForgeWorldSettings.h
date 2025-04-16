#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "GameplayEnums.h"
#include "LevelMusicTracks.h"

#include "StoryForgeWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class STORYFORGE_API AStoryForgeWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Music")
	TObjectPtr<ULevelMusicTracks> LevelMusic;

public:

	UFUNCTION(BlueprintPure, Category = "Music")
	USoundBase* GetMusicFromEnum(EMusicTrack musicTrack) const;

};
