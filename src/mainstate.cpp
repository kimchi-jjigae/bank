#include "mainstate.hpp"

MainState::MainState(fea::MessageBus& bus, fea::Renderer2D& renderer):
    mBus(bus),
    mRenderer(renderer)
{
}

void MainState::update()
{
    render();
}

void MainState::render()
{
    mRenderer.clear(fea::Color::Red);
}
