#include "global.hpp"

std::unordered_map<std::string, std::string> gTextures = {};

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
}
