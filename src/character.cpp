#include "character.hpp"
#include "behaviouralstate.hpp"
#include <iostream>

Character::Character(std::string characterType, glm::vec2 spritePos, bool interactive, std::shared_ptr<BehaviouralState> initialBehaviour, const fea::Texture& texture, glm::vec2 spriteSize, const fea::Animation& anim) :
    mCharacterType(characterType),
    mSpritePosition(spritePos),
    mInteractive(interactive)
{
    mSprite.setTexture(texture);
    mSprite.setSize(spriteSize);
    mSprite.setPosition(mSpritePosition);
    initialBehaviour->setOwner(this);
    mBehaviouralStates.push_back(initialBehaviour);
    mSprite.setAnimation(anim);
    mSprite.setOrigin(glm::vec2(spriteSize.x / 2.0f, spriteSize.y));
}

const fea::AnimatedQuad& Character::getSprite()
{
    return mSprite;
}

fea::AnimatedQuad& Character::getSpriteRef()
{
    return mSprite;
}

std::deque<std::shared_ptr<BehaviouralState>>& Character::getBehaviouralStates()
{
    return mBehaviouralStates;
}

void Character::clearBehaviours()
{
    mBehaviouralStates.clear();
}

void Character::pushBehaviour(std::shared_ptr<BehaviouralState> state)
{
    mBehaviouralStates.push_back(state);
}

glm::vec2 Character::getPosition()
{
    return mSpritePosition;
}

void Character::setPosition(glm::vec2 pos)
{
    mSpritePosition = pos;
    mSprite.setPosition(mSpritePosition);
}

void Character::update()
{
    mSprite.tick();
    if(!mBehaviouralStates.empty())
    {
        std::shared_ptr<BehaviouralState> state = mBehaviouralStates.front();
        if(!state->mSwitchedTo)
        {
            state->setOwner(this);
            state->switchTo();
        }
        state->update();
    }
}
