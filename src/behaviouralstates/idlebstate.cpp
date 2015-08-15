#include "idlebstate.hpp"

IdleBState::IdleBState(fea::MessageBus& bus) :
    BehaviouralState(bus)
{
    mVelocity = glm::vec2(0.0f, 0.0f);
    mAnimationType = "idle-front";
    //mBus.sendMusicMessageThingy("idlemusic");
}

void IdleBState::switchTo()
{
    anim = getAnimation("player", mAnimationType);
    mCharacter->getSprite.setAnimation(anim);
    mSwitchedTo = true;
}

void IdleBState::update()
{
    // nothing happens, I guess
}

void IdleBState::onFinish()
{
    //
}
