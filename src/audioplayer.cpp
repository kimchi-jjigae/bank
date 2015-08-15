#include "audioplayer.hpp"

AudioPlayer::AudioPlayer(fea::MessageBus& bus) :
    mBus(bus),
    mMusicHandle(0),
    mAudioFiles(
    {
        {"ambient_bank", "data/music/Ambankient.ogg"}
    })
{
    subscribe(mBus, *this);
}

void AudioPlayer::update()
{
    mAudioPlayer.update();
}

void AudioPlayer::handleMessage(const PlayMusicMessage& message)
{
    FEA_ASSERT(mAudioFiles.count(message.name) > 0, "music file " + message.name + " not found!");
    mFileStream.openFile(mAudioFiles.at(message.name));
    mAudioPlayer.stop(mMusicHandle);
    mMusicHandle = mAudioPlayer.play(mFileStream);

    mAudioPlayer.setLooping(mMusicHandle, message.loop);
}
