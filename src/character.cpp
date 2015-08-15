#include "character.hpp"
#include "behaviouralstate.hpp"

Character::Character(glm::vec2 spritePos, bool interactive, std::shared_ptr<BehaviouralState> initialBehaviour, const fea::Texture& texture, glm::vec2 spriteSize, fea::Animation anim) :
    mSpritePosition(spritePos),
    mInteractive(interactive)
{
    mSprite.setTexture(texture);
    mSprite.setSize(spriteSize);
    mSprite.setPosition(mSpritePosition);
    initialBehaviour->setOwner(this);
    mBehaviouralStates.push_back(initialBehaviour);
    mSprite.setAnimation(anim);
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
}

void Character::update()
{
    mSprite.tick();
    mBehaviouralStates.front()->update();
}
