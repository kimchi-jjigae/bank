#include "crosswordbstate.hpp"
#include "../global.hpp"
#include "../messages.hpp"

CrosswordBState::CrosswordBState(fea::MessageBus& bus) :
    BehaviouralState(bus)
{
    mVelocity = glm::vec2(0.0f, 0.0f);
    mAnimationType = "idle-front";
    //mBus.sendMusicMessageThingy("idlemusic");
}

void CrosswordBState::switchTo()
{
    const fea::Animation& anim = getAnimation(mCharacter->mCharacterType, mAnimationType);
    mCharacter->getSprite().setAnimation(anim);
    mSwitchedTo = true;
}

void CrosswordBState::update()
{
    mFinished = true;
    onFinish();
}

void CrosswordBState::onFinish()
{
    mBus.send(StartMinigameMessage{"crossword"});
}
