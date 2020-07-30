#include "gameplay/SawBlade.hpp"

#include "core/Game.hpp"

using namespace pk;

SawBlade::SawBlade(GLTexture& texture, GLRect rect, float speed, steer::Path& path, steer::BehaviorParameters* params)
:
    m_sprite(texture, {0.f, 0.f, rect.d_width, rect.d_height}),
    m_path(path),
    m_pathFollowing(&m_path, params)
{
    m_sprite.setPosition({rect.d_left, rect.d_top});
    m_sprite.setScale(pk::Game::getScalingFactor());
    params->FollowPathWeight = speed;
    m_pathFollowing.setWeight(speed);
    m_path.loopOn();
}

SawBlade::~SawBlade()
{

}

void SawBlade::update(float dt)
{
    m_pathFollowing.Update(dt);

    m_sprite.setPosition({m_pathFollowing.getPosition().x*pk::Game::getScalingFactor().x, m_pathFollowing.getPosition().y*pk::Game::getScalingFactor().y});
}
