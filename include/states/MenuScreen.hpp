#ifndef MENUSCREEN_HPP
#define MENUSCREEN_HPP

#include "core/Game.hpp"
#include "states/ScreenState.hpp"
#include "graphics/Sprite.hpp"
#include "graphics/Text.hpp"

///////////////////////////////////////////////////////////////
/// \class MenuScreen
/// \brief SceenState subclass used for the Menu state.
//////////////////////////////////////////////////////////////
class MenuScreen : public pk::ScreenState
{
    public:
        /////////////////////////////////////////////
        /// \fn MenuScreen()
        /// \brief Default constructor.
        /////////////////////////////////////////////
        MenuScreen();
        virtual ~MenuScreen();

        enum menuState
        {
            s_uninitialized,
            s_running,
            s_play,
            s_options,
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
        pk::Texture m_texture;
        pk::Sprite m_sprite;
        pk::Font m_font;
        pk::Texture m_textTexture;
        pk::Texture m_textTextureOutline;
        pk::Text m_screenTitle;
        bool m_running;
        Mix_Music* m_music;
        Mix_Chunk* m_selectSound;
        Mix_Chunk* m_selectedSound;
};

#endif // MENUSCREEN_HPP
