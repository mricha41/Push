#include "gameplay/Thwomp.hpp"

#include "core/Game.hpp"

using namespace pk;

Thwomp::Thwomp(b2World* world, GLTexture& texture, GLRect rect, glm::vec2 crushPosition, float crushSpeed)
:
    m_world(world),
    m_sprite(texture, {0.f, 0.f, rect.d_width, rect.d_height}),
    m_body(world, {rect.d_top, rect.d_left, rect.d_width, rect.d_height})
{
    m_body.setFriction(1.f);
    m_body.setDensity(1.f);
    m_body.setRestitution(0.f);

    m_direction = 1;
    m_initialPosition = {rect.d_left, rect.d_top};
    m_crushPosition = {crushPosition.x, crushPosition.y + rect.d_height};
    m_crushingSpeed = crushSpeed;

    m_sprite.setPosition(m_body.getPositionInPixels());
    m_sprite.setScale(pk::Game::getScalingFactor());
}

Thwomp::~Thwomp()
{

}

void Thwomp::update()
{
    if(m_direction == 1)
    {
        if(m_body.getPosition().y < physics::pixelsToMeters(m_crushPosition).y)
            m_body.setLinearVelocity({0.f, m_crushingSpeed});
        else
            m_direction = -1;
    }

    if(m_direction == -1)
    {
        if(m_body.getPosition().y > physics::pixelsToMeters(m_initialPosition).y)
            m_body.setLinearVelocity({0.f, -m_crushingSpeed});
        else
            m_direction = 1;
    }

    m_sprite.setPosition(m_body.getPositionInPixels()*pk::Game::getScalingFactor());
}
