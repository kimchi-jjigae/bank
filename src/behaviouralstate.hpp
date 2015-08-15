#pragma once
#include "glm.hpp"
#include "character.hpp"
#include <fea/util.hpp>
#include <string>

class BehaviouralState
{
    public:
        BehaviouralState(fea::MessageBus& bus);
        virtual void update() = 0;
        virtual void onFinish() = 0;
        std::string getAnimationType();
        void setOwner(Character* character);
        bool mSwitchedTo;
        virtual void switchTo() = 0;

    protected:
        fea::MessageBus& mBus;
        Character* mCharacter;
        glm::vec2 mPositionDestination;
        glm::vec2 mVelocity;
        std::string mAnimationType;
};
