#include "outdoorbstate.hpp"
#include "../global.hpp"
#include "../messages.hpp"

OutdoorBState::OutdoorBState(fea::MessageBus& bus) :
    BehaviouralState(bus)
{
    mVelocity = glm::vec2(0.0f, 0.0f);
    mAnimationType = "idle-front";
    //mBus.sendMusicMessageThingy("idlemusic");
}

void OutdoorBState::switchTo()
{
    const fea::Animation& anim = getAnimation(mCharacter->mCharacterType, mAnimationType);
    mCharacter->getSprite().setAnimation(anim);
    mSwitchedTo = true;
}

void OutdoorBState::update()
{
    mFinished = true;
    onFinish();
}

void OutdoorBState::onFinish()
{
    mBus.send(StartMinigameMessage{"outdoors"});
}
