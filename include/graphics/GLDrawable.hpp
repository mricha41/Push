#ifndef GLDRAWABLE_HPP
#define GLDRAWABLE_HPP

#include "GL/glew.h"
#include "core/GLStates.hpp"

namespace pk
{

/////////////////////////////////////////////////////
/// \class Drawable
/// \brief Interface for creating drawable entities.
/// Part of the Decorator pattern for drawable objects
/// used in the game.
/////////////////////////////////////////////////////
class GLDrawable
{
    public:
        ////////////////////////////////////////////////
        /// \fn Drawable()
        /// \brief Drawable constructor. Call explicitly
        /// in inherited classes.
        ////////////////////////////////////////////////
        GLDrawable();

        virtual ~GLDrawable();

        ////////////////////////////////////////////////////////////////////////////////////////
        /// \fn virtual void draw(GLStates &states) = 0
        /// \brief Draw the OpenGL drawable object.
        /// \param GLStates &states - a reference to the current OpenGL states used for rendering.
        ////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(GLStates &states) = 0;
};

}

#endif // GLDRAWABLE_HPP
