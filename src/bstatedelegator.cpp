#include "bstatedelegator.hpp"

BehaviouralStateDelegator::BehaviouralStateDelegator(fea::MessageBus& bus, std::vector<Character>& characters) :
    mBus(bus),
    mCharacters(characters)
{
}

void BehaviouralStateDelegator::playerWalk(glm::vec2 destination)
{
    int hej = 0;
    hej++;
}
