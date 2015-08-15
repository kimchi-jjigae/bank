#include "crosswordastate.hpp"
#include "global.hpp"
#include "messages.hpp"

CrosswordAState::CrosswordAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mCounter(600),
    mBackground({1024.0f, 768.0f}),
    mCanvasQuad({764.0f, 684.0f}),
    mDragging(false)
{
    mBackgroundTexture = makeTexture(gTextures.at("crossword"));
    mBackground.setTexture(mBackgroundTexture);


    mCanvas.create(764, 684, fea::Color::Transparent, true, true);
    mCanvasQuad.setTexture(mCanvas);
    mCanvasQuad.setPosition({202.0f, 77.0f});
}

void CrosswordAState::update()
{
    mCounter--;

    if(mCounter == 0)
    {
        mIsFinished = true;
        mBus.send(MissNumberMessage());
    }
}

void CrosswordAState::render()
{
    mRenderer.queue(mBackground);
    mRenderer.queue(mCanvasQuad);
}

void CrosswordAState::handleMouseMove(const glm::uvec2& position)
{
    if(mDragging)
    {
        glm::uvec2 transposed = position - (glm::uvec2)mCanvasQuad.getPosition();

        if(transposed.x < 764 && transposed.y < 684)
            mCanvas.setPixel(transposed.x, transposed.y, fea::Color(0, 15, 85));

        std::cout << transposed << "\n";
        mCanvas.update();
    }
}

void CrosswordAState::handleMouseClick(const glm::uvec2& position)
{
    glm::uvec2 transposed = position - (glm::uvec2)mCanvasQuad.getPosition();

    if(transposed.x < 764 && transposed.y < 684)
    {
        mDragging = true;
    }
    else
    {
        exit(3);
        mIsFinished = true;
    }
}

void CrosswordAState::handleMouseRelease(const glm::uvec2& position)
{
    mDragging = false;
}
