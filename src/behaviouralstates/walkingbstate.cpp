#include "walkingbstate.hpp"
#include "../global.hpp"

WalkingBState::WalkingBState(fea::MessageBus& bus, glm::vec2 targetPos, float speed) :
    BehaviouralState(bus),
    mSpeed(speed)
{
    mVelocity = glm::vec2(0.0f, 0.0f);
    mPositionDestination = targetPos;
    mAnimationType = "walking-front";
}

void WalkingBState::switchTo()
{
    const fea::Animation& anim = getAnimation("player", mAnimationType);
    mCharacter->getSpriteRef().setAnimation(anim);
    mSwitchedTo = true;
}

void WalkingBState::update()
{
    glm::vec2 charPos = mCharacter->getPosition();
    glm::vec2 direction = mPositionDestination - charPos;
    direction = glm::normalize(direction);
    mVelocity = direction * mSpeed;

    glm::vec2 nextPos = charPos + mVelocity;
    mCharacter->setPosition(nextPos);
}

void WalkingBState::onFinish()
{
    //
}
