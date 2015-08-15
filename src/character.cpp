#include "character.hpp"

Character::Character(glm::vec2 spritePos, bool interactive, std::shared_ptr<BehaviouralState> initialBehaviour, const fea::Texture& texture, glm::vec2 spriteSize) :
    mSpritePosition(spritePos),
    mInteractive(interactive),
    mCurrentBehaviouralState(initialBehaviour)
{
    mSprite.setTexture(texture);
    mSprite.setSize(spriteSize);
    mSprite.setPosition(mSpritePosition);
    fea::Animation hej = fea::Animation(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), 1, 8);
    mSprite.setAnimation(hej);
}

const fea::AnimatedQuad& Character::getSprite()
{
    return mSprite;
}

void Character::setAnimation(const fea::Animation& anim)
{
    mSprite.setAnimation(anim);
}

void Character::update()
{
    mSprite.tick();
}
