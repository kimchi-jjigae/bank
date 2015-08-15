#pragma once
#include "../behaviouralstate.hpp"

class WalkingBState : public BehaviouralState
{
    public:
        WalkingBState(fea::MessageBus& bus, glm::vec2 targetPos);
        void update();
        void onFinish();
        std::string getAnimationType();
};
