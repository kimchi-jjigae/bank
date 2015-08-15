#pragma once
#include "../behaviouralstate.hpp"

class IdleBState : public BehaviouralState
{
    public:
        IdleBState(fea::MessageBus& bus);
        void update();
};
