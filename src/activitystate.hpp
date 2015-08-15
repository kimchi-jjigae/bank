#pragma once
#include <fea/util.hpp>
#include <fea/render2d.hpp>

class ActivityState
{
    public:
        ActivityState(fea::MessageBus& bus, fea::Renderer2D& renderer);
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void handleMouseMove(const glm::uvec2& position) = 0;
        virtual void handleMouseClick(const glm::uvec2& position) = 0;
        bool isFinished() const;
    protected:
        fea::MessageBus& mBus;
        fea::Renderer2D& mRenderer;
        bool mIsFinished;
};
