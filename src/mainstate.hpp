#pragma once
#include <fea/util.hpp>
#include <fea/render2d.hpp>
#include <memory>
#include "activitystate.hpp"

class MainState
{
    public:
        MainState(fea::MessageBus& bus, fea::Renderer2D& renderer);
        void update();
    private:
        void render();
        fea::MessageBus& mBus;
        fea::Renderer2D& mRenderer;

        std::unique_ptr<ActivityState> mCurrentActivityState;
};
