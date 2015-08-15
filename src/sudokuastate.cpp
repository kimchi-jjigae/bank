#include "sudokuastate.hpp"
#include "global.hpp"
#include "messages.hpp"

SudokuAState::SudokuAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mCounter(600),
    mBackground({1024.0f, 768.0f})
{
    mBackgroundTexture = makeTexture(gTextures.at("sudoku"));
    mBackground.setTexture(mBackgroundTexture);
}

void SudokuAState::update()
{
    mCounter--;

    if(mCounter == 0)
    {
        mIsFinished = true;
        mBus.send(MissNumberMessage());
    }
}

void SudokuAState::render()
{
    mRenderer.queue(mBackground);
}

void SudokuAState::handleMouseMove(const glm::uvec2& position)
{
}

void SudokuAState::handleMouseClick(const glm::uvec2& position)
{
    mIsFinished = true;
}
