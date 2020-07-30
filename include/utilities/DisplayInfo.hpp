#ifndef SYSTEMINFO_HPP
#define SYSTEMINFO_HPP

#include <stdio.h>
#include <vector>

#include <SDL2/SDL.h>

namespace pk
{
    namespace utilities
    {
        ///////////////////////////////////////////////////////////////
        /// \class DisplayInfo
        /// \brief Class for storing and managing all game data and states.
        /// Game is implemented as a Singleton and also uses the State pattern
        /// along with ScreenState subclasses.
        //////////////////////////////////////////////////////////////
        class DisplayInfo
        {
        public:
            //////////////////////////////////////////
            /// \fn DisplayInfo()
            /// \brief Default constructor.
            //////////////////////////////////////////
            DisplayInfo();

            ~DisplayInfo();

            //////////////////////////////////////////
            /// \fn
            /// \brief Get the number of displays available
            /// on the user's system.
            /// \return int - number of displays.
            //////////////////////////////////////////
            int getDisplayCount(){ return m_numberOfDisplays; };

            //////////////////////////////////////////
            /// \fn void printNumberOfDisplayModes()
            /// \brief Print the number of display modes
            /// available for each screen on the user's system.
            //////////////////////////////////////////
            void printNumberOfDisplayModes(){ int m = 0; for(auto &i : m_numberOfDisplayModes){ printf("Display modes available on screen %i: %i\n", m, i); ++m; } };

            //////////////////////////////////////////
            /// \fn std::vector< std::vector<SDL_DisplayMode> > &getDisplayModes()
            /// \brief Get each available display mode
            /// in a 2D std::vector for each of the user's
            /// displays.
            /// \return std::vector< std::vector<SDL_DisplayMode> > - 2D std::vector
            /// of SDL_Display mode structures. Each contains the pixel format,
            /// the resolution given in width and height, the screen refresh rate,
            /// and a void* containing graphics driver information.
            //////////////////////////////////////////
            std::vector< std::vector<SDL_DisplayMode> > &getDisplayModes(){ return m_displayModes; };

            //////////////////////////////////////////
            /// \fn void printDisplayModes()
            /// \brief Print all of the available display modes
            /// that exist on the users machine.
            //////////////////////////////////////////
            void printDisplayModes();

        private:
            std::vector< std::vector<SDL_DisplayMode> > m_displayModes; ///< All of the display modes on the platform.
            int m_numberOfDisplays; ///< Number of displays on user's machine.
            std::vector<int> m_numberOfDisplayModes; ///< Number of display modes for each screen available.
        };
    }
}
#endif // SYSTEMINFO_HPP
