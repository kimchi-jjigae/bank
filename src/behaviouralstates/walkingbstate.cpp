#include "walkingbstate.hpp"

WalkingBState::WalkingBState(fea::MessageBus& bus, glm::vec2 targetPos, float speed) :
    BehaviouralState(bus),
    mSpeed(speed)
{
    mVelocity = glm::vec2(0.0f, 0.0f);
    mPositionDestination = targetPos;
    mAnimationType = "walking-front";
}

void WalkingBState::update()
{
    // work out velocity first
    glm::vec2 charPos = mCharacter->getPosition();
    glm::vec2 vel = mPositionDestination - charPos;
    vel = glm::normalize(vel);
    mVelocity = vel * mSpeed;
    glm::vec2 nextPos;
    nextPos = mCharacter->getPosition() + mVelocity;
    mCharacter->setPosition(nextPos);
}

void WalkingBState::onFinish()
{
    //
}
