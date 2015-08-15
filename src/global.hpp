#pragma once
#include <string>
#include <unordered_map>
#include "texturemaker.hpp"

extern std::unordered_map<std::string, std::string> gTextures;
extern std::unordered_map<std::string, std::unordered_map<std::string, fea::Animation>> gAnimations;

void setupGlobals();
const fea::Animation& getAnimation(const std::string& character, const std::string& animation);
