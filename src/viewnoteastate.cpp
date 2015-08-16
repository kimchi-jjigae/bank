#include "viewnoteastate.hpp"
#include "global.hpp"
#include "messages.hpp"
#include "intersector.hpp"

ViewNoteAState::ViewNoteAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mBackground({1024.0f, 768.0f}),
    mBackButton({206.0f, 100.0f}),
    mNoteQuad({241.0f, 304.0f}),
    mNoteBroken1Quad({71.0f, 82.0f}),
    mNoteBroken2Quad({150.0f, 127.0f}),
    mFirstNumber({57.0f, 57.0f}),
    mSecondNumber({57.0f, 57.0f})
{
    mBackgroundTexture = makeTexture(gTextures.at("handnotebg"));
    mBackground.setTexture(mBackgroundTexture);

    mBackButtonTexture = makeTexture(gTextures.at("back_button"));
    mBackButton.setTexture(mBackButtonTexture);
    mBackButton.setPosition({35.0f, 640.0f});

    mNoteTexture = makeTexture(gTextures.at("queuenote"));
    mNoteQuad.setTexture(mNoteTexture);
    mNoteQuad.setPosition({430.0f, 327.0f});

    mNoteBroken1Texture = makeTexture(gTextures.at("broken1"));
    mNoteBroken1Quad.setTexture(mNoteBroken1Texture);
    mNoteBroken1Quad.setPosition({470.0f, 407.0f});

    mNoteBroken2Texture = makeTexture(gTextures.at("broken2"));
    mNoteBroken2Quad.setTexture(mNoteBroken2Texture);
    mNoteBroken2Quad.setPosition({470.0f, 407.0f});

    mNoteNumberTexture = makeTexture(gTextures.at("notenumbers"));
    mFirstNumber.setTexture(mNoteNumberTexture);
    mSecondNumber.setTexture(mNoteNumberTexture);

    std::string currentNumber;
    if(gPlayerQueueNumber < 10)
        currentNumber = "0";

    currentNumber.append(std::to_string(gPlayerQueueNumber));

    mFirstNumber.setAnimation(getAnimation("notenumber", std::string(1, currentNumber[0])));
    mFirstNumber.setPosition({482.0f, 456.0f});
    mSecondNumber.setPosition({482.0f + 37.0f, 456.0f + 22.0f});
    mSecondNumber.setAnimation(getAnimation("notenumber", std::string(1, currentNumber[1])));
}

void ViewNoteAState::update()
{
}

void ViewNoteAState::render()
{
    mRenderer.queue(mBackground);
    mRenderer.queue(mBackButton);

    if(gNoteBrokenState != -1)
    {
        mRenderer.queue(mNoteQuad);

        if(gNoteBrokenState != -1)
        {
            mRenderer.queue(mFirstNumber);
            mRenderer.queue(mSecondNumber);
        }

        if(gNoteBrokenState == 1)
            mRenderer.queue(mNoteBroken1Quad);
        else if(gNoteBrokenState == 2)
            mRenderer.queue(mNoteBroken2Quad);
    }
}

void ViewNoteAState::handleMouseMove(const glm::uvec2& position)
{
    (void)position;
}

void ViewNoteAState::handleMouseClick(const glm::uvec2& position)
{
    if(intersects(position, mBackButton))
    {
        mIsFinished = true;
        if(gNoteBrokenState == 2)
        {
            gNoteBrokenState = -1;
            gBrokenNotes++;
        }
    }
    else if(intersects(position, mNoteQuad))
    {
        if(gNoteBrokenState == 0)
        {
            gNoteBrokenState++;
            mBus.send(PlaySoundMessage{"rip1", false});
        }
        else if(gNoteBrokenState == 1)
        {
            gNoteBrokenState++;
            mBus.send(PlaySoundMessage{"rip2", false});
        }
    }
}

void ViewNoteAState::handleMouseRelease(const glm::uvec2& position)
{
    (void)position;
}
