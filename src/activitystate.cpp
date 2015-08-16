#include "activitystate.hpp"

ActivityState::ActivityState(fea::MessageBus& bus, fea::Renderer2D& renderer):
    mBus(bus),
    mRenderer(renderer),
    mIsFinished(false)
{
}

void ActivityState::handleKeyPressed(int32_t position)
{
    (void)position;
}

bool ActivityState::isFinished() const
{
    return mIsFinished;
}
