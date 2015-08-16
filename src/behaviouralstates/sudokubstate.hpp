#pragma once
#include "../behaviouralstate.hpp"

class SudokuBState : public BehaviouralState
{
    public:
        SudokuBState(fea::MessageBus& bus);
        void switchTo() override;
        void update() override;
        void onFinish() override;
        std::string getAnimationType();
};

