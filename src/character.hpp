#include "behaviouralstate.hpp"
#include "glm.hpp"
#include <memory>
#include <fea/render2d.hpp>

class Character
{
    public:
        Character(glm::vec2 spritePos, bool interactive, std::shared_ptr<BehaviouralState> initialBehaviour);
        const fea::AnimatedQuad& getSprite();

    private:
        glm::vec2 mSpritePosition;
        //glm::vec2 mClickablePosition;
        bool mInteractive;
        // id mInteractionActivityStateId;
        std::shared_ptr<BehaviouralState> mCurrentBehaviouralState;
        fea::AnimatedQuad mSprite;
};
