#include "childquestionastate.hpp"
#include "global.hpp"
#include "messages.hpp"

ChildQuestionAState::ChildQuestionAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mCounter(600),
    mBackground({1024.0f, 768.0f}),
    mBackButton({206.0f, 100.0f}),
    mSayButton({120.0f, 80.0f}),
    mSadMouth({118.0f, 56.0f})
{
    mBackgroundTexture = makeTexture(gTextures.at("childquestion"));
    mBackground.setTexture(mBackgroundTexture);

    mBackButtonTexture = makeTexture(gTextures.at("back_button"));
    mBackButton.setTexture(mBackButtonTexture);
    mBackButton.setPosition({35.0f, 640.0f});

    mSayButtonTexture = makeTexture(gTextures.at("say_button"));
    mSayButton.setTexture(mSayButtonTexture);
    mSayButton.setPosition({609.0f, 640.0f});
    
    mSadMouthTexture = makeTexture(gTextures.at("sad_mouth"));
    mSadMouth.setTexture(mSadMouthTexture);
    mSadMouth.setPosition({154.0f, 570.0f});
}

void ChildQuestionAState::update()
{
    if(mCounter > 0)
        mCounter--;
}

void ChildQuestionAState::render()
{
    mRenderer.queue(mBackground);
    mRenderer.queue(mBackButton);
    mRenderer.queue(mSayButton);
    if(mCounter == 0)
        mRenderer.queue(mSadMouth);
}

void ChildQuestionAState::handleMouseMove(const glm::uvec2& position)
{
    (void)position;
}

void ChildQuestionAState::handleMouseClick(const glm::uvec2& position)
{
    if(intersects(position, mBackButton))
    {
        mIsFinished = true;

        if(mCounter == 0)
            mBus.send(AdvanceQueueMessage());
    }
    else if(intersects(position, mSayButton))
    {
        mIsFinished = true;
        mBus.send(MissNumberMessage());
    }
}

void ChildQuestionAState::handleMouseRelease(const glm::uvec2& position)
{
    (void)position;
}
