#include "walkingbstate.hpp"

WalkingBState::WalkingBState(fea::MessageBus& bus, glm::vec2 targetPos) :
    BehaviouralState(bus)
{
    mVelocity = glm::vec2(0.0f, 0.0f);
    mPositionDestination = targetPos;
    mAnimationType = "walking-front";
}

void WalkingBState::update()
{
    
}

void WalkingBState::onFinish()
{
    //
}
