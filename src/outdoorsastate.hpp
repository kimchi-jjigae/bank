#pragma once
#include "activitystate.hpp"
#include <fea/render2d.hpp>

class OutdoorsAState : public ActivityState
{
    public:
        OutdoorsAState(fea::MessageBus& bus, fea::Renderer2D& renderer);
        virtual void update();
        virtual void render();
    private:
        int32_t mCounter;

        fea::Texture mBackgroundTexture;
        fea::Quad mBackground;
};
