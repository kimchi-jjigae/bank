#pragma once
#include "../behaviouralstate.hpp"

class CrosswordBState : public BehaviouralState
{
    public:
        CrosswordBState(fea::MessageBus& bus);
        void switchTo() override;
        void update() override;
        void onFinish() override;
        std::string getAnimationType();
};

