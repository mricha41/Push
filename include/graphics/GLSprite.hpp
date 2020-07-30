#ifndef GLSPRITE_HPP
#define GLSPRITE_HPP

#include "graphics/GLDrawable.hpp"
#include "graphics/GLTransformable.hpp"

namespace pk
{

//forward declaration
class GLTexture;

class GLSprite : public GLDrawable, public GLTransformable
{
    private:
        //////////////////////////////////////////////
        /// \fn void updateNormals(GLfloat * vertices, unsigned int verticeCount, unsigned int stride)
        /// \brief Update the internal lighting normals of the
        /// GLSprite.
        //////////////////////////////////////////////
        void updateNormals(GLfloat * vertices, unsigned int verticeCount, unsigned int stride);

        //////////////////////////////////////////////
        /// \fn void updateGeometry()
        /// \brief Update the internal geometry of the
        /// GLSprite.
        //////////////////////////////////////////////
        void updateGeometry();

    public:
        //////////////////////////////////////////////
        /// \fn GLSprite()
        /// \brief Default constructor - not
        /// the one you're looking for. See below.
        //////////////////////////////////////////////
        GLSprite();

        //////////////////////////////////////////////
        /// \fn GLSprite(char* path, GLRect rect)
        /// \brief Preferred constructor for GLSprite. Requires
        /// a path and a GLRect to define the bounds for the sprite.
        //////////////////////////////////////////////
        GLSprite(GLTexture& t, GLRect rect);

        virtual ~GLSprite();

        void setTextureRect(GLRect r){ m_textureRect = r; updateGeometry(); };

        GLRect &getTextureRect(){ return m_textureRect; };

        //////////////////////////////////////////////
        /// \fn
        /// \brief Get the GLTexture that was used to
        /// create the GLSprite.
        /// \return GLTexture* - a pointer to an existing
        /// GLTexture object.
        //////////////////////////////////////////////
        GLTexture* getTexture(){ return m_texture; };

        //////////////////////////////////////////////
        /// \fn void setVertexColors(GLfloat colors [12])
        /// \brief Set the individual values for the
        /// vertex colors of the GLSprite.
        //////////////////////////////////////////////
        void setFillColor(glm::vec4 fillColor);

        //////////////////////////////////////////////
        /// \fn glm::vec4 &getFillColor()
        /// \brief Get the current fill color for
        /// the GLSprite.
        /// \return glm::vec4 - a glm::vec4
        /// representing the vertex colors.
        //////////////////////////////////////////////
        glm::vec4 &getFillColor(){ return m_fillColor; };

        //////////////////////////////////////////////
        /// \fn void setVertexColors(GLfloat colors [12])
        /// \brief Set the individual values for the
        /// vertex colors of the GLSprite.
        //////////////////////////////////////////////
        void setVertexColors(GLfloat colors [16]);

        //////////////////////////////////////////////
        /// \fn GLfloat* getVertexColors()
        /// \brief Get the current vertex colors for
        /// the GLSprite.
        /// \return GLfloat* - an array of GLfloat
        /// representing the vertex colors.
        //////////////////////////////////////////////
        GLfloat* getVertexColors(){ return m_vertexColors; };

        //////////////////////////////////////////////
        /// \fn void draw(GLStates& states)
        /// \brief Draw the GLSprite to the screen.
        /// \param GLStates& states - reference to an
        /// OpenGl states struct.
        //////////////////////////////////////////////
        void draw(GLStates& states);

    private:
        GLTexture* m_texture; ///< A pointer to a GLTexture to use for the GLSprite.
        GLRect m_textureRect; ///< Stores the value of the GLTexture's texture rect.
        glm::vec4 m_fillColor; ///< Fill color.
        GLfloat m_vertexColors [16]; ///< Array of individual vertex colors.
};

}

#endif // GLSPRITE_HPP
