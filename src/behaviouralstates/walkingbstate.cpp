#include "walkingbstate.hpp"
#include <cmath>
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

    // working out the direction:
    float angle = (float)atan2(direction.y, direction.x);
    if(angle >= -0.75f * glm::pi<float>() && angle < -0.25f * glm::pi<float>())
    {
        // downwards
    }
    else if(angle >= -0.25f * glm::pi<float>() && angle < 0.25f * glm::pi<float>())
    {
        // right
    }
    else if(angle >= 0.25f * glm::pi<float>() && angle < 0.75f * glm::pi<float>())
    {
        // upwards
    }
    else
    {
        // left
    }

    glm::vec2 nextPos = charPos + mVelocity;
    mCharacter->setPosition(nextPos);
}

void WalkingBState::onFinish()
{
    //
}
