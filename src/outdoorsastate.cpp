#include "outdoorsastate.hpp"
#include "global.hpp"

OutdoorsAState::OutdoorsAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mCounter(50),
    mBackground({1024.0f, 768.0f})
{
    mBackgroundTexture = makeTexture(gTextures.at("outside"));
    mBackground.setTexture(mBackgroundTexture);
}

void OutdoorsAState::update()
{
    mCounter--;

    if(mCounter == 0)
        mIsFinished = true;
}

void OutdoorsAState::render()
{
    mRenderer.queue(mBackground);
}
