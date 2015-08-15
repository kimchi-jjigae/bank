#include "behaviouralstate.hpp"
#include "glm.hpp"
#include <memory>
#include <queue>
#include <fea/render2d.hpp>

class Character
{
    public:
        Character(glm::vec2 spritePos, bool interactive, std::shared_ptr<BehaviouralState> initialBehaviour, const fea::Texture& texture, glm::vec2 spriteSize, const fea::Animation& anim);
        const fea::AnimatedQuad& getSprite();
        void update();

    private:
        glm::vec2 mSpritePosition;
        //glm::vec2 mClickablePosition;
        bool mInteractive;
        // id mInteractionActivityStateId;
        std::queue<std::shared_ptr<BehaviouralState>> mBehaviouralStates;
        fea::AnimatedQuad mSprite;
};
