#include "sudokubstate.hpp"
#include "../global.hpp"
#include "../messages.hpp"

SudokuBState::SudokuBState(fea::MessageBus& bus) :
    BehaviouralState(bus)
{
    mVelocity = glm::vec2(0.0f, 0.0f);
    mAnimationType = "idle-front";
    //mBus.sendMusicMessageThingy("idlemusic");
}

void SudokuBState::switchTo()
{
    const fea::Animation& anim = getAnimation(mCharacter->mCharacterType, mAnimationType);
    mCharacter->getSprite().setAnimation(anim);
    mSwitchedTo = true;
}

void SudokuBState::update()
{
    mFinished = true;
    onFinish();
}

void SudokuBState::onFinish()
{
    mBus.send(StartMinigameMessage{"sudoku"});
}
