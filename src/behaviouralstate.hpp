#pragma once
#include "glm.hpp"
#include <fea/util.hpp>
#include <string>

class BehaviouralState
{
    public:
        BehaviouralState(fea::MessageBus& bus);
        virtual void update() = 0;

    protected:
        glm::vec2 mPositionDestination;
        glm::vec2 mVelocity;
        std::string mAnimationType;
        fea::MessageBus& mBus;
};
