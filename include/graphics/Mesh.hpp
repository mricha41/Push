#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "graphics/GLDrawable.hpp"
#include "graphics/GLTransformable.hpp"
#include "core/GLStates.hpp"

namespace pk
{

//////////////////////////////////////////
/// \class Mesh
/// \brief Class for building OpenGL generic
/// geometry.
//////////////////////////////////////////
class Mesh : public GLDrawable, public GLTransformable
{
    private:
        //////////////////////////////////////////////
        /// \fn Mesh()
        /// \brief Default constructor - INACCESSIBLE!
        //////////////////////////////////////////////
        Mesh(){};

        void updateNormals(GLfloat * vertices, unsigned int verticeCount, unsigned int * indices, unsigned int stride);

    public:
        //////////////////////////////////////////////
        /// \fn Mesh(GLfloat *vertices, unsigned int *indices, unsigned int numvertices, unsigned int numindices)
        /// \brief Required constructor - any Mesh
        /// instance will need at least vertices and
        /// indices (and their associated counts) to
        /// function properly.
        //////////////////////////////////////////////
        Mesh(GLfloat *vertices, unsigned int *indices, unsigned int numvertices, unsigned int numindices);

        ~Mesh();

        //////////////////////////////////////////////
        /// \fn void draw(GLStates& states)
        /// \brief Draw the Mesh to the screen.
        /// \param GLStates& states - reference to an
        /// OpenGl states struct.
        //////////////////////////////////////////////
        void draw(GLStates& states);
};

}

#endif //MESH_HPP
