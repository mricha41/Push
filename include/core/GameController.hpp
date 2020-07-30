#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <SDL2/SDL_gamecontroller.h>

namespace pk
{
//////////////////////////////
/// \enum GameControllerAxis
/// \brief Mapping of SDL game pad
/// axes for the purposes of not
/// having to depend on memorizing
/// SDL enums.
///////////////////////////////
enum GameControllerAxis
{
    INVALID_AXIS    =   SDL_CONTROLLER_AXIS_INVALID,
    LEFT_X          =   SDL_CONTROLLER_AXIS_LEFTX,
    LEFT_Y          =   SDL_CONTROLLER_AXIS_LEFTY,
    RIGHT_X         =   SDL_CONTROLLER_AXIS_RIGHTX,
    RIGHT_Y         =   SDL_CONTROLLER_AXIS_RIGHTY,
    TRIGGER_LEFT    =   SDL_CONTROLLER_AXIS_TRIGGERLEFT,
    TRIGGER_RIGHT   =   SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
    AXIS_MAX        =   SDL_CONTROLLER_AXIS_MAX
};

//////////////////////////////
/// \enum GameControllerButton
/// \brief Mapping of SDL game pad
/// buttons for the purposes of not
/// having to depend on memorizing
/// SDL enums.
///////////////////////////////
enum GameControllerButton
{
    INVALID_BUTTON  = SDL_CONTROLLER_BUTTON_INVALID,
    A               = SDL_CONTROLLER_BUTTON_A,
    B               = SDL_CONTROLLER_BUTTON_B,
    X               = SDL_CONTROLLER_BUTTON_X,
    Y               = SDL_CONTROLLER_BUTTON_Y,
    BACK            = SDL_CONTROLLER_BUTTON_BACK,
    GUIDE           = SDL_CONTROLLER_BUTTON_GUIDE,
    START           = SDL_CONTROLLER_BUTTON_START,
    LEFT_STICK      = SDL_CONTROLLER_BUTTON_LEFTSTICK,
    RIGHT_STICK     = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
    LEFT_SHOULDER   = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
    RIGHT_SHOULDER  = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
    DPAD_UP         = SDL_CONTROLLER_BUTTON_DPAD_UP,
    DPAD_DOWN       = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
    DPAD_LEFT       = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
    DPAD_RIGHT      = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
    BUTTON_MAX      = SDL_CONTROLLER_BUTTON_MAX
};

//////////////////////////////////////
/// \class GameController
/// \brief Convenience class for abstracting
/// functionality that already exists in
/// SDL.
//////////////////////////////////////
class GameController
{
    private:
        //////////////////////////////////////////////
        /// \fn GameController()
        /// \brief Default constructor - INACCESSIBLE!
        //////////////////////////////////////////////
        GameController(){};

        //////////////////////////////////////////////
        /// \fn void close()
        /// \brief Calls SDL close routine, cleaning
        /// up for the controller without intervention.
        /// This function is called in the destructor.
        /// Do not call this directly, rely on controller
        /// going out of scope or, if using dynamic memory,
        /// delete as normal.
        //////////////////////////////////////////////
        void close();

    public:
        //////////////////////////////////////////////
        /// \fn GameController(int id)
        /// \brief Preferred constructor initializing
        /// a controller by id, making multiplayer
        /// support a bit more sane.
        /// \param int id - the id you wish to assign
        /// to the GameController object.
        //////////////////////////////////////////////
        GameController(int id);

        virtual ~GameController();

        //////////////////////////////////////////////
        /// \fn int getID()
        /// \brief Get the id for the game pad.
        /// \return int - a plain old int corresponding
        /// to the controller id.
        //////////////////////////////////////////////
        int getID(){ return m_id; };

        //////////////////////////////////////////////
        /// \fn const char* getControllerName()
        /// \brief Get the name for the game pad.
        /// \return const char* - a C-style string corresponding
        /// to the controller name.
        //////////////////////////////////////////////
        const char* getControllerName(){ return m_name; };

        //////////////////////////////////////////////
        /// \fn SDL_bool isConnected()
        /// \brief Get the connection status for the game pad.
        /// \return SDL_bool - an SDL boolean corresponding
        /// to the controller's connection status.
        //////////////////////////////////////////////
        SDL_bool isConnected(){ return SDL_GameControllerGetAttached(m_controller); };

        //////////////////////////////////////////////
        /// \fn void setDeadZone(int deadzone)
        /// \brief Get the dead zone for the game pad's joystick(s).
        /// \param int deadzone - a plain old int that
        /// you wish to assign as the controller's dead zone.
        //////////////////////////////////////////////
        void setDeadZone(int deadzone){ m_deadzone = deadzone; };

        //////////////////////////////////////////////
        /// \fn int getDeadZone()
        /// \brief Get the dead zone for the game pad.
        /// \return int - an int corresponding
        /// to the controller's dead zone.
        //////////////////////////////////////////////
        int getDeadZone(){ return m_deadzone; };

        //////////////////////////////////////////////
        /// \fn Sint16 getAxisState(int axis)
        /// \brief Get the axis state for the game pad.
        /// \param int axis - the axis (see
        /// GameControllerAxis enum) you wish to query for
        /// the current value.
        /// \return Sint16 - an SDL Sint16 corresponding
        /// to the controller's axis value. See GameControllerAxis
        /// enum for valid states to pass in. See SDL
        /// documentation for output ranges.
        //////////////////////////////////////////////
        Sint16 getAxisState(int axis){ return SDL_GameControllerGetAxis(m_controller, (SDL_GameControllerAxis) axis); };

        //////////////////////////////////////////////
        /// \fn Uint8 getButtonState(int button)
        /// \brief Get the button state for the game pad.
        /// \param int button - the button (see
        /// GameControllerButton enum) you wish to query for
        /// the current value.
        /// \return Uint8 - an SDL Uint8 corresponding
        /// to the controller's axis value. See GameControllerButton
        /// enum for valid states to pass in. Returns 1 for pressed state
        /// or 0 for not pressed (or error) state.
        //////////////////////////////////////////////
        Uint8 getButtonState(int button){ return SDL_GameControllerGetButton(m_controller, (SDL_GameControllerButton) button); };

    private:
        SDL_GameController* m_controller; ///< A handle to the SDL_GameController.
        int m_deadzone; ///< The value stored for the game controller's axis dead zone.
        int m_id; ///< The id corresponding to the game controller.
        const char* m_name; ///< The name given by SDL to the game controller.
};

}

#endif // GAMECONTROLLER_HPP
