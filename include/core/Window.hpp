#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "graphics/Drawable.hpp"
#include "graphics/GLDrawable.hpp"
#include "core/GLStates.hpp"

namespace pk
{

//////////////////////////////////////////////////////////
/// \class Window
/// \brief Class for SDL window creation and management,
/// implemented using the Facade pattern to provide a more
/// intuitive interface.
//////////////////////////////////////////////////////////
class Window
{
    private:
        //////////////////////////////////////////////
        /// \fn Window()
        /// \brief Default constructor - INACCESSIBLE!
        //////////////////////////////////////////////
        Window(){};
    public:
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \fn Window(const char *windowTitle, int x, int y, int width, int height, Uint32 windowFlags)
        /// \brief Construct a window from the minimal parameters required to instantiate a Window.
        /// \param windowTitle - const char* C-style string to title the window.
        /// \param position - glm::ivec2 integer vector for the window position on the screen.
        /// \param width - integer value for the window width.
        /// \param height - integer value for the window height.
        /// \param windowFlags - Uint32 value holding the SDL window flags (http://wiki.libsdl.org/SDL_WindowFlags).
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Window(const char *windowTitle, glm::ivec2 position, int width, int height, Uint32 windowFlags);

        virtual ~Window();

        ////////////////////////////////////////////
        /// \fn void render()
        /// \brief Render to the window.
        ////////////////////////////////////////////
        void render();

        ///////////////////////////////////////////////////////////
        /// \fn SDL_Window* getWindow()
        /// \brief Get the raw SDL_Window pointer (read-only).
        /// \return SDL_Window * const - pointer to an SDL_Window.
        ///////////////////////////////////////////////////////////
        SDL_Window * const getWindow(){return m_window;};

        ///////////////////////////////////////////////////////////
        /// \fn const SDL_GLContext &getOpenGLContext()
        /// \brief Get the OpenGL context provided by SDL.
        /// \return SDL_GLContext - an SDL provided OpenGL context.
        ///////////////////////////////////////////////////////////
        SDL_GLContext &getContext(){ return m_context; };

        ///////////////////////////////////////////////////////////////
        /// \fn SDL_Renderer * getRenderer()
        /// \brief Get the raw SDL_Renderer pointer (read-only).
        /// \return SDL_Renderer * const - pointer to an SDL_Renderer.
        ///////////////////////////////////////////////////////////////
        SDL_Renderer * const getRenderer(){return m_renderer;};

        ////////////////////////////////////////////////////////////////
        /// \fn const char * getTitle()
        /// \brief Get the window's title.
        /// \return char * const - a const pointer to a C-style string.
        ////////////////////////////////////////////////////////////////
        const char * getTitle(){ return m_title; };

        ////////////////////////////////////////////////////////////////
        /// \fn void setTitle(const char *title)
        /// \brief Set the title of the window.
        ////////////////////////////////////////////////////////////////
        void setTitle(const char *title){ m_title = title; SDL_SetWindowTitle(m_window, m_title); };

        ////////////////////////////////////////////////////////
        /// \fn glm::ivec2 getPosition()
        /// \brief Get the position of the window on screen.
        /// \return glm::ivec2 - window position.
        ////////////////////////////////////////////////////////
        const glm::ivec2 &getPosition(){ return m_position; };

        ////////////////////////////////////////////////////////////////////////////
        /// \fn void setPosition(glm::ivec2 position)
        /// \brief Set the position of the window on screen.
        /// \param glm::ivec2 - x and y coordinates to set the window position to.
        /// \return void
        ////////////////////////////////////////////////////////////////////////////
        void setPosition(glm::ivec2 position){ m_position = position; };

        ////////////////////////////////////////////////////////
        /// \fn glm::ivec2 getSize()
        /// \brief Get the SDL window size (width and height).
        /// \return const glm::ivec2 & - a glm vector of 2 integers.
        ////////////////////////////////////////////////////////
        glm::ivec2 getSize(){ return glm::ivec2(m_width, m_height); };

        ////////////////////////////////////////////////////////
        /// \fn void setFlags(const Uint32 &flags)
        /// \brief Set the SDL window size (width and height).
        /// \param const glm::ivec2 &windowSize - a glm vector of 2 integers.
        ////////////////////////////////////////////////////////
        void setSize(const glm::ivec2 &windowSize){ m_width = windowSize.x; m_height = windowSize.y; SDL_SetWindowSize(m_window, m_width, m_height);};

