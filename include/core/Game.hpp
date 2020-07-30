#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>

#include "core/Window.hpp"
#include "states/ScreenState.hpp"

namespace pk
{

///////////////////////////////////////////////////////////////
/// \class Game
/// \brief Class for storing and managing all game data and states.
/// Game is implemented as a Singleton and also uses the State pattern
/// along with ScreenState subclasses.
//////////////////////////////////////////////////////////////
class Game
{
    private:
        //Inaccessible constructor
        /// \fn Game()
        /// \brief Inaccessible - Game is a Singleton.
        Game(){};
    public:
        virtual ~Game();

        /////////////////////////////////////////////
        /// \enum gameState
        /// \brief Internal states of the game.
        /////////////////////////////////////////////
        enum gameState
        {
            s_uninitialized,
            s_menu,
            s_options,
            s_levelSelect,
            s_characterSelect,
            s_level,
            s_quit
        };

        //These functions are deleted so that
        //copies cannot be made.
        //Singleton pattern depends on this.
        /// \fn Game(Game const&) = delete;
        /// \brief Inaccessible - Game is a Singleton.
        Game(Game const&) = delete;
        /// \fn void operator=(Game const&) = delete;
        /// \brief Inaccessible - Game is a Singleton.
        void operator=(Game const&) = delete;

        ////////////////////////////////////////////////////
        /// \fn static void init()
        /// \brief Initialization routine for Game ScreenStates.
        ////////////////////////////////////////////////////
        static void init();

        ////////////////////////////////////////////////////
        /// \fn static Game& getInstance()
        /// \brief Retrieve the Singleton Game object.
        ////////////////////////////////////////////////////
        static Game& getInstance();

        ////////////////////////////////////////////////////
        /// \fn static Window * const getWindow()
        /// \brief Retrieve the SDL window from the Game object.
        ////////////////////////////////////////////////////
        static Window * const getWindow(){return m_window;};

        /////////////////////////////////////////////////////
        /// \fn static void run()
        /// \brief Runs the game - call to get everything going.
        /////////////////////////////////////////////////////
        static void run();

        /////////////////////////////////////////////////////
        /// \fn static void setScreenState(ScreenState * const state)
        /// \brief Set the current ScreenState of the Game.
        /////////////////////////////////////////////////////
        static void setScreenState(ScreenState * const state){ m_state = state; };

        /////////////////////////////////////////////////////
        /// \fn static ScreenState * const getMenuScreenState()
        /// \brief Get a pointer to the Menu ScreenState.
        /// \return ScreenState * const - a const pointer to the Menu ScreenState.
        /////////////////////////////////////////////////////
        static ScreenState * const getMenuScreenState(){ return m_menu; };

        /////////////////////////////////////////////////////
        /// \fn static ScreenState * const getLevelScreenState()
        /// \brief Get a pointer to the Level ScreenState.
        /// \return ScreenState * const - a const pointer to the Level ScreenState.
        /////////////////////////////////////////////////////
        static ScreenState * const getLevelScreenState(){ return m_level; };

        /////////////////////////////////////////////////////
        /// \fn static void menu()
        /// \brief Run the MenuScreen state.
        /////////////////////////////////////////////////////
        static void menu();

        /////////////////////////////////////////////////////
        /// \fn static void options()
        /// \brief Run the OptionsScreen state.
        /////////////////////////////////////////////////////
        static void options();

        /////////////////////////////////////////////////////
        /// \fn static void levelSelect()
        /// \brief Run the LevelSelect state.
        /////////////////////////////////////////////////////
        static void levelSelect();

        /////////////////////////////////////////////////////
        /// \fn static void characterSelect()
        /// \brief Run the CharacterSelect state.
        /////////////////////////////////////////////////////
        static void characterSelect();

        /////////////////////////////////////////////////////
        /// \fn static void level()
        /// \brief Run the LevelScreen state.
        /////////////////////////////////////////////////////
        static void level();

        /////////////////////////////////////////////////////
        /// \fn static bool isRunning()
        /// \brief Check if the Game is running.
        /// \return bool
        /////////////////////////////////////////////////////
        static bool isRunning(){ return m_running; };

