#include "gameplay/CharacterController.hpp"

#include "physics/SensorData.hpp"

#include <cmath>

using namespace pk;

CharacterController::CharacterController(b2World* world, GLTexture& texture, int player, GLRect rect)
:
    m_world(world),
    m_sprite(texture, {0.f, 0.f, rect.d_width, rect.d_height}),
    m_body(world, {rect.d_top, rect.d_left, rect.d_width - 2.f, rect.d_height - 2.f}, player),
    m_bulletTexture("images/ammo/shot.png"),
    m_controller(player),
    m_playerID(player),
    m_deaths(0)
{
    m_body.setFriction(0.9f);
    m_body.setDensity(0.5f);
    m_body.setRestitution(0.1f);

    m_pressedFire = false;
    m_pressedJump = false;
    m_pressedLeft = false;
    m_pressedRight= false;
    m_pressedUp   = false;
    m_pressedDown = false;
    m_pressedLeftTrigger = false;
    m_pressedRightTrigger = false;
    m_pressedLeftShoulder = false;
    m_pressedRightShoulder = false;
    m_facingDirection = 1;
    m_fireCounter = 0;
    m_fireTime = 0;
    m_fireDelay = 10;
    m_fireVelocity = 40.f;
    m_fireLifetime = 4000;
    m_velocity = 7.5f;
    m_jumpTime = 0;
    m_jumpDelay = 250;
    m_jumpVelocity = -25.f;
    m_dashVelocity = 35.f;

    m_pressedPause = false;
    m_paused = false;
    m_pauseTimer = 0;

    m_sprite.setPosition({m_body.getPositionInPixels().x - 2.f, m_body.getPositionInPixels().y - 2.f});
    m_sprite.setScale(pk::Game::getScalingFactor());

    m_shotSound = Mix_LoadWAV("sound/shot.wav");
    Mix_VolumeChunk(m_shotSound, pk::Game::getSoundEffectVolume());

    m_jumpSound = Mix_LoadWAV("sound/jump.wav");
    Mix_VolumeChunk(m_jumpSound, pk::Game::getSoundEffectVolume());

    m_dashSound = Mix_LoadWAV("sound/dash.wav");
    Mix_VolumeChunk(m_dashSound, pk::Game::getSoundEffectVolume());

    m_diedSound = Mix_LoadWAV("sound/crush.wav");
    Mix_VolumeChunk(m_diedSound, pk::Game::getSoundEffectVolume());
}

CharacterController::~CharacterController()
{
    Mix_FreeChunk(m_shotSound);
    m_shotSound = nullptr;

    Mix_FreeChunk(m_jumpSound);
    m_jumpSound = nullptr;
}

void CharacterController::BeginContact(b2Contact* contact)
{
    SensorData* fixtureUserDataA = static_cast<SensorData*>(contact->GetFixtureA()->GetUserData());
    SensorData* fixtureUserDataB = static_cast<SensorData*>(contact->GetFixtureB()->GetUserData());
    if(fixtureUserDataA)
    {
        fixtureUserDataA->contactMade();
    }

    if(fixtureUserDataB)
    {
        fixtureUserDataB->contactMade();
    }
}

void CharacterController::EndContact(b2Contact* contact)
{
    SensorData* fixtureUserDataA = static_cast<SensorData*>(contact->GetFixtureA()->GetUserData());
    SensorData* fixtureUserDataB = static_cast<SensorData*>(contact->GetFixtureB()->GetUserData());
    if(fixtureUserDataA)
    {
        fixtureUserDataA->contactEnded();
    }

    if(fixtureUserDataB)
    {
        fixtureUserDataB->contactEnded();
    }
}

void CharacterController::died(glm::vec2 pos){
    ++m_deaths;
    m_body.setLinearVelocity({0.f, 0.f});
    m_body.setPosition(pos*physics::MPP);
    Mix_PlayChannel(-1, m_diedSound, 0);
}

