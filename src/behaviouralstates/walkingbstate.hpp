#pragma once
#include "../behaviouralstate.hpp"

enum Direction {
    FORWARDS = 0,
    BACKWARDS,
    LEFTWARDS,
    RIGHTWARDS
};

class WalkingBState : public BehaviouralState
{
    public:
        WalkingBState(fea::MessageBus& bus, glm::vec2 targetPos, float speed);
        void switchTo() override;
        void update() override;
        void onFinish() override;
        std::string getAnimationType();

    private:
        float mSpeed;
};
