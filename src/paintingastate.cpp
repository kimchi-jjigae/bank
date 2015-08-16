#include "paintingastate.hpp"
#include "global.hpp"
#include "messages.hpp"
#include "intersector.hpp"

PaintingAState::PaintingAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mCounter(600),
    mBackButton({206.0f, 100.0f}),
    mPainting({515.0f, 389.0f}),
    mDragging(false),
    mDied(false)
{
    mBackButtonTexture = makeTexture(gTextures.at("back_button"));
    mBackButton.setTexture(mBackButtonTexture);
    mBackButton.setPosition({35.0f, 640.0f});

    mPaintingTexture = makeTexture(gTextures.at("painting"));
    mPainting.setTexture(mPaintingTexture);
    mPainting.setPosition({507.0f, 185.0f});
    mPainting.setOrigin({252.0f, 11.0f});
    mPainting.setRotation(0.19f);
}

void PaintingAState::update()
{
    mCounter--;

    if(mCounter == 0)
    {
        mIsFinished = true;
        mBus.send(MissNumberMessage());
    }

    if(mDied)
    {
        mPainting.translate({0.0f, 30.0f});
    }
}

void PaintingAState::render()
{
    mRenderer.clear(fea::Color(164, 181, 189));
    mRenderer.queue(mBackButton);
    mRenderer.queue(mPainting);
}

void PaintingAState::handleMouseMove(const glm::uvec2& position)
{
    float xDiff = position.x - mLastPos.x;

    mLastPos = position;

    if(mDragging)
        mPainting.rotate(xDiff / 300.0f);

    float newRotation = mPainting.getRotation();

    if(newRotation > 1.8f || newRotation < -2.4f)
    {
        mDied = true;
        gPaintingRuined = true;
    }
}

void PaintingAState::handleMouseClick(const glm::uvec2& position)
{
    if(intersects(position, mBackButton))
    {
        float rotation = mPainting.getRotation();

        if(fabs(rotation) < 0.02f)
            mBus.send(AdvanceQueueMessage());
        else if(mDied)
            mBus.send(MissNumberMessage());
        mIsFinished = true;
    }
    else
    {
        mDragging = true;
        mLastPos = position;
    }
}

void PaintingAState::handleMouseRelease(const glm::uvec2& position)
{
    (void)position;
    mDragging = false;
}
