#include "BeeColonyManager.hpp"

using namespace pk;

BeeColonyManager::BeeColonyManager(double chaseInterval)
:
    m_beeTexture("images/bee/bee.png")
{
    m_beeColonyParams.NumAgents = 1000;
    m_beeColonyParams.SteeringForce = 4.f;
    m_beeColonyParams.MaxSpeed = 1000.f;
    m_beeColonyParams.MaxForce = 4000.f;
    m_beeColonyParams.SeparationWeight = 100.f;
    m_beeColonyParams.AlignmentWeight = 1.f;
    m_beeColonyParams.CohesionWeight = 10.f;
    m_beesChaseP1 = false;
    m_beesChaseP2 = false;
    m_beesChaseP3 = false;
    m_beesChaseP4 = false;
    m_p1chaseTime = SDL_GetTicks();
    m_p2chaseTime = SDL_GetTicks();
    m_p3chaseTime = SDL_GetTicks();
    m_p4chaseTime = SDL_GetTicks();
    m_chaseDelay = chaseInterval;
    for(int i=0; i<4; ++i)
        m_beeColonies.push_back(new pk::BeeColony(m_beeTexture, {0.f, 0.f, 16.f, 16.f}, &m_beeColonyParams));

    for(auto& colony : m_beeColonies)
        colony->setWrap({pk::Game::getWindow()->getSize().x, pk::Game::getWindow()->getSize().y});
}

BeeColonyManager::~BeeColonyManager()
{
    for(auto& colony : m_beeColonies)
        delete colony;
}

void BeeColonyManager::update(float dt, pk::HUD* hud, pk::CharacterController* p1,
                                pk::CharacterController* p2, pk::CharacterController* p3,
                                pk::CharacterController* p4, std::vector<glm::vec2>& spawnZones)
{
    if(SDL_GetTicks() - m_p1chaseTime > m_chaseDelay)
    {
        m_beesChaseP1 = true;
        m_p1chaseTime = 0;
    }

    if(SDL_GetTicks() - m_p2chaseTime > m_chaseDelay)
    {
        m_beesChaseP2 = true;
        m_p2chaseTime = 0;
    }

    if(SDL_GetTicks() - m_p3chaseTime > m_chaseDelay)
    {
        m_beesChaseP3 = true;
        m_p3chaseTime = 0;
    }

    if(SDL_GetTicks() - m_p4chaseTime > m_chaseDelay)
    {
        m_beesChaseP4 = true;
        m_p4chaseTime = 0;
    }

    int colonyCount = 0;
    for(auto& colony : m_beeColonies)
    {
        switch(colonyCount)
        {
            case 0:
            {
                if(m_beesChaseP1)
                {
                    colony->setTarget(p1->getSprite().getPosition());
                    m_p1chaseTime = SDL_GetTicks();
                }
                else
                {
                    colony->setTarget({-400.f, -100.f});
                }
            }
            break;
            case 1:
            {
                if(m_beesChaseP2)
                {
                    colony->setTarget(p2->getSprite().getPosition());
                    m_p2chaseTime = SDL_GetTicks();
                }
                else
                {
                    colony->setTarget({-400.f, -100.f});
                }
            }
            break;
            case 2:
            {
                if(m_beesChaseP3)
                {
                    colony->setTarget(p3->getSprite().getPosition());
                    m_p3chaseTime = SDL_GetTicks();
                }
                else
                {
                    colony->setTarget({-400.f, -100.f});
                }
            }
            break;
            case 3:
            {
                if(m_beesChaseP4)
                {
                    colony->setTarget(p4->getSprite().getPosition());
                    m_p4chaseTime = SDL_GetTicks();
                }
                else
                {
                    colony->setTarget({-400.f, -100.f});
                }
            }
            break;
        default:
            break;
        }
        colony->update(dt);
        colonyCount++;
    }

    //check for player collisions
    float padding = 0.f;
    for(auto& colonies : m_beeColonies)
    {
        for(auto& bee : colonies->getColony())
        {
            if(m_beesChaseP1)
            {
                if(bee.getPosition().x > (p1->getSprite().getPosition().x + padding)
                        && bee.getPosition().x < (p1->getSprite().getPosition().x + (p1->getSprite().getWidth() - padding))
                        && bee.getPosition().y > (p1->getSprite().getPosition().y + padding)
                        && bee.getPosition().y < (p1->getSprite().getPosition().y + (p1->getSprite().getHeight() - padding)))
                {
                    p1->died(spawnZones[0]);
                    printf("p1 deaths: %i\n", p1->deaths());
                    hud->increaseDeaths(0, 1);
                    m_beesChaseP1 = false;
                }
            }

            if(m_beesChaseP2)
            {
                if(bee.getPosition().x > (p2->getSprite().getPosition().x + padding)
                        && bee.getPosition().x < (p2->getSprite().getPosition().x + (p2->getSprite().getWidth() - padding))
                        && bee.getPosition().y > (p2->getSprite().getPosition().y + padding)
                        && bee.getPosition().y < (p2->getSprite().getPosition().y + (p2->getSprite().getHeight() - padding)))
                {
                    p2->died(spawnZones[1]);
                    printf("p2 deaths: %i\n", p2->deaths());
                    hud->increaseDeaths(1, 1);
                    m_beesChaseP2 = false;
                }
            }

            if(m_beesChaseP3)
            {
                if(bee.getPosition().x > (p3->getSprite().getPosition().x + padding)
                        && bee.getPosition().x < (p3->getSprite().getPosition().x + (p3->getSprite().getWidth() - padding))
                        && bee.getPosition().y > (p3->getSprite().getPosition().y + padding)
                        && bee.getPosition().y < (p3->getSprite().getPosition().y + (p3->getSprite().getHeight() - padding)))
                {
                    p3->died(spawnZones[2]);
                    printf("p3 deaths: %i\n", p3->deaths());
                    hud->increaseDeaths(2, 1);
                    m_beesChaseP3 = false;
                }
            }

            if(m_beesChaseP4)
            {
                if(bee.getPosition().x > (p4->getSprite().getPosition().x + padding)
                        && bee.getPosition().x < (p4->getSprite().getPosition().x + (p4->getSprite().getWidth() - padding))
                        && bee.getPosition().y > (p4->getSprite().getPosition().y + padding)
                        && bee.getPosition().y < (p4->getSprite().getPosition().y + (p4->getSprite().getHeight() - padding)))
                {
                    p4->died(spawnZones[3]);
                    printf("p4 deaths: %i\n", p4->deaths());
                    hud->increaseDeaths(3, 1);
                    m_beesChaseP4 = false;
                }
            }
        }
    }
}

void BeeColonyManager::render(pk::GLStates& states)
{
    for(auto& colony : m_beeColonies)
        colony->render(states);
}
