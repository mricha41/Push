#ifndef CHARACTERCONTROLLER_HPP
#define CHARACTERCONTROLLER_HPP

#include <vector>
#include <algorithm>

#include "core/Game.hpp"
#include "core/GameController.hpp"
#include "graphics/GLTexture.hpp"
#include "graphics/GLSprite.hpp"
#include "physics/CharacterBody.hpp"
#include "gameplay/Bullet.hpp"

namespace pk
{

class CharacterController : public b2ContactListener
{
    public:
        CharacterController();

        CharacterController(b2World* world, GLTexture& texture, int player, GLRect rect);

        virtual ~CharacterController();

        std::vector<pk::Bullet>& getBullets(){ return m_bullets; };

        bool requestPause(){ return m_paused; }

        void handleInput();

        void update();

        GLSprite& getSprite(){ return m_sprite; };

        glm::vec2 getPosition(){ return m_sprite.getPosition(); };

        int getPlayerID(){ return m_playerID; };

        void BeginContact(b2Contact* contact) override;

        void EndContact(b2Contact* contact) override;

        void died(glm::vec2 pos);
        void resetDeaths(){ m_deaths = 0; };
        int deaths(){ return m_deaths; };

    private:
        b2World* m_world;
        pk::GLSprite m_sprite;
        pk::CharacterBody m_body;
        pk::GLTexture m_bulletTexture;
        std::vector<pk::Bullet> m_bullets;

        pk::GameController m_controller;
        int m_playerID;
        int m_deaths;
        bool m_pressedFire;
        bool m_pressedJump;
        bool m_pressedLeft;
        bool m_pressedRight;
        bool m_pressedUp;
        bool m_pressedDown;
        bool m_pressedLeftTrigger;
        bool m_pressedRightTrigger;
        bool m_pressedLeftShoulder;
        bool m_pressedRightShoulder;
        int m_facingDirection;
        unsigned int m_fireCounter;
        double m_fireTime;
        double m_fireDelay;
        float m_fireVelocity;
        double m_fireLifetime;
        float m_velocity;
        double m_jumpTime;
        double m_jumpDelay;
        float m_jumpVelocity;
        float m_dashVelocity;
        bool m_pressedPause;
        bool m_paused;
        double m_pauseTimer;
        Mix_Chunk* m_shotSound;
        Mix_Chunk* m_jumpSound;
        Mix_Chunk* m_dashSound;
        Mix_Chunk* m_diedSound;
};

}

#endif // CHARACTERCONTROLLER_HPP
