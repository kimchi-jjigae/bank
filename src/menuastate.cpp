#include "menuastate.hpp"
#include "global.hpp"
#include "messages.hpp"
#include "intersector.hpp"

MenuAState::MenuAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mBackground({1024.0f, 768.0f}),
    mBackButton({515.0f, 150.0f})
{
    mBackgroundTexture = makeTexture(gTextures.at("menubg"));
    mBackground.setTexture(mBackgroundTexture);

    mBackButtonTexture = makeTexture(gTextures.at("menubutton"));
    mBackButton.setTexture(mBackButtonTexture);
    mBackButton.setPosition({240.0f, 585.0f});
}

void MenuAState::update()
{
}

void MenuAState::render()
{
    mRenderer.queue(mBackground);
    mRenderer.queue(mBackButton);
}

void MenuAState::handleMouseMove(const glm::uvec2& position)
{
    (void)position;
}

void MenuAState::handleMouseClick(const glm::uvec2& position)
{
    if(intersects(position, mBackButton))
    {
        mIsFinished = true;
        gMenuOver = true;

        mBus.send(PlayMusicMessage{"ambient_bank", true});
    }
}

void MenuAState::handleMouseRelease(const glm::uvec2& position)
{
    (void)position;
}
