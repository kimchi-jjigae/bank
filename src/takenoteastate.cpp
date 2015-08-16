#include "takenoteastate.hpp"
#include "global.hpp"
#include "messages.hpp"
#include "intersector.hpp"

TakeNoteAState::TakeNoteAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mBackground({1024.0f, 768.0f}),
    mBackButton({206.0f, 100.0f}),
    mNoteQuad({241.0f, 304.0f}),
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

    gPlayerQueueNumber = gQueueCounter + 5 + gBrokenNotes;

    gNoteBrokenState = 0;

    mNoteNumberTexture = makeTexture(gTextures.at("notenumbers"));
    mFirstNumber.setTexture(mNoteNumberTexture);
    mSecondNumber.setTexture(mNoteNumberTexture);

    std::string currentNumber;
    if(gQueueCounter < 10)
        currentNumber = "0";

    currentNumber.append(std::to_string(gPlayerQueueNumber));

    mFirstNumber.setAnimation(getAnimation("notenumber", std::string(1, currentNumber[0])));
    mFirstNumber.setPosition({482.0f, 456.0f});
    mSecondNumber.setPosition({482.0f + 37.0f, 456.0f + 22.0f});
    mSecondNumber.setAnimation(getAnimation("notenumber", std::string(1, currentNumber[1])));
}

void TakeNoteAState::update()
{
}

void TakeNoteAState::render()
{
    mRenderer.queue(mBackground);
    mRenderer.queue(mBackButton);
    mRenderer.queue(mNoteQuad);

    mRenderer.queue(mFirstNumber);
    mRenderer.queue(mSecondNumber);
}

void TakeNoteAState::handleMouseMove(const glm::uvec2& position)
{
    (void)position;
}

void TakeNoteAState::handleMouseClick(const glm::uvec2& position)
{
    if(intersects(position, mBackButton))
    {
        mIsFinished = true;
    }
}

void TakeNoteAState::handleMouseRelease(const glm::uvec2& position)
{
    (void)position;
}
