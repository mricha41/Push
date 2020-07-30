#ifndef GHOST_HPP
#define GHOST_HPP

#include "core/Game.hpp"
#include "physics/KinematicBody.hpp"
#include "graphics/GLSprite.hpp"
#include "steeriously/libinc.hpp"

namespace pk
{

class Ghost
{
    public:
        Ghost(b2World* world, GLTexture& texture, GLRect rect, steer::BehaviorParameters* params);
        virtual ~Ghost();

        pk::GLSprite& getSprite(){ return m_sprite; };

        void setChaseSpeed(float speed){ m_seek.setWeight(speed); };

        void update(float dt, const glm::vec2& target);

    private:
        b2World* m_world;
        pk::KinematicBody m_body;
        pk::GLSprite m_sprite;
        steer::SeekComponent m_seek;
        float m_chaseSpeed;
};

}

#endif // GHOST_HPP
