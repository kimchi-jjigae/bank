#include "animator.hpp"

Animator::Animator() :
    mAnimations(
    {
        {
            "player", 
            {
                { "idle", fea::Animation(glm::vec2(0.0f, 0.0f), glm::vec2(28.0f / 112.0f, 18.0f / 18.0f), 4, 8) }
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
