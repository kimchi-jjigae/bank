#pragma once
#include "activitystate.hpp"
#include <fea/render2d.hpp>

class RunErrandAState : public ActivityState
{
    public:
        RunErrandAState(fea::MessageBus& bus, fea::Renderer2D& renderer);
        virtual void update() override;
        virtual void render() override;
        virtual void handleMouseMove(const glm::uvec2& position) override;
        virtual void handleMouseClick(const glm::uvec2& position) override;
        virtual void handleMouseRelease(const glm::uvec2& position) override;
    private:
        fea::Texture mBackgroundTexture;
        fea::Quad mBackground;
        fea::Texture mBackButtonTexture;
        fea::Quad mBackButton;
        fea::Texture mArmUpTexture;
        fea::Quad mArmUp;
        fea::Texture mArmDownTexture;
        fea::Quad mArmDown;
        fea::Texture mExplosionTexture;
        fea::Quad mExplosion;
        fea::Texture mChequeTableTexture;
        fea::Quad mChequeTable;
        fea::Texture mNoteTexture;
        fea::Quad mNote;

        bool mHitting;
        int32_t mExplosionCounter;
        int32_t mHitCount;

        bool mNoteDown;
        bool mChequeDown;
        bool mNo;
};