void CharacterController::handleInput()
{
        if(m_controller.getAxisState(pk::GameControllerAxis::LEFT_X) > 8000
           || m_controller.getButtonState(pk::GameControllerButton::DPAD_RIGHT) == 1)
        {
            m_pressedRight = true;
            m_facingDirection = 1;
        }

        if(m_controller.getAxisState(pk::GameControllerAxis::LEFT_X) < 8000
           && m_controller.getButtonState(pk::GameControllerButton::DPAD_RIGHT) == 0)
        {
            m_pressedRight = false;
        }

        if(m_controller.getAxisState(pk::GameControllerAxis::LEFT_X) < -8000
           || m_controller.getButtonState(pk::GameControllerButton::DPAD_LEFT) == 1)
        {
            m_pressedLeft = true;
            m_facingDirection = -1;
        }

        if(m_controller.getAxisState(pk::GameControllerAxis::LEFT_X) > -8000
           && m_controller.getButtonState(pk::GameControllerButton::DPAD_LEFT) == 0)
        {
            m_pressedLeft = false;
        }

        if(m_controller.getButtonState(pk::GameControllerButton::A) == 1)
        {
            m_jumpTime = SDL_GetTicks();
            m_pressedJump = true;
        }

        if(m_controller.getButtonState(pk::GameControllerButton::A) == 0)
        {
            m_pressedJump = false;
        }

        if(m_controller.getButtonState(pk::GameControllerButton::X) == 1)
        {
            if(SDL_GetTicks() - m_fireTime > m_fireDelay)
            {
                m_pressedFire = true;
            }
            //m_fireTime = SDL_GetTicks();
            //m_pressedFire = true;
        }

        if(m_controller.getButtonState(pk::GameControllerButton::X) == 0)
        {
            m_fireTime = SDL_GetTicks();
            m_pressedFire = false;
            m_fireCounter = 0;
            /*if(SDL_GetTicks() - m_fireTime > m_fireDelay)
            {
                m_pressedFire = false;
                m_fireCounter = 0;
            }*/
        }

        if(m_controller.getButtonState(pk::GameControllerButton::LEFT_SHOULDER) == 1)
        {
            m_pressedLeftShoulder = true;
        }

        if(m_controller.getButtonState(pk::GameControllerButton::LEFT_SHOULDER) == 0)
        {
            m_pressedLeftShoulder = false;
        }

        if(m_controller.getButtonState(pk::GameControllerButton::RIGHT_SHOULDER) == 1)
        {
            m_pressedRightShoulder = true;
        }

        if(m_controller.getButtonState(pk::GameControllerButton::RIGHT_SHOULDER) == 0)
        {
            m_pressedRightShoulder = false;
        }

        if(m_controller.getAxisState(pk::GameControllerAxis::TRIGGER_LEFT) > 0)
        {
            m_pressedLeftTrigger = true;
        }

        if(m_controller.getAxisState(pk::GameControllerAxis::TRIGGER_LEFT) <= 0)
        {
            m_pressedLeftTrigger = false;
        }

        if(m_controller.getAxisState(pk::GameControllerAxis::TRIGGER_RIGHT) > 0)
        {
            m_pressedRightTrigger = true;
        }

        if(m_controller.getAxisState(pk::GameControllerAxis::TRIGGER_RIGHT) <= 0)
        {
            m_pressedRightTrigger = false;
        }

        if(m_controller.getButtonState(pk::GameControllerButton::START) == 1)
        {
            m_pauseTimer = SDL_GetTicks();
            m_pressedPause = true;
        }

        if(m_controller.getButtonState(pk::GameControllerButton::START) == 0)
        {
            //offset just enough to prevent flickering
            if(SDL_GetTicks() - m_pauseTimer > 10 && m_pressedPause)
                m_paused = !m_paused;

            m_pressedPause = false;
        }
}

void CharacterController::update()
{
    if(m_pressedRight)
    {
        m_body.setLinearVelocity({m_velocity, m_body.getLinearVelocity().y});
    }

    if(m_pressedLeft)
    {
        m_body.setLinearVelocity({-m_velocity, m_body.getLinearVelocity().y});
    }

    if(m_pressedJump)
    {
        if(SDL_GetTicks() - m_jumpTime < m_jumpDelay && m_body.canJump())
        {
            Mix_PlayChannel(-1, m_jumpSound, 0);
            m_body.setLinearVelocity({m_body.getLinearVelocity().x, m_jumpVelocity});
        }
    }

    if(m_pressedRightShoulder)
    {
        Mix_PlayChannel(-1, m_dashSound, 0);
        m_body.setLinearVelocity({m_dashVelocity, m_body.getLinearVelocity().y});
    }

    if(m_pressedLeftShoulder)
    {
        Mix_PlayChannel(-1, m_dashSound, 0);
        m_body.setLinearVelocity({-m_dashVelocity, m_body.getLinearVelocity().y});
    }

    if(m_pressedFire)
    {
        m_fireCounter++;

        if(m_fireCounter == 1)
        {
            Mix_PlayChannel(-1, m_shotSound, 0);
            pk::Bullet bullet(m_world, m_bulletTexture, {0.f, 0.f, 16.f, 16.f}, m_fireLifetime);
            if(m_facingDirection == 1)
            {
                bullet.setPosition({m_body.getPosition().x + 0.25f, m_body.getPosition().y});
            }
            else if(m_facingDirection == -1)
            {
                bullet.setPosition({m_body.getPosition().x - 0.25f, m_body.getPosition().y});
            }

            bullet.fire(m_facingDirection*m_fireVelocity);
            m_bullets.push_back(bullet);
        }
    }

    //destroy bullets if time has elapsed
    if(m_bullets.size() > 0)
    {
        m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), [](pk::Bullet& b){
                return b.isAlive();
            }),
        m_bullets.end());
    }

    //update transforms
    m_sprite.setPosition(m_body.getPositionInPixels()*pk::Game::getScalingFactor());
    //flip based on facing direction
    //m_sprite.scale({(float)m_facingDirection, 1.f});
}
