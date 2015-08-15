#pragma once
#include "behaviouralstates/allbstates.hpp"
#include <fea/util.hpp>

class BehaviouralStateDelegator
{
    public:
        BehaviouralStateDelegator(fea::MessageBus& bus);

    private:
        fea::MessageBus& mBus;
};
