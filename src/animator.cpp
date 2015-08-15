#include "animator.hpp"

Animator::Animator() :
    mAnimations({
    {
        "player", 
        {
            { "idle", fea::Animation(glm::vec2(0.0f, 0.0f), glm::vec2(28.0f / 112.0f, 18.0f / 18.0f), 4, 8) }
        }
    }
    })
{
}

const fea::Animation& Animator::getAnimation(std::string character, std::string animation)
{
    // what if it doesn't exist?
    return mAnimations.at(character).at(animation);
}
