#include "mainstate.hpp"
#include "messages.hpp"
#include "behaviouralstates/allbstates.hpp"
#include "texturemaker.hpp"
#include "global.hpp"
#include "minigames.hpp"
#include "randomwait.hpp"
#include <map>
#include <fea/userinterface.hpp>

MainState::MainState(fea::MessageBus& bus, fea::Renderer2D& renderer):
    mBus(bus),
    mRenderer(renderer),
    mBStateDelegator(bus, mCharacters),
    mInitialized(false),
    mFramesToNextNumber(randomWaitTime()),
    //rendering
    mBackgroundBack({1024.0f, 768.0f}),
    mBackgroundFront({1024.0f, 768.0f}),
    mPillar({116.0f, 569.0f}),
    mBin({84.0f, 116.0f}),
    mSofa({177.0f, 294.0f}),
    mTicketMachine({113.0f, 96.0f}),
    mWallPainting({40.0f, 116.0f}),
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

    mWallPaintingTexture = makeTexture(gTextures.at("wallpainting"));
    mWallPainting.setTexture(mWallPaintingTexture);
    mWallPainting.setPosition({984.0f, 200.0f});

    mTicketMachineTexture = makeTexture(gTextures.at("ticket_machine"));

    mBackgroundBack.setPosition({0.0f, 0.0f});
    mBackgroundFront.setPosition({0.0f, 0.0f});
    mPillar.setPosition({450.0f, 0.0f});
    mBin.setPosition({520.0f, 440.0f});
    mSofa.setPosition({847.0f, 340.0f});
    
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
        if(gMenuOver)
        {
            for(auto& iter : mCharacters)
            {
                iter.update();
            }
        }
    }

    render();

    if(gMenuOver)
    {
        mBStateDelegator.update();

        if(!mCurrentActivityState)
        {
            mFramesToNextNumber--;
            if(mFramesToNextNumber == 0)
            {
                mBus.send(AdvanceQueueMessage());
                mFramesToNextNumber = randomWaitTime();
            }
        }
    }
}

void MainState::handleMessage(const AdvanceQueueMessage& message)
{
    (void)message;
    gQueueCounter++;

    if(gQueueCounter > 99)
        gQueueCounter = 0;

    mBus.send(PlaySoundMessage{"queue_ding", false});

    updateNumbers();
}

void MainState::handleMessage(const MissNumberMessage& message)
{
    (void)message;
    if(gQueueCounter <= gPlayerQueueNumber)
        gQueueCounter = gPlayerQueueNumber + 1;
    else
        gQueueCounter++;

    if(gQueueCounter > 99)
        gQueueCounter = 0;

    mBus.send(PlaySoundMessage{"queue_ding", false});

    updateNumbers();
}

void MainState::handleMessage(const StartMinigameMessage& message)
{
    if(!mCurrentActivityState)
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
        else if(name == "menu")
            mCurrentActivityState = std::unique_ptr<MenuAState>(new MenuAState(mBus, mRenderer));
        else if(name == "hangman")
            mCurrentActivityState = std::unique_ptr<HangmanAState>(new HangmanAState(mBus, mRenderer));
        else if(name == "takenote")
            mCurrentActivityState = std::unique_ptr<TakeNoteAState>(new TakeNoteAState(mBus, mRenderer));
    }
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

void MainState::handleMessage(const KeyPressedMessage& message)
{
    if(mCurrentActivityState)
    {
        mCurrentActivityState->handleKeyPressed(message.key);
    }
    else
    {
        if(message.key == fea::Keyboard:: O)
            mBus.send(StartMinigameMessage{"outdoors"});
        else if(message.key == fea::Keyboard:: C)
            mBus.send(StartMinigameMessage{"crossword"});
        else if(message.key == fea::Keyboard:: S)
            mBus.send(StartMinigameMessage{"sudoku"});
        else if(message.key == fea::Keyboard:: H)
            mBus.send(StartMinigameMessage{"childquestion"});
        else if(message.key == fea::Keyboard:: E)
            mBus.send(StartMinigameMessage{"heartattack"});
        else if(message.key == fea::Keyboard:: W)
            mBus.send(StartMinigameMessage{"whiteboard"});
        else if(message.key == fea::Keyboard:: P)
            mBus.send(StartMinigameMessage{"painting"});
        else if(message.key == fea::Keyboard:: A)
            mBus.send(StartMinigameMessage{"hangman"});
        else if(message.key == fea::Keyboard:: T)
            mBus.send(StartMinigameMessage{"takenote"});
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

            if(iter.mScaled)
            {
                float scale = ((yPos - 430.0f) / 336.0f)/2.0f + 0.5f;

                sprite.setScale({scale, scale});
            }

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
        mRenderer.queue(mBin);
        mRenderer.queue(mSofa);

        if(!gPaintingRuined)
            mRenderer.queue(mWallPainting);

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

    gQueueCounter = 28;

    // main player
    mCharacters.push_back(Character("player", glm::vec2(600.0f, 500.0f), false, mPlayerTexture, glm::vec2(124.0f, 396.0f), true));
    mCharacters.front().pushBehaviour(std::make_shared<IdleBState>(mBus));


    mBus.send(StartMinigameMessage{"menu"});

    // ticket machine
    Character hej = Character("ticket_machine", glm::vec2(470.0f, 548.0f), true, mTicketMachineTexture, glm::vec2(113.0f, 96.0f), false);
    glm::vec2 asdf = hej.getSprite().getSize();
    hej.getSprite().setOrigin({asdf.x / 2.0f, asdf.y * 2.25f});
    hej.pushBehaviour(std::make_shared<IdleBState>(mBus));
    mCharacters.push_back(hej);
}

void MainState::updateNumbers()
{
    std::string current;
    if(gQueueCounter < 10)
        current = "0";

    current.append(std::to_string(gQueueCounter));

    mFirstNumber.setAnimation(getAnimation("number", std::string(1, current[0])));
    mSecondNumber.setAnimation(getAnimation("number", std::string(1, current[1])));
}
