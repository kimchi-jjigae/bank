#include "cashierbstate.hpp"
#include "../global.hpp"
#include "../messages.hpp"

CashierBState::CashierBState(fea::MessageBus& bus) :
    BehaviouralState(bus)
{
    mVelocity = glm::vec2(0.0f, 0.0f);
    mAnimationType = "idle-front";
    //mBus.sendMusicMessageThingy("idlemusic");
}

void CashierBState::switchTo()
{
    const fea::Animation& anim = getAnimation(mCharacter->mCharacterType, mAnimationType);
    mCharacter->getSprite().setAnimation(anim);
    mSwitchedTo = true;
}

void CashierBState::update()
{
    mFinished = true;
    onFinish();
}

void CashierBState::onFinish()
{
    mBus.send(StartMinigameMessage{"runerrand"});
}
