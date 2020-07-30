#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <SDL2/SDL.h>

namespace pk
{

/////////////////////////////////////////////////////
/// \class Drawable
/// \brief Interface for creating drawable entities.
/// Part of the Decorator pattern for drawable objects
/// used in the game.
/////////////////////////////////////////////////////
class Drawable
{
    public:
        ////////////////////////////////////////////////
        /// \fn Drawable()
        /// \brief Drawable constructor. Call explicitly
        /// in inherited classes.
        ////////////////////////////////////////////////
        Drawable();

        virtual ~Drawable();

        ////////////////////////////////////////////////////////////////////////////////////////
        /// \fn virtual void draw(SDL_Renderer * const renderTarget, SDL_Rect * const renderTargetRect) = 0
        /// \brief Draw the drawable entity to a render target.
        /// \param SDL_Renderer * const renderTarget - the target to draw to.
        /// \param SDL_Rect * const renderTargetRect - the rect belonging to the render target.
        ////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(SDL_Renderer * const renderTarget, SDL_Rect * const renderTargetRect) = 0;
};

} //end namespace pk

#endif // DRAWABLE_HPP