        ////////////////////////////////////////////////////////
        /// \fn const Uint32 &getFlags()
        /// \brief Get the SDL window flags.
        /// \return Uint32
        ////////////////////////////////////////////////////////
        const Uint32 &getFlags(){ return m_flags; };

        ////////////////////////////////////////////////////////
        /// \fn void setFlags(const Uint32 &flags)
        /// \brief Set the SDL window flags.
        /// \param Uint32 flags - a Uint32.
        ////////////////////////////////////////////////////////
        void setFlags(const Uint32 &flags){ m_flags = flags; };

        ///////////////////////////////////////////////////////
        /// \fn const SDL_Rect& getWindowRect()
        /// \brief Get the SDL_Rect belonging to the Window.
        ///////////////////////////////////////////////////////
        const SDL_Rect &getWindowRect(){ return m_rect; };

        ////////////////////////////////////////////////////////
        /// \fn void setWindowRect(SDL_Rect &rect)
        /// \brief Set the SDL_Rect belonging to the Window.
        /// \param SDL_Rect &rect - Reference to an SDL_Rect.
        ////////////////////////////////////////////////////////
        void setWindowRect(SDL_Rect &rect){ m_rect = rect; };

        ////////////////////////////////////////////////////////
        /// \fn const glm::ivec4 &getClearColor()
        /// \brief Get the clear color of the Window.
        /// \return glm::ivec4 - the clear color of the Window.
        ////////////////////////////////////////////////////////
        const glm::tvec4<Uint8> &getClearColor(){ return m_clearColor; };

        ////////////////////////////////////////////////////////
        /// \fn SDL_Color getSDLClearColor()
        /// \brief Get the clear color of the Window in SDL_Color format.
        /// \return SDL_Color - the clear color of the Window.
        ////////////////////////////////////////////////////////
        SDL_Color getSDLClearColor(){ SDL_Color c = {m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a}; return c; };

        ////////////////////////////////////////////////////////
        /// \fn void draw(GLDrawable &drawable)
        /// \brief Draw a DrawableGL object in the Window.
        /// \param GLDrawable &drawable - the DrawableGL object.
        /// \param GLStates &states - a reference to the struct containing the available OpenGL states.
        ////////////////////////////////////////////////////////
        void draw(GLDrawable &drawable, GLStates &states);

        ////////////////////////////////////////////////////////
        /// \fn void draw(Drawable &drawable)
        /// \brief Draw a Drawable object in the Window.
        /// \param Drawable &drawable - the Drawable object.
        ////////////////////////////////////////////////////////
        void draw(Drawable &drawable);

        ////////////////////////////////////////////////////////////
        /// \fn void draw(Drawable * const drawables)
        /// \brief Draw an array of Drawable objects in the Window
        /// \param Drawable * const drawables - an array of drawables
        /// for drawing to the window.
        ////////////////////////////////////////////////////////////
        void draw(Drawable * const drawables);

        /////////////////////////////////////////////////////////////
        /// \fn void clear()
        /// \brief Clear the window for rendering with SDL (not OpenGL).
        /// \param glm::ivec4 color - a glm vector of integers
        /// specifying the window clear color.
        /////////////////////////////////////////////////////////////
        void clear(glm::ivec4 color = glm::ivec4());

    private:
        SDL_GLContext m_context; ///< OpenGL context provided by SDL.
        SDL_Window *m_window; ///< SDL_Window object.
        const char *m_title; ///< The window title.
        SDL_Renderer *m_renderer; ///< SDL_Renderer object.
        glm::ivec2 m_position; ///< Window position as a vector of integers.
        int m_width; ///< Width of the Window.
        int m_height; ///< Height of the Window.
        Uint32 m_flags; ///< Display flags for the SDL_Window.
        SDL_Rect m_rect; ///< SDL_Rect for drawing within a rectangular area of the window.
        glm::tvec4<Uint8> m_clearColor; ///< SDL_Color for clearing the screen.
};

}///end namespace pk

#endif // WINDOW_HPP
