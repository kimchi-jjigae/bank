#include "childquestionastate.hpp"
#include "global.hpp"
#include "messages.hpp"

ChildQuestionAState::ChildQuestionAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mCounter(600),
    mBackground({1024.0f, 768.0f})
{
    mBackgroundTexture = makeTexture(gTextures.at("childquestion"));
    mBackground.setTexture(mBackgroundTexture);
}

void ChildQuestionAState::update()
{
    mCounter--;

    if(mCounter == 0)
    {
        mIsFinished = true;
        mBus.send(MissNumberMessage());
    }
}

void ChildQuestionAState::render()
{
    mRenderer.queue(mBackground);
}

void ChildQuestionAState::handleMouseMove(const glm::uvec2& position)
{
}

void ChildQuestionAState::handleMouseClick(const glm::uvec2& position)
{
    mIsFinished = true;
}

void ChildQuestionAState::handleMouseRelease(const glm::uvec2& position)
{
}
