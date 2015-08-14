#pragma once
#include <fea/util.hpp>
#include <fea/render2d.hpp>

class MainState
{
    public:
        MainState(fea::MessageBus& bus, fea::Renderer2D& renderer);
    private:
        fea::MessageBus& mBus;
        fea::Renderer2D& mRenderer;
};
