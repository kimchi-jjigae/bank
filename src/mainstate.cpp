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
    mCrosswordTexture = makeTexture(gTextures.at("crosswordt"));
    mSudokuTexture = makeTexture(gTextures.at("sudokut"));
    mCheckTexture = makeTexture(gTextures.at("checkt"));
    mCashierTexture = makeTexture(gTextures.at("cashiert"));

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

    if(!gPaintingRuined)
    {
        // delete painting character
        /*
        for(auto& iter : mCharacters)
        {
            //
        }
        */
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
        else if(name == "runerrand")
            mCurrentActivityState = std::unique_ptr<RunErrandAState>(new RunErrandAState(mBus, mRenderer));
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
        else if(name == "viewnote")
            mCurrentActivityState = std::unique_ptr<ViewNoteAState>(new ViewNoteAState(mBus, mRenderer));
        else if(name == "cheque")
            mCurrentActivityState = std::unique_ptr<ChequeAState>(new ChequeAState(mBus, mRenderer));
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
        std::map<float, Character> clickableChars;

        for(auto& iter : mCharacters)
        {
            auto& sprite = iter.getSprite();
            float yPos = sprite.getPosition().y;
            if(intersects(message.position, iter.getSprite()))
            {
                if(iter.mInteractive)
                {
                    clickableChars.emplace(yPos, iter);
                }
            }
        }
        if(!clickableChars.empty())
        {
            // grab the first one, do interactive stuff
            Character car = clickableChars.rbegin()->second;
            std::string type = car.mCharacterType;

            if(type == "player")
            {
                mBStateDelegator.gameBehaviour({0.0f, 0.0f}, "viewnote");
            }
            if(type == "ticket_machine")
            {
                mBStateDelegator.gameBehaviour({454.0f, 561.0f}, "ticket_machine");
            }
            else if(type == "painting")
            {
                mBStateDelegator.gameBehaviour({906.0f, 496.0f}, "painting");
            }
            else if(type == "crossword")
            {
                mBStateDelegator.gameBehaviour({714.0f, 658.0f}, "crossword");
            }
            else if(type == "sudoku")
            {
                mBStateDelegator.gameBehaviour({714.0f, 658.0f}, "sudoku");
            }
            else if(type == "check")
            {
                mBStateDelegator.gameBehaviour({583.0f, 485.0f}, "check");
            }
            else if(type == "cashier")
            {
                if(gChequeDone && gPlayerQueueNumber == gQueueCounter)
                {
                    mBStateDelegator.gameBehaviour({150.0f, 480.0f}, "cashier");
                }
            }
            else if(type == "outdoors")
            {
                std::cout << "hi\n";
                mBStateDelegator.gameBehaviour({14.0f, 522.0f}, "outdoors");
            }
        }
        else if(message.position.x > 0 && message.position.x < 1024 && message.position.y > 0 && message.position.y < 768)
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
        else if(message.key == fea::Keyboard:: S)
            mBus.send(StartMinigameMessage{"sudoku"});
        else if(message.key == fea::Keyboard:: H)
            mBus.send(StartMinigameMessage{"childquestion"});
        else if(message.key == fea::Keyboard:: E)
            mBus.send(StartMinigameMessage{"heartattack"});
        else if(message.key == fea::Keyboard:: R)
            mBus.send(StartMinigameMessage{"runerrand"});
        else if(message.key == fea::Keyboard:: W)
            mBus.send(StartMinigameMessage{"whiteboard"});
        else if(message.key == fea::Keyboard:: A)
            mBus.send(StartMinigameMessage{"hangman"});
        else if(message.key == fea::Keyboard:: T)
            mBus.send(StartMinigameMessage{"takenote"});
        else if(message.key == fea::Keyboard:: V)
            mBus.send(StartMinigameMessage{"viewnote"});
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
        std::map<float, fea::AnimatedQuad> mAfterForeground;

        for(auto& iter : mCharacters)
        {
            auto& sprite = iter.getSprite();
            float yPos = sprite.getPosition().y;

            if(iter.mScaled)
            {
                float scale = ((yPos - 430.0f) / 336.0f)/2.0f + 0.5f;

                sprite.setScale({scale, scale});
            }

            if(yPos > 658.0f)
                mAfterForeground.emplace(yPos, sprite);
            else if(yPos > 546.0f)
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

        for(auto& sprite : mBeforePillar)
        {
            mRenderer.queue(sprite.second);
        }

        mRenderer.queue(mFirstNumber);
        mRenderer.queue(mSecondNumber);
        mRenderer.queue(mBackgroundFront);

        for(auto& sprite : mAfterForeground)
        {
            mRenderer.queue(sprite.second);
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
    mInitialized = true;

    gQueueCounter = 28;
    updateNumbers();

    mBus.send(StartMinigameMessage{"menu"});

    // main player
    mCharacters.push_back(Character("player", glm::vec2(269.0f, 569.0f), false, mPlayerTexture, glm::vec2(124.0f, 396.0f), true));
    mCharacters.front().pushBehaviour(std::make_shared<IdleBState>(mBus));

    // ticket machine
    Character hej = Character("ticket_machine", glm::vec2(470.0f, 548.0f), true, mTicketMachineTexture, glm::vec2(113.0f, 96.0f), false);
    glm::vec2 asdf = hej.getSprite().getSize();
    hej.getSprite().setOrigin({asdf.x / 2.0f, asdf.y * 2.25f});
    hej.pushBehaviour(std::make_shared<IdleBState>(mBus));
    mCharacters.push_back(hej);

    // painting
    hej = Character("painting", glm::vec2(1006.0f, 320.0f), true, mWallPaintingTexture, glm::vec2(40.0f, 116.0f), false);
    asdf = hej.getSprite().getSize();
    hej.pushBehaviour(std::make_shared<IdleBState>(mBus));
    mCharacters.push_back(hej);

    // crossword
    hej = Character("crossword", glm::vec2(800.0f, 764.0f), true, mCrosswordTexture, glm::vec2(156.0f, 94.0f), false);
    hej.pushBehaviour(std::make_shared<IdleBState>(mBus));
    mCharacters.push_back(hej);

    // sudoku
    hej = Character("sudoku", glm::vec2(780.0f, 764.0f), true, mSudokuTexture, glm::vec2(156.0f, 94.0f), false);
    hej.pushBehaviour(std::make_shared<IdleBState>(mBus));
    mCharacters.push_back(hej);

    // cheques
    hej = Character("check", glm::vec2(588.0f, 337.0f), true, mCheckTexture, glm::vec2(43.0f, 31.0f), false);
    hej.pushBehaviour(std::make_shared<IdleBState>(mBus));
    mCharacters.push_back(hej);

    // cashier
    hej = Character("cashier", glm::vec2(152.0f, 339.0f), true, mCashierTexture, glm::vec2(119.0f, 93.0f), false);
    hej.pushBehaviour(std::make_shared<IdleBState>(mBus));
    mCharacters.push_back(hej);

    // outdoors
    hej = Character("outdoors", glm::vec2(20.0f, 529.0f), true, mCashierTexture, glm::vec2(119.0f, 93.0f), false);
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
