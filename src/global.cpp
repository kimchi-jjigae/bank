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
    };
}
