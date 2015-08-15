#include "character.hpp"
#include "behaviouralstate.hpp"
#include <iostream>

Character::Character(glm::vec2 spritePos, bool interactive, std::shared_ptr<BehaviouralState> initialBehaviour, const fea::Texture& texture, glm::vec2 spriteSize, fea::Animation anim) :
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

std::deque<std::shared_ptr<BehaviouralState>>& Character::getBehaviouralStates()
{
    return mBehaviouralStates;
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
    std::shared_ptr<BehaviouralState> state = mBehaviouralStates.front();
    if(!state->mSwitchedTo)
    {
        state->switchTo();
    }
    state->update();
}
