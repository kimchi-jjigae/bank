#pragma once
#include "../behaviouralstate.hpp"

class CheckBState : public BehaviouralState
{
    public:
        CheckBState(fea::MessageBus& bus);
        void switchTo() override;
        void update() override;
        void onFinish() override;
        std::string getAnimationType();
};

