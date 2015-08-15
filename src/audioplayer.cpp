#include "audioplayer.hpp"

AudioPlayer::AudioPlayer(fea::MessageBus& bus) :
    mBus(bus)
{
    subscribe(mBus, *this);
}

void AudioPlayer::update()
{
    mAudioPlayer.update();
}

void AudioPlayer::handleMessage(const PlayMusicMessage& message)
{
}
