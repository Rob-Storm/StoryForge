#include "StoryForgeWorldSettings.h"


USoundBase* AStoryForgeWorldSettings::GetMusicFromEnum(EMusicTrack musicTrack) const
{
    switch (musicTrack)
    {
        case EMusicTrack::Ambient:
            return LevelMusic->AmbientTrack;
            break;
        case EMusicTrack::Death:
            return LevelMusic->DeathTrack;
            break;
        case EMusicTrack::Combat:
            return LevelMusic->ConversationTrack;
            break;
        case EMusicTrack::Conversation:
            return LevelMusic->ConversationTrack;
            break;
        case EMusicTrack::Outro:
            return LevelMusic->OutroTrack;
            break;
        default:
            return LevelMusic->AmbientTrack;
            break;
    }
}
