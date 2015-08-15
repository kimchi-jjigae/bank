#include "character.hpp"

Character::Character(glm::vec2 spritePos, bool interactive, std::shared_ptr<BehaviouralState> initialBehaviour, const fea::Texture& texture, glm::vec2 spriteSize, const fea::Animation& anim) :
    mSpritePosition(spritePos),
    mInteractive(interactive)
{
    mSprite.setTexture(texture);
    mSprite.setSize(spriteSize);
    mSprite.setPosition(mSpritePosition);
    mBehaviouralStates.push(initialBehaviour);
    mSprite.setAnimation(anim);

}

const fea::AnimatedQuad& Character::getSprite()
{
    return mSprite;
}

void Character::update()
{
    mSprite.tick();
    mBehaviouralStates.front()->update();
}
