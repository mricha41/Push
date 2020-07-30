#ifndef CHARACTERSELECTSCREEN_HPP
#define CHARACTERSELECTSCREEN_HPP

#include "core/Game.hpp"
#include "states/ScreenState.hpp"
#include "graphics/GLTexture.hpp"
#include "graphics/GLSprite.hpp"

namespace pk
{

class CharacterSelectScreen : public ScreenState
{
    public:
        CharacterSelectScreen();
        virtual ~CharacterSelectScreen();

        enum characterSelectState
        {
            s_uninitialized,
            s_running,
            s_exit
        };

        /////////////////////////////////////////////
        /// \fn void display()
        /// \brief Display the CharacterSelectScreen state in the window.
        /////////////////////////////////////////////
        void display() override;

        /////////////////////////////////////////////
        /// \fn virtual bool isRunning()
        /// \brief Check if CharacterSelectScreen is running.
        /// \return bool - a plain old bool.
        /////////////////////////////////////////////
        virtual bool isRunning() override { return m_running; };

    private:
        bool m_running;
        Mix_Music* m_music;
        Mix_Chunk* m_selectSound;
        Mix_Chunk* m_selectionSound;
        Mix_Chunk* m_selectedSound;
        GLTexture m_p1LabelTexture;
        GLTexture m_p2LabelTexture;
        GLTexture m_p3LabelTexture;
        GLTexture m_p4LabelTexture;
        GLTexture m_playerOneTexture;
        GLTexture m_playerTwoTexture;
        GLTexture m_playerThreeTexture;
        GLTexture m_playerFourTexture;
        GLSprite m_playerOne;
        GLSprite m_playerTwo;
        GLSprite m_playerThree;
        GLSprite m_playerFour;
        GLSprite m_p1Label;
        GLSprite m_p2Label;
        GLSprite m_p3Label;
        GLSprite m_p4Label;
        Uint32 m_p1Selection;
        Uint32 m_p2Selection;
        Uint32 m_p3Selection;
        Uint32 m_p4Selection;
        std::string m_p1Path;
        std::string m_p2Path;
        std::string m_p3Path;
        std::string m_p4Path;
};

}

#endif // CHARACTERSELECTSCREEN_HPP
