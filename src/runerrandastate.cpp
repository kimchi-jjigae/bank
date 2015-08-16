#include "runerrandastate.hpp"
#include "global.hpp"
#include "messages.hpp"
#include "intersector.hpp"

RunErrandAState::RunErrandAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mBackground({1024.0f, 768.0f}),
    mBackButton({206.0f, 100.0f}),
    mArmUp({518.0f, 684.0f}),
    mArmDown({517.0f, 684.0f}),
    mExplosion({240.0f, 217.0f}),
    mChequeTable({106.0f, 33.0f}),
    mNote({50.0f, 50.0f}),
    mCover({1024.0f, 768.0f}),
    mHitting(false),
    mExplosionCounter(0),
    mHitCount(0),
    mNoteDown(false),
    mChequeDown(false),
    mNo(false),
    mNoCounter(180),
    mFade(false)
{
    mBackgroundTexture = makeTexture(gTextures.at("cashier"));
    mBackgroundTexture2 = makeTexture(gTextures.at("nocashier"));
    mBackground.setTexture(mBackgroundTexture);

    mBackButtonTexture = makeTexture(gTextures.at("back_button"));
    mBackButton.setTexture(mBackButtonTexture);
    mBackButton.setPosition({35.0f, 640.0f});

    mArmUpTexture = makeTexture(gTextures.at("arm_up"));
    mArmUp.setTexture(mArmUpTexture);
    mArmUp.setOrigin({450.0f, 183.0f});

    mArmDownTexture = makeTexture(gTextures.at("arm_down"));
    mArmDown.setTexture(mArmDownTexture);
    mArmDown.setOrigin({450.0f, 183.0f});

    mExplosionTexture = makeTexture(gTextures.at("explosion"));
    mExplosion.setTexture(mExplosionTexture);
    mExplosion.setOrigin({124.0f, 112.0f});

    mChequeTableTexture = makeTexture(gTextures.at("cheque_table"));
    mChequeTable.setTexture(mChequeTableTexture);
    mChequeTable.setPosition({372.0f, 690.0f});

    mNoteTexture = makeTexture(gTextures.at("queuenote"));
    mNote.setTexture(mNoteTexture);
    mNote.setPosition({674.0f, 684.0f});

    mBus.send(PlaySoundMessage{"sigh", false});

    mCover.setColor(fea::Color::Black);
    mCover.setOpacity(0.0f);
}

void RunErrandAState::update()
{
    //mBus.send(MissNumberMessage());
    if(mExplosionCounter > 0)
        mExplosionCounter--;

    if(!mNo && mNoteDown && mChequeDown)
    {
        mNoCounter--;

        if(mNoCounter == 0)
            mNo = true;
    }

    if(mFade)
    {
        float newOp = std::min(mCover.getOpacity() + 0.01f, 1.0f);
        mCover.setOpacity(newOp);
    }
}

void RunErrandAState::render()
{
    mRenderer.queue(mBackground);

    if(mChequeDown)
        mRenderer.queue(mChequeTable);
    if(mNoteDown)
        mRenderer.queue(mNote);

    if(mExplosionCounter > 0)
        mRenderer.queue(mExplosion);

    if(mNo)
    {
        if(!mHitting)
            mRenderer.queue(mArmUp);
        else
            mRenderer.queue(mArmDown);
    }


    mRenderer.queue(mBackButton);
    mRenderer.queue(mCover);
}

void RunErrandAState::handleMouseMove(const glm::uvec2& position)
{
    mArmUp.setPosition((glm::vec2)position);
    mArmDown.setPosition((glm::vec2)position);
}

void RunErrandAState::handleMouseClick(const glm::uvec2& position)
{
    if(intersects(position, mBackButton))
    {
        mIsFinished = true;

        if(mHitCount == 1)
            mBus.send(AdvanceQueueMessage());
        else if(mHitCount > 1)
            mBus.send(MissNumberMessage());
    }
    else
    {
        if(mNo)
        {
            mHitting = true;
            mFade = true;
            mBus.send(PlaySoundMessage{"punch", false});

            mExplosion.setPosition((glm::vec2)position);
            mExplosionCounter = 10;

            mHitCount++;
        }
        
        if(!mNoteDown)
        {
            mNoteDown = true;
        }
        else
        {
            if(!mChequeDown)
            {
                mChequeDown = true;
                mBackground.setTexture(mBackgroundTexture2); 
            }
        }
    }
}

void RunErrandAState::handleMouseRelease(const glm::uvec2& position)
{
    (void)position;
    mHitting = false;
}
