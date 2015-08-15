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
    
    glm::vec2 temp;
    temp = mCharacter->getPosition() + mVelocity;
    mCharacter->setPosition(temp);
}

void WalkingBState::onFinish()
{
    //
}
