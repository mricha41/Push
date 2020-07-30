#include "gameplay/Walker.hpp"

using namespace pk;

Walker::Walker(b2World* world, GLTexture& texture, GLRect rect, glm::vec2 endPosition, steer::BehaviorParameters* params)
:
    m_world(world),
    m_sprite(texture, {0.f, 0.f, rect.d_width, rect.d_height}),
    m_body(world, {rect.d_top, rect.d_left, rect.d_width, rect.d_height}),
    m_seek(params),
    m_direction(1),
    m_initialPosition({rect.d_left, rect.d_top}),
    m_endPosition({endPosition.x, endPosition.y + rect.d_height}),
    m_moveSpeed(params->SeekWeight)
{
    m_seek.setWeight(m_moveSpeed);
    m_seek.setPosition({rect.d_left, rect.d_top});

    m_body.setFriction(1.f);
    m_body.setDensity(1.f);
    m_body.setRestitution(0.f);

    m_sprite.setPosition(m_body.getPositionInPixels());
    m_sprite.setScale(pk::Game::getScalingFactor());
}

Walker::~Walker()
{

}

void Walker::update(float dt)
{
    m_seek.Update(dt);

    glm::vec2 p = {m_seek.getPosition().x, m_seek.getPosition().y};

    if(m_direction == 1)
    {
        if(p.x > m_endPosition.x)
            m_seek.setTarget({m_initialPosition.x, m_initialPosition.y});
        else
            m_direction = -1;
    }

    if(m_direction == -1)
    {
        if(p.x < m_initialPosition.x)
            m_seek.setTarget({m_endPosition.x, m_endPosition.y});
        else
            m_direction = 1;
    }

    b2Vec2 v = physics::pixelsToMeters({m_seek.getVelocity().x, m_seek.getVelocity().y});
    m_body.setLinearVelocity({v.x, 0.f});

    m_sprite.setPosition(m_body.getPositionInPixels()*pk::Game::getScalingFactor());
}
