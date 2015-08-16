#include "ticketbstate.hpp"
#include "../global.hpp"
#include "../messages.hpp"

TicketBState::TicketBState(fea::MessageBus& bus) :
    BehaviouralState(bus)
{
    mVelocity = glm::vec2(0.0f, 0.0f);
    mAnimationType = "idle-front";
    //mBus.sendMusicMessageThingy("idlemusic");
}

void TicketBState::switchTo()
{
    const fea::Animation& anim = getAnimation(mCharacter->mCharacterType, mAnimationType);
    mCharacter->getSprite().setAnimation(anim);
    mSwitchedTo = true;
}

void TicketBState::update()
{
    mFinished = true;
    onFinish();
}

void TicketBState::onFinish()
{
    mBus.send(StartMinigameMessage{"takenote"});
}
