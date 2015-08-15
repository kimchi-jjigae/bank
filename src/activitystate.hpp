#pragma once
#include <fea/util.hpp>
#include <fea/render2d.hpp>

class ActivityState
{
    public:
        ActivityState(fea::MessageBus& bus, fea::Renderer2D& renderer);
        virtual void update() = 0;
        virtual void render() = 0;
    protected:
        fea::MessageBus& mBus;
        fea::Renderer2D& mRenderer;
};
