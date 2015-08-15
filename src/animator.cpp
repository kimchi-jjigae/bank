#include "animator.hpp"

Animator::Animator() :
    mAnimations(
    {
        {
            "player", 
            {
                {"idle-front",    fea::Animation(glm::vec2(0.0f,    0.0f), glm::vec2(124.0f / 496.0f, 396.0f / 1980.0f), 1, 8)},
                {"walking-front", fea::Animation(glm::vec2(0.0f,  778.0f), glm::vec2(124.0f / 496.0f, 396.0f / 1980.0f), 4, 8)},
                {"walking-left",  fea::Animation(glm::vec2(0.0f, 1167.0f), glm::vec2(124.0f / 496.0f, 396.0f / 1980.0f), 4, 8)},
                {"walking-right", fea::Animation(glm::vec2(0.0f, 1556.0f), glm::vec2(124.0f / 496.0f, 396.0f / 1980.0f), 4, 8)},
                {"idle-back",     fea::Animation(glm::vec2(0.0f,  389.0f), glm::vec2(124.0f / 496.0f, 396.0f / 1980.0f), 1, 8)},
            },
        },
        {
            "number", 
            {
                {"0", fea::Animation(glm::vec2((0.0f * 26.0f) / 260.0f, 0.0f), glm::vec2(26.0f / 260.0f, 1.0f), 1, 1)},
                {"1", fea::Animation(glm::vec2((1.0f * 26.0f) / 260.0f, 0.0f), glm::vec2(26.0f / 260.0f, 1.0f), 1, 1)},
                {"2", fea::Animation(glm::vec2((2.0f * 26.0f) / 260.0f, 0.0f), glm::vec2(26.0f / 260.0f, 1.0f), 1, 1)},
                {"3", fea::Animation(glm::vec2((3.0f * 26.0f) / 260.0f, 0.0f), glm::vec2(26.0f / 260.0f, 1.0f), 1, 1)},
                {"4", fea::Animation(glm::vec2((4.0f * 26.0f) / 260.0f, 0.0f), glm::vec2(26.0f / 260.0f, 1.0f), 1, 1)},
                {"5", fea::Animation(glm::vec2((5.0f * 26.0f) / 260.0f, 0.0f), glm::vec2(26.0f / 260.0f, 1.0f), 1, 1)},
                {"6", fea::Animation(glm::vec2((6.0f * 26.0f) / 260.0f, 0.0f), glm::vec2(26.0f / 260.0f, 1.0f), 1, 1)},
                {"7", fea::Animation(glm::vec2((7.0f * 26.0f) / 260.0f, 0.0f), glm::vec2(26.0f / 260.0f, 1.0f), 1, 1)},
                {"8", fea::Animation(glm::vec2((8.0f * 26.0f) / 260.0f, 0.0f), glm::vec2(26.0f / 260.0f, 1.0f), 1, 1)},
                {"9", fea::Animation(glm::vec2((9.0f * 26.0f) / 260.0f, 0.0f), glm::vec2(26.0f / 260.0f, 1.0f), 1, 1)}
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
