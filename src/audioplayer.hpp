#pragma once
#include <fea/audio.hpp>
#include <fea/util.hpp>
#include "messages.hpp"

class AudioPlayer :
    public fea::MessageReceiver<PlayMusicMessage>
{
    public:
        AudioPlayer(fea::MessageBus& bus);
        void update();
        void handleMessage(const PlayMusicMessage& message) override;
    private:
        fea::MessageBus& mBus;
        fea::AudioPlayer mAudioPlayer;
        fea::AudioFileStream mFileStream;
        fea::AudioHandle mMusicHandle;
        std::unordered_map<std::string, std::string> mAudioFiles;
};
