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
    mBehaviouralStates.push(initialBehaviour);
    mSprite.setAnimation(anim);

}

const fea::AnimatedQuad& Character::getSprite()
{
    return mSprite;
}

std::queue<std::shared_ptr<BehaviouralState>>& Character::getBehaviouralStates()
{
    return mBehaviouralStates;
}

void Character::update()
{
    mSprite.tick();
    mBehaviouralStates.front()->update();
}
