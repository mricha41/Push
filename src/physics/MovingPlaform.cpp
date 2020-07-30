#include "physics/MovingPlaform.hpp"

#include "core/Game.hpp"

using namespace pk;

MovingPlaform::MovingPlaform(b2World* world, GLTexture& texture, GLRect rect, glm::vec2 endPosition, float platformSpeed)
:
    m_world(world),
    m_sprite(texture, {0.f, 0.f, rect.d_width, rect.d_height}),
    m_body(world, {rect.d_top, rect.d_left, rect.d_width, rect.d_height})
{
    m_body.setFriction(1.f);
    m_body.setDensity(0.5f);
    m_body.setRestitution(0.1f);

    m_direction = 1;
    m_initialPosition = {rect.d_left, rect.d_top};
    m_endPosition = {endPosition.x, endPosition.y + rect.d_height};
    m_platformSpeed = platformSpeed;

    m_sprite.setPosition(m_body.getPositionInPixels()*pk::Game::getScalingFactor());
    m_sprite.setScale(pk::Game::getScalingFactor());
}

MovingPlaform::~MovingPlaform()
{

}

void MovingPlaform::update()
{
    if(m_direction == 1)
    {
        if(m_body.getPosition().x < physics::pixelsToMeters(m_endPosition).x)
            m_body.setLinearVelocity({m_platformSpeed, 0.f});
        else
            m_direction = -1;
    }

    if(m_direction == -1)
    {
        if(m_body.getPosition().x > physics::pixelsToMeters(m_initialPosition).x)
            m_body.setLinearVelocity({-m_platformSpeed, 0.f});
        else
            m_direction = 1;
    }

    m_sprite.setPosition(m_body.getPositionInPixels()*pk::Game::getScalingFactor());
    //m_sprite.setScale(pk::Game::getScalingFactor());
}
