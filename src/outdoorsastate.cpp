#include "outdoorsastate.hpp"
#include "global.hpp"
#include "messages.hpp"
#include "intersector.hpp"

OutdoorsAState::OutdoorsAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mCounter(600),
    mBackground({1024.0f, 768.0f}),
    mBackButton({206.0f, 100.0f})
{
    mBackgroundTexture = makeTexture(gTextures.at("outside"));
    mBackground.setTexture(mBackgroundTexture);

    mBackButtonTexture = makeTexture(gTextures.at("back_button"));
    mBackButton.setTexture(mBackButtonTexture);
    mBackButton.setPosition({35.0f, 640.0f});

    mBus.send(PlaySoundMessage{"sigh"});
}

void OutdoorsAState::update()
{
    mCounter--;

    if(mCounter == 0)
    {
        mIsFinished = true;
        mBus.send(MissNumberMessage());
    }
}

void OutdoorsAState::render()
{
    mRenderer.queue(mBackground);
    mRenderer.queue(mBackButton);
}

void OutdoorsAState::handleMouseMove(const glm::uvec2& position)
{
}

void OutdoorsAState::handleMouseClick(const glm::uvec2& position)
{
    if(intersects(position, mBackButton))
    {
        mIsFinished = true;
    }
}

void OutdoorsAState::handleMouseRelease(const glm::uvec2& position)
{
}
