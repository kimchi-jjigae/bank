#include "mainstate.hpp"
#include "messages.hpp"

MainState::MainState(fea::MessageBus& bus, fea::Renderer2D& renderer):
    mBus(bus),
    mRenderer(renderer),
    mInitialized(false)
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
}

void MainState::render()
{
    mRenderer.clear(fea::Color::Red);
    for(auto iter : mCharacters)
    {
        //mRenderer.queue(iter->getSprite());
    }
    mRenderer.render();
}

void MainState::initialize()
{
    mBus.send(PlayMusicMessage{"ambient_bank", true});
    mInitialized = true;
}
