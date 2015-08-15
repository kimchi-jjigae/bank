#include "global.hpp"

std::unordered_map<std::string, std::string> gTextures = {};

void setupGlobals()
{
    gTextures = 
    {
        {"bank_bg", "data/sprites/bank.png"},
        {"outside", "data/sprites/Outside.png"},
        {"crossword", "data/sprites/crossword.png"},
        {"sudoku", "data/sprites/sudoku.png"},
        {"player", "data/sprites/gubbe.png"},
        {"number_texture", "data/sprites/numbers.png"},
    };
}
