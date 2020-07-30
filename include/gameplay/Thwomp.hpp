#ifndef THWOMP_HPP
#define THWOMP_HPP

#include "physics/KinematicBody.hpp"
#include "graphics/GLSprite.hpp"

namespace pk
{

class Thwomp
{
    public:
        Thwomp();

        Thwomp(b2World* world, GLTexture& texture, GLRect rect, glm::vec2 crushPosition, float crushSpeed);
        virtual ~Thwomp();

        pk::GLSprite& getSprite(){ return m_sprite; };

        void setCrushingSpeed(float speed){ m_crushingSpeed = speed; };

        void update();

    private:
        b2World* m_world;
        pk::KinematicBody m_body;
        pk::GLSprite m_sprite;
        int m_direction;
        glm::vec2 m_initialPosition;
        glm::vec2 m_crushPosition;
        float m_crushingSpeed;
};

}

#endif // THWOMP_HPP
