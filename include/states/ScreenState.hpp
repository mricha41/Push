#ifndef SCREENSTATE_HPP
#define SCREENSTATE_HPP

#include <SDL2/SDL.h>

namespace pk
{

///////////////////////////////////////////////////////////////
/// \class ScreenState
/// \brief Abstract class for screen states, necessary for implementing
/// the State pattern along with the Game class.
///////////////////////////////////////////////////////////////
class ScreenState
{
    public:
        /////////////////////////////////////////////
        /// \fn ScreenState();
        /// \brief Default constructor.
        /////////////////////////////////////////////
        ScreenState();

        virtual ~ScreenState();

        /////////////////////////////////////////////
        /// \fn virtual void display()
        /// \brief Display the screen state in the window.
        ///        Requires and override in inherited classes.
        /////////////////////////////////////////////
        virtual void display() = 0;

        /////////////////////////////////////////////
        /// \fn virtual bool isRunning()
        /// \brief Check if ScreenState is running.
        ///        Requires and override in inherited classes.
        /////////////////////////////////////////////
        virtual bool isRunning() = 0;

        /////////////////////////////////////////////
        /// \fn Uint32 getState()
        /// \brief Get the internal state of the ScreenState
        /// \return Uint32
        /////////////////////////////////////////////
        Uint32 getState(){ return m_state; };

        /////////////////////////////////////////////
        /// \fn void setState(Uint32 state)
        /// \brief Set the internal state of the ScreenState
        /// \param Uint32 state - an unsigned int (32-bit) representing the internal state.
        /////////////////////////////////////////////
        void setState(Uint32 state) { m_state = state; };

    private:
        Uint32 m_state;
};

} //end namespace pk

#endif // SCREENSTATE_HPP
