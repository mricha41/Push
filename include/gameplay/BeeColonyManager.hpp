#ifndef BEECOLONYMANAGER_HPP
#define BEECOLONYMANAGER_HPP

#include <vector>

#include "states/HUD.hpp"
#include "gameplay/CharacterController.hpp"
#include "gameplay/BeeColony.hpp"

namespace pk
{

class BeeColonyManager
{
    public:
        BeeColonyManager(double chaseInterval);
        virtual ~BeeColonyManager();

        void update(float dt, pk::HUD* hud, pk::CharacterController* p1, pk::CharacterController* p2,
                    pk::CharacterController* p3, pk::CharacterController* p4, std::vector<glm::vec2>& spawnZones);
        void render(pk::GLStates& states);

    private:
        steer::BehaviorParameters m_beeColonyParams;
        pk::GLTexture m_beeTexture;
        std::vector<pk::BeeColony*> m_beeColonies;
        bool m_beesChaseP1;
        bool m_beesChaseP2;
        bool m_beesChaseP3;
        bool m_beesChaseP4;
        double m_p1chaseTime;
        double m_p2chaseTime;
        double m_p3chaseTime;
        double m_p4chaseTime;
        double m_chaseDelay;
};

}

#endif // BEECOLONYMANAGER_HPP
