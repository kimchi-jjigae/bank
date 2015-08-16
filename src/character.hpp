#pragma once
#include "glm.hpp"
#include <memory>
#include <queue>
#include <fea/render2d.hpp>

class BehaviouralState;

class Character
{
    public:
        Character(std::string characterType, glm::vec2 spritePos, bool interactive, const fea::Texture& texture, glm::vec2 spriteSize, const fea::Animation& anim);
        const fea::AnimatedQuad& getSprite() const;
        fea::AnimatedQuad& getSprite();
        std::deque<std::shared_ptr<BehaviouralState>>& getBehaviouralStates();
        void update();
        glm::vec2 getPosition();
        void setPosition(glm::vec2 pos);
        std::string mCharacterType;
        void clearBehaviours();
        void pushBehaviour(std::shared_ptr<BehaviouralState> state);

    private:
        //glm::vec2 mClickablePosition;
        bool mInteractive;
        // id mInteractionActivityStateId;
        std::deque<std::shared_ptr<BehaviouralState>> mBehaviouralStates;
        fea::AnimatedQuad mSprite;
};
