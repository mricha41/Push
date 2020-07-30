#ifndef BULLET_HPP
#define BULLET_HPP

#include <SDL2/SDL_timer.h>

#include "Box2D/Box2D.h"

#include "graphics/GLTransformable.hpp"
#include "physics/DynamicBody.hpp"
#include "graphics/GLSprite.hpp"

namespace pk
{

class Bullet
{
    public:
        Bullet();
        Bullet(b2World* world, GLTexture& texture, GLRect rect, float delay);
        virtual ~Bullet();

        void setVelocity(glm::vec2 velocity);

        glm::vec2 getVelocity();

        glm::vec2 getPosition();
        void setPosition(glm::vec2 position);

        float getRotation();

        void fire(float speed);

        bool isAlive();

        GLSprite& getSprite(){ return *m_bulletSprite; };

        void update();

    private:
        b2World* m_world;
        DynamicBody m_body;
        pk::GLSprite* m_bulletSprite;
        double m_aliveTime;
        double m_destroyDelay;
};

}

#endif // BULLET_HPP
