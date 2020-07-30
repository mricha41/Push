#ifndef OPTIONSSCREEN_HPP
#define OPTIONSSCREEN_HPP

#include <iostream>
#include <fstream>

#include "states/ScreenState.hpp"
#include "tables/options.hpp"

namespace pk
{

class OptionsScreen : public ScreenState
{
    public:
        OptionsScreen();
        virtual ~OptionsScreen();

        enum optionsState
        {
            s_uninitialized,
            s_running,
            s_menu,
            s_exit
        };

        /////////////////////////////////////////////
        /// \fn void display()
        /// \brief Display the options screen state in the window.
        /////////////////////////////////////////////
        void display() override;

        /////////////////////////////////////////////
        /// \fn virtual bool isRunning()
        /// \brief Check if OptionsScreen is running.
        /// \return bool
        /////////////////////////////////////////////
        virtual bool isRunning() override { return m_running; };

    private:
        bool m_running;
        pk::options::optionsCereal m_options;
};

}

#endif // OPTIONSSCREEN_HPP
