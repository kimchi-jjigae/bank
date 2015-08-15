#include "mainstate.hpp"
#include "messages.hpp"
#include "behaviouralstates/allbstates.hpp"
#include "texturemaker.hpp"
#include "global.hpp"
#include "minigames.hpp"
#include "animator.hpp"

MainState::MainState(fea::MessageBus& bus, fea::Renderer2D& renderer):
    mBus(bus),
    mRenderer(renderer),
    mInitialized(false),
    mQueueCounter(28),
    mPlayerQueueNumber(38),
    //rendering
    mBackground({1024.0f, 768.0f}),
    mFirstNumber({26.0f, 40.0f}),
    mSecondNumber({26.0f, 40.0f}),
    mBStateDelegator(bus, mCharacters)
{
    subscribe(mBus, *this);
}

void MainState::setupGraphics()
{
    mRenderer.setup();

    mBackgroundTexture = makeTexture(gTextures.at("bank_bg"));
    mBackground.setTexture(mBackgroundTexture);
    
    mPlayerTexture = makeTexture(gTextures.at("player"));
    mNumberTexture = makeTexture(gTextures.at("number_texture"));

    mFirstNumber.setTexture(mNumberTexture);
    mSecondNumber.setTexture(mNumberTexture);

    mFirstNumber.setPosition({464.0f, 89.0f});
    mSecondNumber.setPosition({492.0f, 89.0f});

    Animator animator;

    mFirstNumber.setAnimation(animator.getAnimation("number", "4"));
    mSecondNumber.setAnimation(animator.getAnimation("number", "5"));

    updateNumbers();
}

void MainState::update()
{
    if(!mInitialized)
        initialize();

    if(mCurrentActivityState)
    {
        mCurrentActivityState->update();
        for(auto iter : mCharacters)
        {
            iter.update();
        }

        if(mCurrentActivityState->isFinished())
            mCurrentActivityState = nullptr;
    }
    else
    {
        for(auto iter : mCharacters)
        {
            iter.update();
        }

    }

    render();

    if(!mCurrentActivityState)
    {
        if(rand() % 1000 == 0)
            mBus.send(AdvanceQueueMessage());
    }
}

void MainState::handleMessage(const AdvanceQueueMessage& message)
{
    mQueueCounter++;

    if(mQueueCounter > 99)
        mQueueCounter = 0;

    mBus.send(PlaySoundMessage{"queue_ding", false});

    updateNumbers();
}

void MainState::handleMessage(const MissNumberMessage& message)
{
    if(mQueueCounter <= mPlayerQueueNumber)
        mQueueCounter = mPlayerQueueNumber + 1;
    else
        mQueueCounter++;

    if(mQueueCounter > 99)
        mQueueCounter = 0;

    mBus.send(PlaySoundMessage{"queue_ding", false});

    updateNumbers();
}

void MainState::handleMessage(const StartMinigameMessage& message)
{
    auto& name = message.name;

    if(name == "outdoors")
        mCurrentActivityState = std::unique_ptr<OutdoorsAState>(new OutdoorsAState(mBus, mRenderer));
    else if(name == "crossword")
        mCurrentActivityState = std::unique_ptr<CrosswordAState>(new CrosswordAState(mBus, mRenderer));
    else if(name == "sudoku")
        mCurrentActivityState = std::unique_ptr<SudokuAState>(new SudokuAState(mBus, mRenderer));
    else if(name == "childquestion")
        mCurrentActivityState = std::unique_ptr<ChildQuestionAState>(new ChildQuestionAState(mBus, mRenderer));
}

void MainState::handleMessage(const MouseMoveMessage& message)
{
    if(mCurrentActivityState)
    {
        mCurrentActivityState->handleMouseMove(message.position);
    }
    else
    {
        //behav deleg?
    }
}

void MainState::handleMessage(const MouseClickMessage& message)
{
    if(mCurrentActivityState)
    {
        mCurrentActivityState->handleMouseClick(message.position);
    }
    else
    {
        /*
        std::vector<Character> clickableChars;
        for(auto iter : mCharacters)
        {
        }
        */
        // std::vector characters
        // for every character, check if it's at the click AND interactive
            // add to characters vector
        // if characters != empty
            // sort(std::vector) by z-index
            // grab the first one, do interactive stuff
        // else if click spot is out of bounds
            // do nothing
        // else
            // walk to spot
            mBStateDelegator.playerWalk(message.position);
    }
}

void MainState::handleMessage(const MouseReleaseMessage& message)
{
    if(mCurrentActivityState)
    {
        mCurrentActivityState->handleMouseRelease(message.position);
    }
    else
    {
        //behav deleg?
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
            mRenderer.queue(iter.getSprite());
        }

        mRenderer.queue(mFirstNumber);
        mRenderer.queue(mSecondNumber);
    }
    else
    {
        mCurrentActivityState->render();
    }

    mRenderer.render();
}

void MainState::initialize()
{
    Animator animator;
    mInitialized = true;

    mBus.send(PlayMusicMessage{"ambient_bank", false});

    // main player
    mCharacters.push_back(Character(glm::vec2(600.0f, 200.0f), false, std::make_shared<IdleBState>(mBus), mPlayerTexture, glm::vec2(124.0f, 396.0f), animator.getAnimation("player", "idle-front")));
}

void MainState::updateNumbers()
{
    std::string current;
    if(mQueueCounter < 10)
        current = "0";

    current.append(std::to_string(mQueueCounter));

    Animator animator;

    mFirstNumber.setAnimation(animator.getAnimation("number", std::string(1, current[0])));
    mSecondNumber.setAnimation(animator.getAnimation("number", std::string(1, current[1])));
}
