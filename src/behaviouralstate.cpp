#include "behaviouralstate.hpp"

BehaviouralState::BehaviouralState(fea::MessageBus& bus) :
    mBus(bus)
{
}

std::string BehaviouralState::getAnimationType()
{
    return mAnimationType;
}

void BehaviouralState::setOwner(Character* character)
{
    mCharacter = character;
}
