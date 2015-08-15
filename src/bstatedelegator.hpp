#pragma once
#include "behaviouralstates/allbstates.hpp"
#include "character.hpp"
#include <fea/util.hpp>

class BehaviouralStateDelegator
{
    public:
        BehaviouralStateDelegator(fea::MessageBus& bus, std::vector<Character>& characters);
        void playerWalk(glm::vec2 destination);

    private:
        fea::MessageBus& mBus;
        std::vector<Character>& mCharacters;
        
};
