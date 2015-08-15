#include "whiteboardastate.hpp"
#include "global.hpp"
#include "messages.hpp"
#include "intersector.hpp"

fea::Texture WhiteboardAState::mCanvas = fea::Texture();
bool WhiteboardAState::mCanvasInitialized = false;

WhiteboardAState::WhiteboardAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mCounter(600),
    mBackground({1024.0f, 768.0f}),
    mCanvasQuad({877.0f, 613.0f}),
    mDragging(false),
    mBackButton({206.0f, 100.0f})
{
    mBackgroundTexture = makeTexture(gTextures.at("whiteboard"));
    mBackground.setTexture(mBackgroundTexture);

    mBackButtonTexture = makeTexture(gTextures.at("back_button"));
    mBackButton.setTexture(mBackButtonTexture);
    mBackButton.setPosition({35.0f, 640.0f});


    if(!mCanvasInitialized)
    {
        mCanvas.create(877, 613, fea::Color::Transparent, true, true);
        mCanvasInitialized = true;
    }
    
    mCanvasQuad.setTexture(mCanvas);
    mCanvasQuad.setPosition({68.0f, 70.0f});

    mBus.send(PlaySoundMessage{"turn_page"});
}

void WhiteboardAState::update()
{
    mCounter--;

    if(mCounter == 0)
    {
        mIsFinished = true;
        mBus.send(MissNumberMessage());
    }
}

void WhiteboardAState::render()
{
    mRenderer.queue(mBackground);
    mRenderer.queue(mCanvasQuad);
    mRenderer.queue(mBackButton);
}

void WhiteboardAState::handleMouseMove(const glm::uvec2& position)
{
    if(mDragging)
    {
        glm::uvec2 transposed = position - (glm::uvec2)mCanvasQuad.getPosition();

        if(transposed.x < 877 && transposed.y < 613)
        {
            while(mLastPosition != transposed)
            {
                if(mLastPosition.x < transposed.x)
                    mLastPosition.x++;
                if(mLastPosition.x > transposed.x)
                    mLastPosition.x--;
                if(mLastPosition.y < transposed.y)
                    mLastPosition.y++;
                if(mLastPosition.y > transposed.y)
                    mLastPosition.y--;

                putDot(mLastPosition);
            }

            mLastPosition = transposed;
        }

        mCanvas.update();
    }
}

void WhiteboardAState::handleMouseClick(const glm::uvec2& position)
{
    if(intersects(position, mBackButton))
    {
        mIsFinished = true;
    }
    else
    {
        glm::uvec2 transposed = position - (glm::uvec2)mCanvasQuad.getPosition();

        if(transposed.x < 877 && transposed.y < 613)
        {
            mDragging = true;
            mLastPosition = transposed;
            mBus.send(PlaySoundMessage{"pen", true});
        }
    }
}

void WhiteboardAState::handleMouseRelease(const glm::uvec2& position)
{
    mDragging = false;
    mBus.send(StopSoundMessage());
}

void WhiteboardAState::putDot(const glm::uvec2& position)
{
    int32_t radius = 2;

    for(int32_t x = position.x - radius; x < position.x + radius; x++)
    {
        for(int32_t y = position.y - radius; y < position.y + radius; y++)
        {
            if(x > 0 && y > 0 && x < 877 && y < 613)
                mCanvas.setPixel(x, y, fea::Color(241, 50, 0));
        }
    }
}
