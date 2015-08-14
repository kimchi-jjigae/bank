#pragma once

class ActivityState
{
    public:
        ActivityState(fea::MessageBus& bus, fea::Renderer2D& renderer);
        virtual void update() = 0;
    protected:
        fea::MessageBus& mBus;
        fea::Renderer2D& mRenderer;
};
