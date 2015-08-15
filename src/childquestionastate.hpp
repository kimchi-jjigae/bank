#pragma once
#include "activitystate.hpp"
#include <fea/render2d.hpp>
#include "intersector.hpp"

class ChildQuestionAState : public ActivityState
{
    public:
        ChildQuestionAState(fea::MessageBus& bus, fea::Renderer2D& renderer);
        virtual void update() override;
        virtual void render() override;
        virtual void handleMouseMove(const glm::uvec2& position) override;
        virtual void handleMouseClick(const glm::uvec2& position) override;
        virtual void handleMouseRelease(const glm::uvec2& position) override;
    private:
        int32_t mCounter;

        fea::Texture mBackgroundTexture;
        fea::Texture mBackButtonTexture;
        fea::Texture mSayButtonTexture;
        fea::Texture mSadMouthTexture;
        fea::Quad mBackground;
        fea::Quad mBackButton;
        fea::Quad mSayButton;
        fea::Quad mSadMouth;
};
