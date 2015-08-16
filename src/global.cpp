#include "global.hpp"

std::unordered_map<std::string, std::string> gTextures = {};
std::unordered_map<std::string, std::unordered_map<std::string, fea::Animation>> gAnimations = {};
bool gPaintingRuined = false;
bool gMenuOver = false;

void setupGlobals()
{
    gTextures = 
    {
        {"player", "data/sprites/player.png"},
        {"sudoku", "data/sprites/sudoku.png"},
        {"pillar", "data/sprites/pillar.png"},
        {"outside", "data/sprites/Outside.png"},
        {"bank_bg_b", "data/sprites/bg_back.png"},
        {"bank_bg_f", "data/sprites/bg_front.png"},
        {"bank_mask", "data/sprites/mask.png"},
        {"crossword", "data/sprites/crossword.png"},
        {"say_button", "data/sprites/sayButton.png"},
        {"back_button", "data/sprites/backButton.png"},
        {"childquestion", "data/sprites/childquestion.png"},
        {"heartattack_bg", "data/sprites/heartattack.png"},
        {"ticket_machine", "data/sprites/ticketmachine.png"},
        {"number_texture", "data/sprites/numbers.png"},
        {"sad_mouth", "data/sprites/sadmouth.png"},
        {"arm_up", "data/sprites/heartattackarmup.png"},
        {"arm_down", "data/sprites/heartattackarmdown.png"},
        {"explosion", "data/sprites/explosion.png"},
        {"whiteboard", "data/sprites/whiteboard.png"},
        {"painting", "data/sprites/tavla.png"},
        {"bin", "data/sprites/bin.png"},
        {"sofa", "data/sprites/sofa.png"},
        {"wallpainting", "data/sprites/wallpainting.png"},
        {"menubg", "data/sprites/menu.png"},
        {"menubutton", "data/sprites/menubutton.png"},
    };

    gAnimations = 
    {
        {
            "player", 
            {
                {"idle-front",    fea::Animation(glm::vec2(0.0f, (0.0f * 172.0f)/860.0f), glm::vec2(53.0f/215.0f, 172.0f/860.0f), 4, 8)},
                {"walking-front", fea::Animation(glm::vec2(0.0f, (1.0f * 172.0f)/860.0f), glm::vec2(53.0f/215.0f, 172.0f/860.0f), 4, 8)},
                {"walking-left",  fea::Animation(glm::vec2(0.0f, (2.0f * 172.0f)/860.0f), glm::vec2(53.0f/215.0f, 172.0f/860.0f), 4, 8)},
                {"walking-right", fea::Animation(glm::vec2(0.0f, (3.0f * 172.0f)/860.0f), glm::vec2(53.0f/215.0f, 172.0f/860.0f), 4, 8)},
                {"idle-back",     fea::Animation(glm::vec2(0.0f, (4.0f * 172.0f)/860.0f), glm::vec2(53.0f/215.0f, 172.0f/860.0f), 1, 8)},
            },
        },
        {
            "ticket_machine", 
            {
                {"idle-front",    fea::Animation(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), 1, 8)},
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
