#ifndef BEECOLONY_HPP
#define BEECOLONY_HPP

#include <vector>

#include "steeriously/libinc.hpp"

#include "graphics/GLTexture.hpp"
#include "graphics/GLSprite.hpp"

namespace pk
{

class BeeColony
{
    public:
        BeeColony(GLTexture& texture, GLRect rect, steer::BehaviorParameters* params);
        virtual ~BeeColony();

        std::vector<steer::SuperComponent> getColony(){ return m_colony; };

        void setWrap(glm::vec2 wrap){ m_wrap = {wrap.x, wrap.y}; };
        void setTarget(glm::vec2 target){ m_target = {target.x, target.y}; };

        void update(float dt);

        void render(GLStates& states);

    private:
        std::vector<steer::SuperComponent> m_colony;
        std::vector<steer::SuperComponent*> m_colonyPointers;
        steer::Vector2 m_target;
        steer::Vector2 m_wrap;
        GLSprite m_bee;
};

}

#endif // BEECOLONY_HPP
