#include "BeeColony.hpp"

#include "core/Game.hpp"

using namespace pk;

BeeColony::BeeColony(GLTexture& texture, GLRect rect, steer::BehaviorParameters* params)
:
    m_target(),
    m_wrap(),
    m_bee(texture, rect)
{
    for(int i=0; i<params->NumAgents; ++i)
    {
        steer::SuperComponent bee(params);
        bee.flockingOn();
        bee.wallAvoidanceOff();
        bee.obstacleAvoidanceOff();
        bee.setTarget({400.0, 300.0});
        bee.setPosition({rect.d_left, rect.d_top});
        m_colony.push_back(bee);
        m_colonyPointers.push_back(&bee);
    }

    //set the neighbors in the colony
    for(auto& bee : m_colony)
    {
        bee.setNeighbors(&m_colonyPointers);
    }

    //actually looks more like bees at normal scale :D
    //m_bee.setScale(pk::Game::getScalingFactor());
}

BeeColony::~BeeColony()
{

}

void BeeColony::update(float dt)
{
    for(auto& bee : m_colony)
    {
        bee.Update(dt);
        bee.setTarget(m_target);
        WrapAround(bee.m_agentPosition, m_wrap.x, m_wrap.y);
    }
}

void BeeColony::render(GLStates& states)
{
    pk::Window* win = pk::Game::getWindow();
    for(auto& bee : m_colony)
    {
        m_bee.setPosition({bee.getPosition().x, bee.getPosition().y});
        m_bee.setAngle(bee.getRotation());
        win->draw(m_bee, states);
    }
}
