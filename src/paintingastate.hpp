#pragma once
#include "activitystate.hpp"
#include <fea/render2d.hpp>

class PaintingAState : public ActivityState
{
    public:
        PaintingAState(fea::MessageBus& bus, fea::Renderer2D& renderer);
        virtual void update() override;
        virtual void render() override;
        virtual void handleMouseMove(const glm::uvec2& position) override;
        virtual void handleMouseClick(const glm::uvec2& position) override;
        virtual void handleMouseRelease(const glm::uvec2& position) override;
    private:
        int32_t mCounter;

        fea::Texture mBackButtonTexture;
        fea::Quad mBackButton;

        fea::Texture mPaintingTexture;
        fea::Quad mPainting;
        bool mDragging;
        glm::vec2 mLastPos;
        bool mDied;
};
