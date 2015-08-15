#include "heartattackastate.hpp"
#include "global.hpp"
#include "messages.hpp"
#include "intersector.hpp"

HeartAttackAState::HeartAttackAState(fea::MessageBus& bus, fea::Renderer2D& renderer) :
    ActivityState(bus, renderer),
    mBackground({1024.0f, 768.0f}),
    mBackButton({206.0f, 100.0f}),
    mArmUp({518.0f, 684.0f}),
    mArmDown({517.0f, 684.0f}),
    mExplosion({240.0f, 217.0f}),
    mHitting(false),
    mExplosionCounter(0),
    mHitCount(0)
{
    mBackgroundTexture = makeTexture(gTextures.at("heartattack_bg"));
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

    mBus.send(PlaySoundMessage{"sigh"});
}

void HeartAttackAState::update()
{
    //mBus.send(MissNumberMessage());
    if(mExplosionCounter > 0)
        mExplosionCounter--;
}

void HeartAttackAState::render()
{
    mRenderer.queue(mBackground);

    if(mExplosionCounter > 0)
        mRenderer.queue(mExplosion);

    if(!mHitting)
        mRenderer.queue(mArmUp);
    else
        mRenderer.queue(mArmDown);

    mRenderer.queue(mBackButton);
}

void HeartAttackAState::handleMouseMove(const glm::uvec2& position)
{
    mArmUp.setPosition((glm::vec2)position);
    mArmDown.setPosition((glm::vec2)position);
}

void HeartAttackAState::handleMouseClick(const glm::uvec2& position)
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
        mHitting = true;
        mBus.send(PlaySoundMessage{"punch"});

        mExplosion.setPosition((glm::vec2)position);
        mExplosionCounter = 10;

        mHitCount++;
    }
}

void HeartAttackAState::handleMouseRelease(const glm::uvec2& position)
{
    mHitting = false;
}
