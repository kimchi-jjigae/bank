#pragma once
#include "activitystate.hpp"
#include <fea/render2d.hpp>

class CrosswordAState : public ActivityState
{
    public:
        CrosswordAState(fea::MessageBus& bus, fea::Renderer2D& renderer);
        virtual void update() override;
        virtual void render() override;
        virtual void handleMouseMove(const glm::uvec2& position) override;
        virtual void handleMouseClick(const glm::uvec2& position) override;
    private:
        int32_t mCounter;

        fea::Texture mBackgroundTexture;
        fea::Quad mBackground;
};
