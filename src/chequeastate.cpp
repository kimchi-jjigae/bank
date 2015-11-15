#include "chequeastate.hpp"
#include "global.hpp"
#include "messages.hpp"
#include "intersector.hpp"

fea::Texture ChequeAState::mCanvas = fea::Texture();
bool ChequeAState::mCanvasInitialized = false;

ChequeAState::ChequeAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mBackButton({206.0f, 100.0f}),
    mBackground({1024.0f, 768.0f}),
    mCanvasQuad({641.0f, 372.0f}),
    mDragging(false)
{
    mBackgroundTexture = makeTexture(gTextures.at("chequebg"));
    mBackground.setTexture(mBackgroundTexture);

    mBackButtonTexture = makeTexture(gTextures.at("back_button"));
    mBackButton.setTexture(mBackButtonTexture);
    mBackButton.setPosition({35.0f, 640.0f});

    if(!mCanvasInitialized)
    {
        mCanvas.create({641, 372}, fea::Color::Transparent, true, true);
        mCanvasInitialized = true;
    }
    
    mCanvasQuad.setTexture(mCanvas);
    mCanvasQuad.setPosition({143.0f, 254.0f});

    mBus.send(PlaySoundMessage{"turn_page", false});
}

void ChequeAState::update()
{
}

void ChequeAState::render()
{
    mRenderer.queue(mBackground);
    mRenderer.queue(mCanvasQuad);
    mRenderer.queue(mBackButton);
}

void ChequeAState::handleMouseMove(const glm::uvec2& position)
{
    if(mDragging)
    {
        glm::uvec2 transposed = position - (glm::uvec2)mCanvasQuad.getPosition();

        if(transposed.x < 641 && transposed.y < 372)
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

void ChequeAState::handleMouseClick(const glm::uvec2& position)
{
    if(intersects(position, mBackButton))
    {
        mIsFinished = true;
    }
    else
    {
        glm::uvec2 transposed = position - (glm::uvec2)mCanvasQuad.getPosition();

        if(transposed.x < 641 && transposed.y < 372)
        {
            mDragging = true;
            mLastPosition = transposed;
            mBus.send(PlaySoundMessage{"pen", true});
        }
    }
}

void ChequeAState::handleMouseRelease(const glm::uvec2& position)
{
    (void) position;
    mDragging = false;
    mBus.send(StopSoundMessage());
}

void ChequeAState::putDot(const glm::uvec2& position)
{
    gChequeDone = true;

    int32_t radius = 1;

    for(int32_t x = (int32_t)position.x - (int32_t)radius; x < (int32_t)position.x + (int32_t)radius; x++)
    {
        for(int32_t y = (int32_t)position.y - radius; y < (int32_t)position.y + radius; y++)
        {
            if(x > 0 && y > 0 && x < 641 && y < 372)
                mCanvas.setPixel({(uint32_t)x,(uint32_t) y}, fea::Color(0, 15, 85));
        }
    }
}
