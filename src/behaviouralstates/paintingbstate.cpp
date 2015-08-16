#include "paintingbstate.hpp"
#include "../global.hpp"
#include "../messages.hpp"

PaintingBState::PaintingBState(fea::MessageBus& bus) :
    BehaviouralState(bus)
{
    mVelocity = glm::vec2(0.0f, 0.0f);
    mAnimationType = "idle-front";
    //mBus.sendMusicMessageThingy("idlemusic");
}

void PaintingBState::switchTo()
{
    const fea::Animation& anim = getAnimation(mCharacter->mCharacterType, mAnimationType);
    mCharacter->getSprite().setAnimation(anim);
    mSwitchedTo = true;
}

void PaintingBState::update()
{
    mFinished = true;
    onFinish();
}

void PaintingBState::onFinish()
{
    //mBus.send(StartMinigameMessage{"take_ticket"});
    mBus.send(StartMinigameMessage{"painting"});
}
