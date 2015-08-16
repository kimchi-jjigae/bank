#pragma once
#include "../behaviouralstate.hpp"

class CashierBState : public BehaviouralState
{
    public:
        CashierBState(fea::MessageBus& bus);
        void switchTo() override;
        void update() override;
        void onFinish() override;
        std::string getAnimationType();
};

