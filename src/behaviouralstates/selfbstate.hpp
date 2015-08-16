#pragma once
#include "../behaviouralstate.hpp"

class SelfBState : public BehaviouralState
{
    public:
        SelfBState(fea::MessageBus& bus);
        void switchTo() override;
        void update() override;
        void onFinish() override;
        std::string getAnimationType();
};

