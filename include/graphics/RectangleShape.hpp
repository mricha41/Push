#ifndef RectangleShape_HPP
#define RectangleShape_HPP

#include "GL/glew.h"
#include <glm/glm.hpp>
#include "graphics/GLDrawable.hpp"
#include "graphics/GLTransformable.hpp"
#include "core/GLStates.hpp"

namespace pk
{

///////////////////////////////////////
/// \class RectangleShape
/// \brief Create a drawable RectangleShape
/// using OpenGL. For more complex OpenGL
/// geometry see the Mesh class.
///////////////////////////////////////
class RectangleShape : public GLDrawable, public GLTransformable
{
    private:
        //////////////////////////////////////////////
        /// \fn RectangleShape()
        /// \brief Default constructor - INACCESSIBLE!
        //////////////////////////////////////////////
        RectangleShape(){};

        //////////////////////////////////////////////
        /// \fn void updateNormals(GLfloat * vertices, unsigned int verticeCount, unsigned int stride)
        /// \brief Update the internal lighting normals of the
        /// RectangleShape.
        //////////////////////////////////////////////
        void updateNormals(GLfloat * vertices, unsigned int verticeCount, unsigned int stride);

        //////////////////////////////////////////////
        /// \fn void updateGeometry()
        /// \brief Update the internal geometry of the
        /// RectangleShape.
        //////////////////////////////////////////////
        void updateGeometry();

    public:
        //////////////////////////////////////////////
        /// \fn RectangleShape(GLfloat width, GLfloat height)
        /// \brief Construct a RectangleShape from a
        /// width and height.
        /// \param GLfloat width - width specified
        /// for the RectangleShape.
        /// \param GLfloat height - height specified
        /// for the RectangleShape.
        //////////////////////////////////////////////
        RectangleShape(GLfloat width, GLfloat height);

        virtual ~RectangleShape();

        //////////////////////////////////////////////
        /// \fn void setVertexColors(GLfloat colors [12])
        /// \brief Set the individual values for the
        /// vertex colors of the RectangleShape.
        //////////////////////////////////////////////
        void setFillColor(glm::vec4 fillColor);

        //////////////////////////////////////////////
        /// \fn glm::vec4 &getFillColor()
        /// \brief Get the current fill color for
        /// the RectangleShape.
        /// \return glm::vec4 - a glm::vec4
        /// representing the vertex colors.
        //////////////////////////////////////////////
        glm::vec4 &getFillColor(){ return m_fillColor; };

        //////////////////////////////////////////////
        /// \fn void setVertexColors(GLfloat colors [12])
        /// \brief Set the individual values for the
        /// vertex colors of the RectangleShape.
        //////////////////////////////////////////////
        void setVertexColors(GLfloat colors [16]);

        //////////////////////////////////////////////
        /// \fn GLfloat* getVertexColors()
        /// \brief Get the current vertex colors for
        /// the RectangleShape.
        /// \return GLfloat* - an array of GLfloat
        /// representing the vertex colors.
        //////////////////////////////////////////////
        GLfloat* getVertexColors(){ return m_vertexColors; };

        //////////////////////////////////////////////
        /// \fn void draw(GLStates& states)
        /// \brief Draw the RectangleShape to the screen.
        /// \param GLStates& states - reference to an
        /// OpenGl states struct.
        //////////////////////////////////////////////
        void draw(GLStates& states);

    private:
        glm::vec4 m_fillColor; ///< Rectangle fill color.
        GLfloat m_vertexColors [16]; ///< Array of individual vertex colors.
};

}

#endif // RectangleShape_HPP
