#include "mainstate.hpp"
#include "messages.hpp"

MainState::MainState(fea::MessageBus& bus, fea::Renderer2D& renderer):
    mBus(bus),
    mRenderer(renderer),
    mInitialized(false),
    counter(0)
{
}

void MainState::update()
{
    if(!mInitialized)
        initialize();

    if(!mCurrentActivityState)
    {
        render();
    }
    else
    {
        mCurrentActivityState->update();
    }

    counter++;

    if(counter % 100 == 0)
        mBus.send(PlaySoundMessage{"turn_page", false});
}

void MainState::render()
{
    mRenderer.clear(fea::Color::Red);
}

void MainState::initialize()
{
    mBus.send(PlayMusicMessage{"ambient_bank", false});
    mInitialized = true;
}
