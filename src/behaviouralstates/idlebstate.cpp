#include "idlebstate.hpp"
#include "../global.hpp"

IdleBState::IdleBState(fea::MessageBus& bus) :
    BehaviouralState(bus)
{
    mVelocity = glm::vec2(0.0f, 0.0f);
    mAnimationType = "idle-front";
    //mBus.sendMusicMessageThingy("idlemusic");
}

void IdleBState::switchTo()
{
    const fea::Animation& anim = getAnimation("player", mAnimationType);
    mCharacter->getSpriteRef().setAnimation(anim);
    mSwitchedTo = true;
}

void IdleBState::update()
{
}

void IdleBState::onFinish()
{
    //
}
