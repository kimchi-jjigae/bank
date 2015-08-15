#include "bstatedelegator.hpp"
#include <iostream>

BehaviouralStateDelegator::BehaviouralStateDelegator(fea::MessageBus& bus, std::vector<Character>& characters) :
    mBus(bus),
    mCharacters(characters)
{
}

void BehaviouralStateDelegator::playerWalk(glm::vec2 destination)
{
    std::deque<std::shared_ptr<BehaviouralState>>& behaviours = mCharacters.at(0).getBehaviouralStates();
    behaviours.clear();
    std::shared_ptr<WalkingBState> walkState = std::make_shared<WalkingBState>(mBus, destination, 3.0f);
    walkState->setOwner(&mCharacters.at(0));
    std::shared_ptr<IdleBState> idleState = std::make_shared<IdleBState>(mBus);
    idleState->setOwner(&mCharacters.at(0));
    behaviours.push_back(walkState);
    behaviours.push_back(idleState);
}
