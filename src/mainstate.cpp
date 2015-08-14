#include "mainstate.hpp"

MainState::MainState(fea::MessageBus& bus, fea::Renderer2D& renderer):
    mBus(bus),
    mRenderer(renderer)
{
}
