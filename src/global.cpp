#include "global.hpp"

std::unordered_map<std::string, std::string> gTextures = {};
std::unordered_map<std::string, std::unordered_map<std::string, fea::Animation>> gAnimations = {};

void setupGlobals()
{
    gTextures = 
    {
        {"bank_bg", "data/sprites/bank.png"},
        {"outside", "data/sprites/Outside.png"},
        {"player", "data/sprites/player.png"},
        {"crossword", "data/sprites/crossword.png"},
        {"sudoku", "data/sprites/sudoku.png"},
        {"number_texture", "data/sprites/numbers.png"},
        {"childquestion", "data/sprites/childquestion.png"},
        {"back_button", "data/sprites/backButton.png"},
        {"say_button", "data/sprites/sayButton.png"},
        {"sad_mouth", "data/sprites/sadmouth.png"},
        {"heartattack_bg", "data/sprites/heartattack.png"},
        {"arm_up", "data/sprites/heartattackarmup.png"},
        {"arm_down", "data/sprites/heartattackarmdown.png"},
        {"explosion", "data/sprites/explosion.png"},
    };

    gAnimations = 
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
   };
}

const fea::Animation& getAnimation(const std::string& character, const std::string& animation)
{
    // what if it doesn't exist?
    return gAnimations.at(character).at(animation);
}
