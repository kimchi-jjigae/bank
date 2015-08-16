#pragma once
#include "../behaviouralstate.hpp"

class OutdoorBState : public BehaviouralState
{
    public:
        OutdoorBState(fea::MessageBus& bus);
        void switchTo() override;
        void update() override;
        void onFinish() override;
        std::string getAnimationType();
};

