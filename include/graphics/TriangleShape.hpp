#ifndef TRIANGLESHAPE_HPP
#define TRIANGLESHAPE_HPP

#include "GL/glew.h"
#include <glm/glm.hpp>
#include "graphics/GLDrawable.hpp"
#include "graphics/GLTransformable.hpp"
#include "core/GLStates.hpp"

namespace pk
{
    ///////////////////////////////////////
    /// \class TriangleShape
    /// \brief Create a drawable TriangleShape
    /// using OpenGL. Useful for basic test
    /// programs, but not very flexible - it
    /// will create only isosceles triangles.
    /// For more complex OpenGL geometry see
    /// the Mesh class.
    ///////////////////////////////////////
    class TriangleShape : public GLDrawable, public GLTransformable
    {
        private:
            //////////////////////////////////////////////
            /// \fn TriangleShape()
            /// \brief Default constructor - INACCESSIBLE!
            //////////////////////////////////////////////
            TriangleShape(){};

            void updateNormals(GLfloat * vertices, unsigned int verticeCount, unsigned int * indices, unsigned int stride);

            //////////////////////////////////////////////
            /// \fn void updateGeometry()
            /// \brief Update the internal geometry of the
            /// TriangleShape.
            //////////////////////////////////////////////
            void updateGeometry();

        public:
            //////////////////////////////////////////////
            /// \fn TriangleShape(GLfloat width, GLfloat height)
            /// \brief Construct a TriangleShape from a
            /// width and height.
            /// \param GLfloat width - width specified
            /// for the TriangleShape.
            /// \param GLfloat height - height specified
            /// for the TriangleShape.
            //////////////////////////////////////////////
            TriangleShape(GLfloat width, GLfloat height);

            virtual ~TriangleShape();

            //////////////////////////////////////////////
            /// \fn void setVertexColors(GLfloat colors [12])
            /// \brief Set the individual values for the
            /// vertex colors of the TriangleShape.
            //////////////////////////////////////////////
            void setFillColor(glm::vec4 fillColor);

            //////////////////////////////////////////////
            /// \fn glm::vec4 &getFillColor()
            /// \brief Get the current fill color for
            /// the TriangleShape.
            /// \return glm::vec4 - a glm::vec4
            /// representing the vertex colors.
            //////////////////////////////////////////////
            glm::vec4 &getFillColor(){ return m_fillColor; };

            //////////////////////////////////////////////
            /// \fn void setVertexColors(GLfloat colors [16])
            /// \brief Set the individual values for the
            /// vertex colors of the TriangleShape.
            //////////////////////////////////////////////
            void setVertexColors(GLfloat colors [16]);

            //////////////////////////////////////////////
            /// \fn GLfloat* getVertexColors()
            /// \brief Get the current vertex colors for
            /// the TriangleShape.
            /// \return GLfloat* - an array of GLfloat
            /// representing the vertex colors.
            //////////////////////////////////////////////
            GLfloat* getVertexColors(){ return m_vertexColors; };

            //////////////////////////////////////////////
            /// \fn void draw(GLStates& states)
            /// \brief Draw the TriangleShape to the screen.
            /// \param GLStates& states - reference to an
            /// OpenGl states struct.
            //////////////////////////////////////////////
            void draw(GLStates& states);

        private:
            glm::vec4 m_fillColor; ///< Triangle fill color.
            GLfloat m_vertexColors [16]; ///< Array of individual vertex colors.
    };
}

#endif // TRIANGLESHAPE_HPP
