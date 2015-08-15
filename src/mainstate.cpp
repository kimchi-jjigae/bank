#include "mainstate.hpp"
#include "messages.hpp"

MainState::MainState(fea::MessageBus& bus, fea::Renderer2D& renderer):
    mBus(bus),
    mRenderer(renderer),
    mInitialized(false),
    mQueueCounter(28),
    mPlayerQueueNumber(38)
{
    subscribe(mBus, *this);
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

    if(rand() % 100 == 0)
        mBus.send(AdvanceQueueMessage());
}

void MainState::handleMessage(const AdvanceQueueMessage& message)
{
    mQueueCounter++;

    if(mQueueCounter > 99)
        mQueueCounter = 0;

    mBus.send(PlaySoundMessage{"queue_ding", false});
}

void MainState::handleMessage(const MissNumberMessage& message)
{
    mQueueCounter = mPlayerQueueNumber + 1;

    if(mQueueCounter > 99)
        mQueueCounter = 0;

    mBus.send(PlaySoundMessage{"queue_ding", false});
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
