#include "activitystate.hpp"

ActivityState::ActivityState(fea::MessageBus& bus, fea::Renderer2D& renderer):
    mBus(bus),
    mRenderer(renderer),
    mIsFinished(false)
{
}

bool ActivityState::isFinished() const
{
    return mIsFinished;
}
