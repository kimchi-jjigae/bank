#pragma once
#include "activitystate.hpp"
#include <fea/render2d.hpp>

class HangmanAState : public ActivityState
{
    public:
        HangmanAState(fea::MessageBus& bus, fea::Renderer2D& renderer);
        virtual void update() override;
        virtual void render() override;
        virtual void handleMouseMove(const glm::uvec2& position) override;
        virtual void handleMouseClick(const glm::uvec2& position) override;
        virtual void handleMouseRelease(const glm::uvec2& position) override;
        virtual void handleKeyPressed(int32_t key) override;
    private:
        fea::Texture mBackgroundTexture;
        fea::Quad mBackground;
        fea::Texture mBackButtonTexture;
        fea::Quad mBackButton;

        fea::Texture mRTexture;
        fea::Texture mETexture;
        fea::Texture mYTexture;
        fea::Texture mKTexture;
        fea::Texture mATexture;
        fea::Texture mVTexture;
        fea::Texture mITexture;
        fea::Texture mWrong1Texture;
        fea::Texture mWrong2Texture;
        fea::Texture mWrong3Texture;

        fea::Quad mRQuad;
        fea::Quad mEQuad;
        fea::Quad mY1Quad;
        fea::Quad mK1Quad;
        fea::Quad mY2Quad;
        fea::Quad mAQuad;
        fea::Quad mVQuad;
        fea::Quad mIQuad;
        fea::Quad mK2Quad;
        fea::Quad mWrongQuad;

        int32_t mRightAmount;
        int32_t mWrongAmount;

        std::set<int32_t> mGuesses;
};
