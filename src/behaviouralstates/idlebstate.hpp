#pragma once
#include "../behaviouralstate.hpp"

class IdleBState : public BehaviouralState
{
    public:
        IdleBState(fea::MessageBus& bus);
        void switchTo() override;
        void update() override;
        void onFinish() override;
        std::string getAnimationType();
};
