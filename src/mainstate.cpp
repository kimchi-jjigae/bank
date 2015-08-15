#include "mainstate.hpp"
#include "messages.hpp"
#include "texturemaker.hpp"
#include "global.hpp"
#include "minigames.hpp"

MainState::MainState(fea::MessageBus& bus, fea::Renderer2D& renderer):
    mBus(bus),
    mRenderer(renderer),
    mInitialized(false),
    mQueueCounter(28),
    mPlayerQueueNumber(38),
    //rendering
    mBackground({1024.0f, 768.0f})
{
    subscribe(mBus, *this);
}

void MainState::setupGraphics()
{
    mRenderer.setup();

    mBackgroundTexture = makeTexture(gTextures.at("bank_bg"));
    mBackground.setTexture(mBackgroundTexture);
}

void MainState::update()
{
    if(!mInitialized)
        initialize();

    if(mCurrentActivityState)
    {
        mCurrentActivityState->update();

        if(mCurrentActivityState->isFinished())
            mCurrentActivityState = nullptr;
    }

    render();

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

void MainState::handleMessage(const StartMinigameMessage& message)
{
    auto& name = message.name;

    if(name == "outdoors")
    {
        mCurrentActivityState = std::unique_ptr<OutdoorsAState>(new OutdoorsAState(mBus, mRenderer));
    }
}

void MainState::render()
{
    mRenderer.clear();

    if(!mCurrentActivityState)
    {
        mRenderer.queue(mBackground);

        for(auto iter : mCharacters)
        {
            //mRenderer.queue(iter->getSprite());
        }
    }
    else
    {
        mCurrentActivityState->render();
    }

    mRenderer.render();
}

void MainState::initialize()
{
    mBus.send(PlayMusicMessage{"ambient_bank", false});
    mInitialized = true;
}
