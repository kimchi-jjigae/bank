#pragma once
#include "../behaviouralstate.hpp"

class PaintingBState : public BehaviouralState
{
    public:
        PaintingBState(fea::MessageBus& bus);
        void switchTo() override;
        void update() override;
        void onFinish() override;
        std::string getAnimationType();
};

