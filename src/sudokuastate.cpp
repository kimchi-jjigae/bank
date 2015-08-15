#include "sudokuastate.hpp"
#include "global.hpp"
#include "messages.hpp"

fea::Texture SudokuAState::mCanvas = fea::Texture();
bool SudokuAState::mCanvasInitialized = false;

SudokuAState::SudokuAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mCounter(600),
    mBackground({1024.0f, 768.0f}),
    mCanvasQuad({764.0f, 684.0f}),
    mDragging(false)
{
    mBackgroundTexture = makeTexture(gTextures.at("sudoku"));
    mBackground.setTexture(mBackgroundTexture);


    if(!mCanvasInitialized)
    {
        mCanvas.create(764, 684, fea::Color::Transparent, true, true);
        mCanvasInitialized = true;
    }
    
    mCanvasQuad.setTexture(mCanvas);
    mCanvasQuad.setPosition({202.0f, 77.0f});

    mBus.send(PlaySoundMessage{"turn_page"});
}

void SudokuAState::update()
{
    mCounter--;

    if(mCounter == 0)
    {
        mIsFinished = true;
        mBus.send(MissNumberMessage());
    }
}

void SudokuAState::render()
{
    mRenderer.queue(mBackground);
    mRenderer.queue(mCanvasQuad);
}

void SudokuAState::handleMouseMove(const glm::uvec2& position)
{
    if(mDragging)
    {
        glm::uvec2 transposed = position - (glm::uvec2)mCanvasQuad.getPosition();

        if(transposed.x < 764 && transposed.y < 684)
        {
            while(mLastPosition != transposed)
            {
                if(mLastPosition.x < transposed.x)
                    mLastPosition.x++;
                if(mLastPosition.x > transposed.x)
                    mLastPosition--;
                if(mLastPosition.y < transposed.y)
                    mLastPosition.y++;
                if(mLastPosition.y > transposed.y)
                    mLastPosition--;

                putDot(mLastPosition);
            }

            mLastPosition = transposed;
        }

        mCanvas.update();
    }
}

void SudokuAState::handleMouseClick(const glm::uvec2& position)
{
    glm::uvec2 transposed = position - (glm::uvec2)mCanvasQuad.getPosition();

    if(transposed.x < 764 && transposed.y < 684)
    {
        mDragging = true;
        mLastPosition = transposed;
        mBus.send(PlaySoundMessage{"pen", true});
    }
    else
    {
        mIsFinished = true;
    }
}

void SudokuAState::handleMouseRelease(const glm::uvec2& position)
{
    mDragging = false;
    mBus.send(StopSoundMessage());
}

void SudokuAState::putDot(const glm::uvec2& position)
{
    int32_t radius = 1;

    for(int32_t x = position.x - radius; x < position.x + radius; x++)
    {
        for(int32_t y = position.y - radius; y < position.y + radius; y++)
        {
            if(x > 0 && y > 0 && x < 764 && y < 684)
                mCanvas.setPixel(x, y, fea::Color(0, 15, 85));
        }
    }
}
