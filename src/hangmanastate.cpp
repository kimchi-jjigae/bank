#include "hangmanastate.hpp"
#include "global.hpp"
#include "messages.hpp"
#include "intersector.hpp"
#include <fea/userinterface.hpp>

HangmanAState::HangmanAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mBackground({1024.0f, 768.0f}),
    mBackButton({206.0f, 100.0f}),
    mRQuad({50.0f, 76.0f}),
    mEQuad({50.0f, 76.0f}),
    mY1Quad({50.0f, 76.0f}),
    mK1Quad({50.0f, 76.0f}),
    mY2Quad({50.0f, 76.0f}),
    mAQuad({50.0f, 76.0f}),
    mVQuad({50.0f, 76.0f}),
    mIQuad({50.0f, 76.0f}),
    mK2Quad({50.0f, 76.0f}),
    mWrongQuad({150.0f, 250.0f}),
    mRightAmount(0),
    mWrongAmount(0)
{
    mBackgroundTexture = makeTexture(gTextures.at("hangman_bg"));
    mBackground.setTexture(mBackgroundTexture);

    mBackButtonTexture = makeTexture(gTextures.at("back_button"));
    mBackButton.setTexture(mBackButtonTexture);
    mBackButton.setPosition({35.0f, 640.0f});

    mWrong1Texture = makeTexture(gTextures.at("wrong1"));
    mWrong2Texture = makeTexture(gTextures.at("wrong2"));
    mWrong3Texture = makeTexture(gTextures.at("wrong3"));

    mRTexture = makeTexture(gTextures.at("r"));
    mRQuad.setTexture(mRTexture);
    mETexture = makeTexture(gTextures.at("e"));
    mEQuad.setTexture(mETexture);
    mYTexture = makeTexture(gTextures.at("y"));
    mY1Quad.setTexture(mYTexture);
    mY2Quad.setTexture(mYTexture);
    mKTexture = makeTexture(gTextures.at("k"));
    mK1Quad.setTexture(mKTexture);
    mK2Quad.setTexture(mKTexture);
    mATexture = makeTexture(gTextures.at("a"));
    mAQuad.setTexture(mATexture);
    mVTexture = makeTexture(gTextures.at("v"));
    mVQuad.setTexture(mVTexture);
    mITexture = makeTexture(gTextures.at("i"));
    mIQuad.setTexture(mITexture);

    mRQuad.setPosition({-100.0f, 76.0f});
    mEQuad.setPosition({-100.0f, 76.0f});
    mY1Quad.setPosition({-100.0f, 76.0f});
    mK1Quad.setPosition({-100.0f, 76.0f});
    mY2Quad.setPosition({-100.0f, 76.0f});
    mAQuad.setPosition({-100.0f, 76.0f});
    mVQuad.setPosition({-100.0f, 76.0f});
    mIQuad.setPosition({-100.0f, 76.0f});
    mK2Quad.setPosition({-100.0f, 76.0f});
    mWrongQuad.setPosition({739.0f, 250.0f});
}

void HangmanAState::update()
{
}

void HangmanAState::render()
{
    mRenderer.queue(mBackground);
    mRenderer.queue(mBackButton);

    mRenderer.queue(mRQuad);
    mRenderer.queue(mEQuad);
    mRenderer.queue(mY1Quad);
    mRenderer.queue(mK1Quad);
    mRenderer.queue(mY2Quad);
    mRenderer.queue(mAQuad);
    mRenderer.queue(mVQuad);
    mRenderer.queue(mIQuad);
    mRenderer.queue(mK2Quad);
    if(mWrongAmount > 0)
        mRenderer.queue(mWrongQuad);
}

void HangmanAState::handleMouseMove(const glm::uvec2& position)
{
    (void)position;
}

void HangmanAState::handleMouseClick(const glm::uvec2& position)
{
    if(intersects(position, mBackButton))
    {
        mIsFinished = true;
        if(mGuesses.size() > 3)
            mBus.send(MissNumberMessage());
    }
}

void HangmanAState::handleMouseRelease(const glm::uvec2& position)
{
    (void)position;
}

void HangmanAState::handleKeyPressed(int32_t key)
{
    if(mGuesses.count(key) == 0 && mWrongAmount < 3)
    {
        if(key == fea::Keyboard::R)
        {
            mRightAmount++;
            mRQuad.setPosition({364.0f, 570.0f});
        }
        else if(key == fea::Keyboard::E)
        {
            mRightAmount++;
            mEQuad.setPosition({424.0f, 570.0f});
        }
        else if(key == fea::Keyboard::Y)
        {
            mRightAmount++;
            mY1Quad.setPosition({504.0f, 570.0f});
            mY2Quad.setPosition({635.0f, 570.0f});
        }
        else if(key == fea::Keyboard::K)
        {
            mRightAmount++;
            mK1Quad.setPosition({562.0f, 570.0f});
            mK2Quad.setPosition({909.0f, 570.0f});
        }
        else if(key == fea::Keyboard::A)
        {
            mRightAmount++;
            mAQuad.setPosition({711.0f, 570.0f});
        }
        else if(key == fea::Keyboard::V)
        {
            mRightAmount++;
            mVQuad.setPosition({774.0f, 570.0f});
        }
        else if(key == fea::Keyboard::I)
        {
            mRightAmount++;
            mIQuad.setPosition({833.0f, 570.0f});
        }
        else
        {
            mWrongAmount++;

            if(mWrongAmount == 1)
                mWrongQuad.setTexture(mWrong1Texture);
            else if(mWrongAmount == 2)
                mWrongQuad.setTexture(mWrong2Texture);
            else if(mWrongAmount == 3)
                mWrongQuad.setTexture(mWrong3Texture);
        }

        mGuesses.emplace(key);
    }
}
