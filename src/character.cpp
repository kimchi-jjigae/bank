#include "character.hpp"

Character::Character(glm::vec2 spritePos, bool interactive, std::shared_ptr<BehaviouralState> initialBehaviour) :
    mSpritePosition(spritePos),
    mInteractive(interactive),
    mCurrentBehaviouralState(initialBehaviour)
{
}

const fea::AnimatedQuad& Character::getSprite()
{
    return mSprite;
}
