#include "crosswordastate.hpp"
#include "global.hpp"
#include "messages.hpp"

CrosswordAState::CrosswordAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mCounter(600),
    mBackground({1024.0f, 768.0f})
{
    mBackgroundTexture = makeTexture(gTextures.at("crossword"));
    mBackground.setTexture(mBackgroundTexture);
}

void CrosswordAState::update()
{
    mCounter--;

    if(mCounter == 0)
    {
        mIsFinished = true;
        mBus.send(MissNumberMessage());
    }
}

void CrosswordAState::render()
{
    mRenderer.queue(mBackground);
}

void CrosswordAState::handleMouseMove(const glm::uvec2& position)
{
}

void CrosswordAState::handleMouseClick(const glm::uvec2& position)
{
    mIsFinished = true;
}
