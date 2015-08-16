#pragma once
#include "behaviouralstates/allbstates.hpp"
#include "character.hpp"
#include <fea/util.hpp>
#include <list>

class BehaviouralStateDelegator
{
    public:
        BehaviouralStateDelegator(fea::MessageBus& bus, std::list<Character>& characters);
        void playerWalk(glm::vec2 destination);

    private:
        fea::MessageBus& mBus;
        std::list<Character>& mCharacters;
        
};
