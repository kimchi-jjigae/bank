#include "mainstate.hpp"

MainState::MainState(fea::MessageBus& bus, fea::Renderer2D& renderer):
    mBus(bus),
    mRenderer(renderer)
{
}

void MainState::update()
{
    if(!mCurrentActivityState)
    {
        render();
    }
    else
    {
        mCurrentActivityState->update();
    }
}

void MainState::render()
{
    mRenderer.clear(fea::Color::Red);
}
