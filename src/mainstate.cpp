#include "mainstate.hpp"
#include "messages.hpp"
#include "behaviouralstates/allbstates.hpp"
#include "texturemaker.hpp"
#include "global.hpp"
#include "minigames.hpp"
#include <map>

MainState::MainState(fea::MessageBus& bus, fea::Renderer2D& renderer):
    mBus(bus),
    mRenderer(renderer),
    mBStateDelegator(bus, mCharacters),
    mInitialized(false),
    mQueueCounter(28),
    mPlayerQueueNumber(38),
    //rendering
    mBackgroundBack({1024.0f, 768.0f}),
    mBackgroundFront({1024.0f, 768.0f}),
    mPillar({116.0f, 569.0f}),
    mBin({84.0f, 116.0f}),
    mSofa({177.0f, 294.0f}),
    mTicketMachine({113.0f, 96.0f}),
    mFirstNumber({26.0f, 40.0f}),
    mSecondNumber({26.0f, 40.0f})
{
    subscribe(mBus, *this);
}

void MainState::setupGraphics()
{
    mRenderer.setup();

    mBackgroundBackTexture = makeTexture(gTextures.at("bank_bg_b"));
    mBackgroundBack.setTexture(mBackgroundBackTexture);

    mBackgroundFrontTexture = makeTexture(gTextures.at("bank_bg_f"));
    mBackgroundFront.setTexture(mBackgroundFrontTexture);

    mBackgroundMask = makeTexture(gTextures.at("bank_mask"), false, true);

    mPillarTexture = makeTexture(gTextures.at("pillar"));
    mPillar.setTexture(mPillarTexture);

    mBinTexture = makeTexture(gTextures.at("bin"));
    mBin.setTexture(mBinTexture);

    mSofaTexture = makeTexture(gTextures.at("sofa"));
    mSofa.setTexture(mSofaTexture);

    mTicketMachineTexture = makeTexture(gTextures.at("ticket_machine"));
    mTicketMachine.setTexture(mTicketMachineTexture);

    mBackgroundBack.setPosition({0.0f, 0.0f});
    mBackgroundFront.setPosition({0.0f, 0.0f});
    mPillar.setPosition({450.0f, 0.0f});
    mBin.setPosition({520.0f, 440.0f});
    mSofa.setPosition({847.0f, 340.0f});
    mTicketMachine.setPosition({400.0f, 345.0f});
    
    mPlayerTexture = makeTexture(gTextures.at("player"));
    mNumberTexture = makeTexture(gTextures.at("number_texture"));

    mFirstNumber.setTexture(mNumberTexture);
    mSecondNumber.setTexture(mNumberTexture);

    mFirstNumber.setPosition({480.0f, 175.0f});
    mSecondNumber.setPosition({508.0f, 175.0f});

    mFirstNumber.setAnimation(getAnimation("number", "4"));
    mSecondNumber.setAnimation(getAnimation("number", "5"));

    updateNumbers();
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
    else
    {
        for(auto& iter : mCharacters)
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
    (void)message;
    mQueueCounter++;

    if(mQueueCounter > 99)
        mQueueCounter = 0;

    mBus.send(PlaySoundMessage{"queue_ding", false});

    updateNumbers();
}

void MainState::handleMessage(const MissNumberMessage& message)
{
    (void)message;
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
    else if(name == "heartattack")
        mCurrentActivityState = std::unique_ptr<HeartAttackAState>(new HeartAttackAState(mBus, mRenderer));
    else if(name == "whiteboard")
        mCurrentActivityState = std::unique_ptr<WhiteboardAState>(new WhiteboardAState(mBus, mRenderer));
    else if(name == "painting")
        mCurrentActivityState = std::unique_ptr<PaintingAState>(new PaintingAState(mBus, mRenderer));
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
        std::list<Character> clickableChars;
        for(auto& iter : mCharacters)
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
        if(message.position.x > 0 && message.position.x < 1024 && message.position.y > 0 && message.position.y < 768)
        {
            if(mBackgroundMask.getPixel(message.position.x, message.position.y) == fea::Color::Black)
                mBStateDelegator.playerWalk(message.position);
        }
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
        mRenderer.queue(mBackgroundBack);

        std::map<float, fea::AnimatedQuad> mBehindPillar;
        std::map<float, fea::AnimatedQuad> mBeforePillar;

        for(auto& iter : mCharacters)
        {
            auto& sprite = iter.getSprite();

            float yPos = sprite.getPosition().y;
            float scale = ((yPos - 430.0f) / 336.0f)/2.0f + 0.5f;

            sprite.setScale({scale, scale});

            if(yPos > 546.0f)
                mBeforePillar.emplace(yPos, sprite);
            else
                mBehindPillar.emplace(yPos, sprite);
        }

        for(auto& sprite : mBehindPillar)
        {
            mRenderer.queue(sprite.second);
        }

        mRenderer.queue(mPillar);
        mRenderer.queue(mTicketMachine);
        mRenderer.queue(mBin);
        mRenderer.queue(mSofa);

        for(auto& sprite : mBeforePillar)
        {
            mRenderer.queue(sprite.second);
        }

        mRenderer.queue(mFirstNumber);
        mRenderer.queue(mSecondNumber);
        mRenderer.queue(mBackgroundFront);
    }
    else
    {
        mCurrentActivityState->render();
    }

    mRenderer.render();
}

void MainState::initialize()
{
    mInitialized = true;

    mBus.send(PlayMusicMessage{"ambient_bank", false});

    // main player
    mCharacters.push_back(Character("player", glm::vec2(600.0f, 200.0f), false, mPlayerTexture, glm::vec2(124.0f, 396.0f), getAnimation("player", "idle-front")));
    mCharacters.front().pushBehaviour(std::make_shared<IdleBState>(mBus));
}

void MainState::updateNumbers()
{
    std::string current;
    if(mQueueCounter < 10)
        current = "0";

    current.append(std::to_string(mQueueCounter));

    mFirstNumber.setAnimation(getAnimation("number", std::string(1, current[0])));
    mSecondNumber.setAnimation(getAnimation("number", std::string(1, current[1])));
}
