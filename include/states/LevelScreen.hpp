#ifndef LEVELSCREEN_HPP
#define LEVELSCREEN_HPP

#include <stdio.h>
#include <vector>

#include <glm\gtc\type_ptr.hpp>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <Box2D/Box2D.h>

#include "core/Game.hpp"
#include "graphics/Camera.hpp"
#include "graphics/GLSprite.hpp"
#include "graphics/GLTexture.hpp"
#include "graphics/Shader.hpp"
#include "lighting/AmbientLight.hpp"
#include "lighting/DiffuseLight.hpp"
#include "lighting/Material.hpp"
#include "states/ScreenState.hpp"
#include "utilities/DisplayInfo.hpp"

namespace pk
{
    class HUD;
    class Arena;
}

///////////////////////////////////////////////////////////////
/// \class LevelScreen
/// \brief ScreenState subclass used for the Level state.
//////////////////////////////////////////////////////////////
class LevelScreen : public pk::ScreenState
{
    public:
        /////////////////////////////////////////////
        /// \fn LevelScreen()
        /// \brief Default constructor.
        /////////////////////////////////////////////
        LevelScreen();

        /////////////////////////////////////////////
        /// \fn LevelScreen(Uint32 level)
        /// \brief Construct from a selected level.
        /////////////////////////////////////////////
        LevelScreen(Uint32 level);
        virtual ~LevelScreen();

        enum levelState
        {
            s_uninitialized,
            s_running,
            s_menu,
            s_exit
        };

        /////////////////////////////////////////////
        /// \fn void display()
        /// \brief Display the menu screen state in the window.
        /////////////////////////////////////////////
        void display() override;

        /////////////////////////////////////////////
        /// \fn virtual bool isRunning()
        /// \brief Check if MenuScreen is running.
        /// \return bool
        /////////////////////////////////////////////
        virtual bool isRunning() override { return m_running; };

    private:
        bool m_running;
        Mix_Music* m_music;
        Uint32 m_levelToLoad;
        pk::Arena* m_arena;
        pk::GLTexture m_winnerTexture;
        pk::GLSprite m_winner;
        bool m_triggerOutro;
        double m_outroTime;
        double m_outroDelay;
        float m_outroSpeed;
        double m_matchTime;
        bool m_showWinner;
};

#endif // LEVELSCREEN_HPP