        /////////////////////////////////////////////////////
        /// \fn static glm::vec2 getScalingFactor()
        /// \brief Get the scaling factor according to the
        /// user's currently selected screen resolution relative to 800 x 600.
        /// Useful for scaling content with screen resolution.
        /// \return glm::vec2 - a vector of floats.
        /////////////////////////////////////////////////////
        static glm::vec2 getScalingFactor(){ return m_scalingFactor; };

        /////////////////////////////////////////////////////
        /// \fn static void setScalingFactor(glm::vec2 f)
        /// \brief Set the global scaling factor for drawing.
        /// \param glm::vec2 f - a scaling factor specified as a glm::vec2 of floats.
        /////////////////////////////////////////////////////
        static void setScalingFactor(glm::vec2 f){ m_scalingFactor = f; };
        /////////////////////////////////////////////////////
        /// \fn static int getMusicVolume()
        /// \brief Get the global setting for music volume.
        /////////////////////////////////////////////////////
        static int getMusicVolume(){ return m_musicVolume; };

        /////////////////////////////////////////////////////
        /// \fn static void setMusicVolume(int v)
        /// \brief Set the global music volume.
        /// \param int v - integer specifying the music volume.
        /////////////////////////////////////////////////////
        static void setMusicVolume(int v){ m_musicVolume = v; };

        /////////////////////////////////////////////////////
        /// \fn static int getSoundEffectVolume()
        /// \brief Get the global setting for sound effect volume.
        /////////////////////////////////////////////////////
        static int getSoundEffectVolume(){ return m_soundEffectVolume; };

        /////////////////////////////////////////////////////
        /// \fn static void setSoundEffectVolume(int v)
        /// \brief Set the global sound effect volume.
        /// \param int v - integer specifying the music volume.
        /////////////////////////////////////////////////////
        static void setSoundEffectVolume(int v){ m_soundEffectVolume = v; };

        /////////////////////////////////////////////////////
        /// \fn static void setPlayerCharacters(std::string p1, std::string p2, std::string p3, std::string p4)
        /// \brief Set the player character selection strings
        /// for use in each arena once players exit the
        /// character selection screen.
        /////////////////////////////////////////////////////
        static void setPlayerCharacters(std::string p1, std::string p2, std::string p3, std::string p4)
        {
            m_p1 = p1;
            m_p2 = p2;
            m_p3 = p3;
            m_p4 = p4;
        };

        /////////////////////////////////////////////////////
        /// \fn static std::vector<std::string> getPlayerCharacters()
        /// \brief Get the player character selection strings
        /// for use in each arena once players exit the
        /// character selection screen.
        /// \return std::vector<std::string> - a vector of strings.
        /////////////////////////////////////////////////////
        static std::vector<std::string> getPlayerCharacters(){ std::vector<std::string> s{ m_p1, m_p2, m_p3, m_p4 }; return s; };

    private:
        static Window *m_window; ///< Window object for context and rendering.
        static ScreenState *m_menu; ///< Main menu state instance.
        static ScreenState *m_options; ///< Options menu state instance.
        static ScreenState *m_levelSelect; ///< LevelSelect state instance.
        static ScreenState *m_characterSelect; ///< CharacterSelect state instance.
        static ScreenState *m_level; ///< Level state instance.
        static ScreenState *m_state; ///< Current state instance.
        static Uint32 m_gameState; ///< Game object state (not screen state...but related).
        static bool m_running; ///< Check if Game is running.
        static glm::vec2 m_scalingFactor; ///< The scaling factor according to the current resolution relative to 800 x 600.
        static int m_musicVolume; ///< The current setting for music volume.
        static int m_soundEffectVolume; ///< The current setting for sound effect volume.
        static Uint32 m_levelSelected; ///< The current level selected by the player.
        static std::string m_p1; ///< path to the player one texture.
        static std::string m_p2; ///< path to the player two texture.
        static std::string m_p3; ///< path to the player three texture.
        static std::string m_p4; ///< path to the player four texture.
};

} // end namespace pk

#endif // GAME_HPP
