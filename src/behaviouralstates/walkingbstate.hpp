#pragma once
#include "../behaviouralstate.hpp"

class WalkingBState : public BehaviouralState
{
    public:
        WalkingBState(fea::MessageBus& bus, glm::vec2 targetPos, float speed);
        void switchTo();
        void update();
        void onFinish();
        std::string getAnimationType();

    private:
        float mSpeed;
};
