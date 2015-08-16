#include "checkbstate.hpp"
#include "../global.hpp"
#include "../messages.hpp"

CheckBState::CheckBState(fea::MessageBus& bus) :
    BehaviouralState(bus)
{
    mVelocity = glm::vec2(0.0f, 0.0f);
    mAnimationType = "idle-front";
    //mBus.sendMusicMessageThingy("idlemusic");
}

void CheckBState::switchTo()
{
    const fea::Animation& anim = getAnimation(mCharacter->mCharacterType, mAnimationType);
    mCharacter->getSprite().setAnimation(anim);
    mSwitchedTo = true;
}

void CheckBState::update()
{
    mFinished = true;
    onFinish();
}

void CheckBState::onFinish()
{
    //mBus.send(StartMinigameMessage{"take_ticket"});
    mBus.send(StartMinigameMessage{"cheque"});
}
