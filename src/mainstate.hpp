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
                                StartMinigameMessage>
{
    public:
        MainState(fea::MessageBus& bus, fea::Renderer2D& renderer);
        void setupGraphics();
        void update();
        void handleMessage(const AdvanceQueueMessage& message) override;
        void handleMessage(const MissNumberMessage& message) override;
        void handleMessage(const StartMinigameMessage& message) override;
    private:
        void render();
        void initialize();
        void updateNumbers();
        fea::MessageBus& mBus;
        fea::Renderer2D& mRenderer;

        std::vector<Character> mCharacters;
        std::unique_ptr<ActivityState> mCurrentActivityState;

        BehaviouralStateDelegator mBStateDelegator;

        bool mInitialized;
        int32_t mQueueCounter;
        int32_t mPlayerQueueNumber;

        //graphics
        fea::Texture mBackgroundTexture;
        fea::Texture mPlayerTexture;
        fea::Texture mNumberTexture;
        fea::Quad mBackground;
        fea::AnimatedQuad mFirstNumber;
        fea::AnimatedQuad mSecondNumber;
};
