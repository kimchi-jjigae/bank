#pragma once
#include <fea/util.hpp>
#include <fea/render2d.hpp>
#include <memory>
#include "activitystate.hpp"
#include "character.hpp"
#include "bstatedelegator.hpp"
#include "messages.hpp"

class MainState : 
    public fea::MessageReceiver<AdvanceQueueMessage,
                                MissNumberMessage,
                                StartMinigameMessage,
                                MouseMoveMessage,
                                MouseClickMessage,
                                MouseReleaseMessage,
                                KeyPressedMessage>
{
    public:
        MainState(fea::MessageBus& bus, fea::Renderer2D& renderer);
        void setupGraphics();
        void update();
        void handleMessage(const AdvanceQueueMessage& message) override;
        void handleMessage(const MissNumberMessage& message) override;
        void handleMessage(const StartMinigameMessage& message) override;
        void handleMessage(const MouseMoveMessage& message) override;
        void handleMessage(const MouseClickMessage& message) override;
        void handleMessage(const MouseReleaseMessage& message) override;
        void handleMessage(const KeyPressedMessage& message) override;
    private:
        void render();
        void initialize();
        void updateNumbers();
        fea::MessageBus& mBus;
        fea::Renderer2D& mRenderer;

        std::list<Character> mCharacters;
        std::unique_ptr<ActivityState> mCurrentActivityState;

        BehaviouralStateDelegator mBStateDelegator;

        bool mInitialized;
        int32_t mQueueCounter;
        int32_t mPlayerQueueNumber;
        int32_t mFramesToNextNumber;

        //graphics
        fea::Texture mBackgroundBackTexture;
        fea::Texture mBackgroundFrontTexture;
        fea::Texture mBackgroundMask;
        fea::Texture mPillarTexture;
        fea::Texture mBinTexture;
        fea::Texture mSofaTexture;
        fea::Texture mTicketMachineTexture;
        fea::Texture mPlayerTexture;
        fea::Texture mNumberTexture;
        fea::Texture mWallPaintingTexture;
        fea::Quad mBackgroundBack;
        fea::Quad mBackgroundFront;
        fea::Quad mPillar;
        fea::Quad mBin;
        fea::Quad mSofa;
        fea::Quad mTicketMachine;
        fea::Quad mWallPainting;
        fea::AnimatedQuad mFirstNumber;
        fea::AnimatedQuad mSecondNumber;
};
