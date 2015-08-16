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
    std::cout << "old posnext: " << charPos << "\n";
    glm::vec2 vel = mPositionDestination - charPos;
    vel = glm::normalize(vel);
    mVelocity = vel * mSpeed;
    glm::vec2 nextPos;
    nextPos = charPos + mVelocity;
    mCharacter->setPosition(nextPos);

    std::cout << "vel: " << mVelocity << "\n";
    std::cout << "old pos: " << charPos << "\n";
    std::cout << "pos: " << mCharacter->getPosition() << "\n";
}

void WalkingBState::onFinish()
{
    //
}
