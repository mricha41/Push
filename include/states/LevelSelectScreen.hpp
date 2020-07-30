#ifndef LEVELSELECTSCREEN_HPP
#define LEVELSELECTSCREEN_HPP

#include <vector>

#include "core/Game.hpp"
#include "states/ScreenState.hpp"
#include "graphics/GLTexture.hpp"
#include "graphics/GLSprite.hpp"

namespace pk
{

namespace levelSelection
{
    enum
    {
        UNINITIALIZED,
        RUNNING,
        SPIKES,
        ICE,
        DESERT,
        JUNGLE,
        CASTLE,
        FIRE,
        GREEN,
        PINK,
        PURPLE,
        EXIT
    };
}

///////////////////////////////////////////////////////////////
/// \class LevelSelectScreen
/// \brief ScreenState subclass used for the Level Select state.
//////////////////////////////////////////////////////////////
class LevelSelectScreen : public ScreenState
{
    public:
        /////////////////////////////////////////////
        /// \fn LevelSelectScreen()
        /// \brief Default constructor.
        /////////////////////////////////////////////
        LevelSelectScreen();
        virtual ~LevelSelectScreen();

        enum levelSelectState
        {
            s_uninitialized,
            s_running,
            s_spikes,
            s_ice,
            s_desert,
            s_jungle,
            s_castle,
            s_fireDungeon,
            s_greenDungeon,
            s_pinkDungeon,
            s_purpleDungeon,
            s_exit
        };

        /////////////////////////////////////////////
        /// \fn void display()
        /// \brief Display the LevelSelectScreen state in the window.
        /////////////////////////////////////////////
        void display() override;

        /////////////////////////////////////////////
        /// \fn virtual bool isRunning()
        /// \brief Check if LevelSelectScreen is running.
        /// \return bool - a plain old bool.
        /////////////////////////////////////////////
        virtual bool isRunning() override { return m_running; };

        void levelSelectionMade();

    private:
        bool m_running;
        Uint32 m_selection;
        Mix_Music* m_music;
        Mix_Chunk* m_selectSound;
        Mix_Chunk* m_selectedSound;
        GLTexture m_levelTexture;
        GLSprite m_levelSprite;
        GLTexture m_leftArrowTexture;
        GLTexture m_rightArrowTexture;
        GLSprite m_leftArrow;
        GLSprite m_rightArrow;
};

}

#endif // LEVELSELECTSCREEN_HPP
