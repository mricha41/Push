#include "gameplay/Ghost.hpp"

using namespace pk;

Ghost::Ghost(b2World* world, GLTexture& texture, GLRect rect, steer::BehaviorParameters* params)
:
    m_world(world),
    m_sprite(texture, {0.f, 0.f, rect.d_width, rect.d_height}),
    m_body(world, {rect.d_top, rect.d_left, rect.d_width, rect.d_height}),
    m_seek(params),
    m_chaseSpeed(params->SeekWeight)
{
    m_seek.setWeight(params->SeekWeight);
    m_seek.setPosition({rect.d_left, rect.d_top});

    m_body.setFriction(1.f);
    m_body.setDensity(1.f);
    m_body.setRestitution(0.f);

    m_sprite.setPosition(m_body.getPositionInPixels());
    m_sprite.setScale(pk::Game::getScalingFactor());
}

Ghost::~Ghost()
{

}

void Ghost::update(float dt, const glm::vec2& target)
{
    m_seek.Update(dt);
    m_seek.setTarget({target.x/pk::Game::getScalingFactor().x, target.y/pk::Game::getScalingFactor().y});

    b2Vec2 v = physics::pixelsToMeters({m_seek.getVelocity().x, m_seek.getVelocity().y});
    m_body.setLinearVelocity({v.x, v.y});

    m_sprite.setPosition(m_body.getPositionInPixels()*pk::Game::getScalingFactor());
}
