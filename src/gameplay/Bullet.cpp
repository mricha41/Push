#include "gameplay/Bullet.hpp"

#include "core/Game.hpp"

using namespace pk;

Bullet::Bullet(b2World* world, GLTexture& texture, GLRect rect, float delay)
:
    m_world(world),
    m_body(m_world, {rect.d_top, rect.d_left, rect.d_width/2.f, rect.d_height/2.f}),
    m_bulletSprite(new GLSprite(texture, rect)),
    m_aliveTime(SDL_GetTicks()),
    m_destroyDelay(delay)
{
    m_body.setDensity(1000.f);
    m_body.setFriction(0.0f);
    m_body.setRestitution(0.5f);
}

Bullet::~Bullet()
{

}

glm::vec2 Bullet::getPosition()
{
    return m_body.getPositionInPixels();
}

void Bullet::setPosition(glm::vec2 position)
{
    m_body.setTransform({position.x, position.y}, getRotation());
    m_bulletSprite->setPosition(m_body.getPositionInPixels()*pk::Game::getScalingFactor());
}

void Bullet::setVelocity(glm::vec2 velocity)
{
    m_body.setLinearVelocity({velocity.x, velocity.y});
}

glm::vec2 Bullet::getVelocity()
{
    return {m_body.getLinearVelocity().x, m_body.getLinearVelocity().y};
}

float Bullet::getRotation()
{
    return m_body.getRotation();
}

void Bullet::fire(float speed)
{
    m_body.setLinearVelocity({speed, getVelocity().y});
}

bool Bullet::isAlive()
{
    if((SDL_GetTicks() - m_aliveTime > m_destroyDelay))
    {
        m_body.destroyBody();
        if(m_bulletSprite)
            delete m_bulletSprite;
    }

    return (SDL_GetTicks() - m_aliveTime > m_destroyDelay);
}

void Bullet::update()
{
    m_bulletSprite->setPosition(m_body.getPositionInPixels()*pk::Game::getScalingFactor());
    m_bulletSprite->setAngle(getRotation());
}
