#pragma once
#include "glm.hpp"
#include <memory>
#include <queue>
#include <fea/render2d.hpp>

class BehaviouralState;

class Character
{
    public:
        Character(std::string characterType, glm::vec2 spritePos, bool interactive, std::shared_ptr<BehaviouralState> initialBehaviour, const fea::Texture& texture, glm::vec2 spriteSize, fea::Animation anim);
        const fea::AnimatedQuad& getSprite();
        std::deque<std::shared_ptr<BehaviouralState>>& getBehaviouralStates();
        void update();
        glm::vec2 getPosition();
        void setPosition(glm::vec2 pos);

    private:
        std::string mCharacterType;
        glm::vec2 mSpritePosition;
        //glm::vec2 mClickablePosition;
        bool mInteractive;
        // id mInteractionActivityStateId;
        std::deque<std::shared_ptr<BehaviouralState>> mBehaviouralStates;
        fea::AnimatedQuad mSprite;
};
