#include "outdoorsastate.hpp"
#include "global.hpp"
#include "messages.hpp"

OutdoorsAState::OutdoorsAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mCounter(600),
    mBackground({1024.0f, 768.0f})
{
    mBackgroundTexture = makeTexture(gTextures.at("outside"));
    mBackground.setTexture(mBackgroundTexture);
}

void OutdoorsAState::update()
{
    mCounter--;

    if(mCounter == 0)
    {
        mIsFinished = true;
        mBus.send(MissNumberMessage());
    }
}

void OutdoorsAState::render()
{
    mRenderer.queue(mBackground);
}

void OutdoorsAState::handleMouseMove(const glm::uvec2& position)
{
}

void OutdoorsAState::handleMouseClick(const glm::uvec2& position)
{
    mIsFinished = true;
}

void OutdoorsAState::handleMouseRelease(const glm::uvec2& position)
{
}
