#pragma once
#include <fea/rendering/animation.hpp>
#include <string>
#include <unordered_map>
#include "glm.hpp"

class Animator
{
    public:
        Animator();
        const fea::Animation& getAnimation(std::string character, std::string animation);

    private:
        std::unordered_map<std::string, std::unordered_map<std::string, fea::Animation>> mAnimations;
};
