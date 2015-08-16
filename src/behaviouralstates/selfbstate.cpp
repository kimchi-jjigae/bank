#include "selfbstate.hpp"
#include "../global.hpp"
#include "../messages.hpp"

SelfBState::SelfBState(fea::MessageBus& bus) :
    BehaviouralState(bus)
{
    mVelocity = glm::vec2(0.0f, 0.0f);
    mAnimationType = "idle-front";
    //mBus.sendMusicMessageThingy("idlemusic");
}

void SelfBState::switchTo()
{
    const fea::Animation& anim = getAnimation(mCharacter->mCharacterType, mAnimationType);
    mCharacter->getSprite().setAnimation(anim);
    mSwitchedTo = true;
}

void SelfBState::update()
{
    mFinished = true;
    onFinish();
}

void SelfBState::onFinish()
{
    //mBus.send(StartMinigameMessage{"take_ticket"});
    mBus.send(StartMinigameMessage{"viewnote"});
}
