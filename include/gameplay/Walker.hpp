#ifndef WALKER_HPP
#define WALKER_HPP

#include "core/Game.hpp"
#include "physics/KinematicBody.hpp"
#include "graphics/GLSprite.hpp"
#include "steeriously/libinc.hpp"

namespace pk
{

class Walker
{
    public:
        Walker(b2World* world, GLTexture& texture, GLRect rect, glm::vec2 endPosition, steer::BehaviorParameters* params);
        virtual ~Walker();

        pk::GLSprite& getSprite(){ return m_sprite; };

        void setMoveSpeed(float speed){ m_seek.setWeight(speed); };

        void setTarget(glm::vec2 target){ m_seek.setTarget({target.x, target.y}); };

        void update(float dt);

    private:
        b2World* m_world;
        pk::KinematicBody m_body;
        pk::GLSprite m_sprite;
        steer::SeekComponent m_seek;
        int m_direction;
        glm::vec2 m_initialPosition;
        glm::vec2 m_endPosition;
        float m_moveSpeed;
};

}

#endif // WALKER_HPP
