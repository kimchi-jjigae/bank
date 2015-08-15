#include "bstatedelegator.hpp"

BehaviouralStateDelegator::BehaviouralStateDelegator(fea::MessageBus& bus, std::vector<Character>& characters) :
    mBus(bus),
    mCharacters(characters)
{
}

void BehaviouralStateDelegator::playerWalk(glm::vec2 destination)
{
    std::queue<std::shared_ptr<BehaviouralState>>& behaviours = mCharacters.at(0).getBehaviouralStates();
    behaviours.empty();
}
