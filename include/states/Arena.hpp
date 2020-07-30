#ifndef ARENA_HPP
#define ARENA_HPP

#include <algorithm>
#include <string>

#include <csv/reader.hpp>

#include "steeriously/libinc.hpp"

#include "graphics/GLTexture.hpp"
#include "graphics/Shader.hpp"
#include "gameplay/Thwomp.hpp"
#include "physics/StaticPlatform.hpp"
#include "physics/MovingPlaform.hpp"
#include "gameplay/Ghost.hpp"
#include "gameplay/Walker.hpp"
#include "gameplay/BeeColonyManager.hpp"
#include "gameplay/CharacterController.hpp"

namespace pk
{

//forward declarations
class HUD;

class Arena
{
    public:
        Arena(b2World* world, std::string level);
        virtual ~Arena();

        void handleInput();

        void update(float dt);

        void render(pk::GLStates& states);

        void renderHUD();

        int getWinner()
        {
            std::vector<int> scores {m_p1->deaths(), m_p2->deaths(), m_p3->deaths(), m_p4->deaths()};
            int win = *std::min_element(scores.begin(), scores.end());
            if(win == m_p1->deaths())
                return 0;
            else if(win == m_p2->deaths())
                return 1;
            else if(win == m_p3->deaths())
                return 2;
            else if(win == m_p4->deaths())
                return 3;
        };

        bool requestPause(){ return (m_p1->requestPause() || m_p2->requestPause() || m_p3->requestPause() || m_p4->requestPause()); };

    private:
        b2World* m_world;
        std::string m_level;
        SDL_Window* m_SDLWindow;
        pk::Window* m_window;
        SDL_GLContext* m_context;
        GLTexture m_backgroundTexture;
        GLSprite m_backgroundSprite;
        csv::Reader m_platformData;
        std::vector<pk::StaticPlatform> m_platforms;
        pk::GLTexture m_shortPlatformTexture;
        pk::GLTexture m_mediumPlatformTexture;
        pk::GLTexture m_longPlatformTexture;
        csv::Reader m_specialPlatformData;
        std::vector<pk::MovingPlaform*> m_movingPlatforms;
        pk::GLTexture m_thwompTexture;
        csv::Reader m_thwompData;
        std::vector<pk::Thwomp*> m_thwomps;
        steer::BehaviorParameters m_fishParams;
        pk::GLTexture m_fishTexture;
        csv::Reader m_ghostData;
        std::vector<pk::Ghost*> m_fish;
        steer::BehaviorParameters m_groundEnemyParams;
        pk::GLTexture m_groundEnemyTexture;
        csv::Reader m_walkerData;
        std::vector<pk::Walker*> m_groundEnemies;
        pk::BeeColonyManager* m_beeManager;
        csv::Reader m_deathZoneData;
        std::vector<pk::GLRect> m_deathZones;
        csv::Reader m_spawnZoneData;
        std::vector<glm::vec2> m_spawnZones;
        pk::GLTexture m_playerOneTexture;
        pk::GLTexture m_playerTwoTexture;
        pk::GLTexture m_playerThreeTexture;
        pk::GLTexture m_playerFourTexture;
        pk::CharacterController* m_p1;
        pk::CharacterController* m_p2;
        pk::CharacterController* m_p3;
        pk::CharacterController* m_p4;
        pk::HUD* m_hud;
        pk::GLTexture m_controllerMappingTexture;
        pk::GLSprite m_controllerMapping;
};

}

#endif // ARENA_HPP
