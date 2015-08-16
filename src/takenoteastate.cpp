#include "takenoteastate.hpp"
#include "global.hpp"
#include "messages.hpp"
#include "intersector.hpp"

TakeNoteAState::TakeNoteAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mBackground({1024.0f, 768.0f}),
    mBackButton({206.0f, 100.0f}),
    mNoteQuad({241.0f, 304.0f})
{
    mBackgroundTexture = makeTexture(gTextures.at("handnotebg"));
    mBackground.setTexture(mBackgroundTexture);

    mBackButtonTexture = makeTexture(gTextures.at("back_button"));
    mBackButton.setTexture(mBackButtonTexture);
    mBackButton.setPosition({35.0f, 640.0f});

    mNoteTexture = makeTexture(gTextures.at("queuenote"));
    mNoteQuad.setTexture(mNoteTexture);
    mNoteQuad.setPosition({430.0f, 327.0f});

    mBus.send(PlaySoundMessage{"sigh", false});

    gPlayerQueueNumber = gQueueCounter + 5;
}

void TakeNoteAState::update()
{
}

void TakeNoteAState::render()
{
    mRenderer.queue(mBackground);
    mRenderer.queue(mBackButton);
    mRenderer.queue(mNoteQuad);
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
