#pragma once
#include "../behaviouralstate.hpp"

class TicketBState : public BehaviouralState
{
    public:
        TicketBState(fea::MessageBus& bus);
        void switchTo() override;
        void update() override;
        void onFinish() override;
        std::string getAnimationType();
};

