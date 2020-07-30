#ifndef GLTRANSFORMABLE_HPP
#define GLTRANSFORMABLE_HPP

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "core/GLStates.hpp"

namespace pk
{
    ///////////////////////////////////
    /// \struct GLRect
    /// \brief Useful for defining size
    /// and origin of an OpenGL object.
    ////////////////////////////////////
    struct GLRect
    {
        GLfloat d_top;
        GLfloat d_left;
        GLfloat d_width;
        GLfloat d_height;
    };

    //////////////////////////////
    /// \struct GLTransformData
    /// \brief Transform data for
    /// GLTransformable objects.
    /// Used by the GLTransformable
    /// class internally, but usable
    /// in isolation as well.
    //////////////////////////////
    struct GLTransformData
    {
        GLuint d_VAO; ///< A GLuint specifying an OpenGL vertex array object to bind.
        GLuint d_VBO; ///< A GLuint specifying an OpenGL vertex buffer object to bind.
        GLuint d_IBO; ///< A GLuint specifying an OpenGL index buffer object to bind.
        GLsizei d_indexCount; ///< The number of indices in the OpenGL index buffer object.
        glm::mat4 d_model; ///< An OpenGL Model matrix.
        GLStates d_glStates; ///< The available OpenGL state used for rendering.
        glm::vec2 d_origin; ///< A vector of floats representing the origin of the GLTransformable.
        glm::vec2 d_position; ///< A vector of floats representing the position of the GLTransformable.
        GLfloat d_angle; ///< The angle of rotation for the GLTransformable specified in degrees (NOT radians).
        glm::vec2 d_scale; ///< A vector of floats representing the scale of the GLTransformable.
        GLRect d_rect; ///< A struct containing information necessary for calculating size and origin of an object.
    };

    ///////////////////////////////////////////////
    /// \class GLTransformable
    /// \brief Decorator class for creating easing
    /// OpenGL transformations for game objects.
    ///////////////////////////////////////////////
    class GLTransformable
    {
        public:

            //////////////////////////////////////
            /// \fn GLTransformable()
            /// \brief Default constructor.
            //////////////////////////////////////
            GLTransformable();

            virtual ~GLTransformable();

            //////////////////////////////////////////////
            /// \fn void setRect(GLRect r)
            /// \brief Set the bounding rectangle for the
            /// GLTransformable object. Useful for calculating
            /// origin and size definitions.
            /// \param GLRect r - a bounding rectangle
            /// for the GLTransformable object.
            //////////////////////////////////////////////
            void setRect(GLRect r){ m_data.d_rect = r; };

            //////////////////////////////////////////////
            /// \fn GLRect &getRect()
            /// \brief Get the current bounding rectangle
            /// of the GLTransformable object.
            /// \return GLRect & - a reference to a
            /// bounding rectangle.
            //////////////////////////////////////////////
            GLRect &getRect(){ return m_data.d_rect; };

            //////////////////////////////////////////////
            /// \fn void setWidth(GLfloat w)
            /// \brief Convenient function for setting
            /// the width of the GLTransformable.
            /// \param GLfloat w - width of the GLTransformable.
            //////////////////////////////////////////////
            void setWidth(GLfloat w){ m_data.d_rect.d_width = w; };

            //////////////////////////////////////////////
            /// \fn GLfloat &getWidth()
            /// \brief Get the width of the GLTransformable.
            /// \return GLfloat & - reference to the width
            /// of the GLTransformable.
            //////////////////////////////////////////////
            GLfloat &getWidth(){ return m_data.d_rect.d_width; };

            //////////////////////////////////////////////
            /// \fn /// \brief Convenient function for setting
            /// the width of the GLTransformable.
            /// \brief Convenient function for setting
            /// the height of the GLTransformable.
            /// \param GLfloat h - height of the GLTransformable.
            //////////////////////////////////////////////
            void setHeight(GLfloat h){ m_data.d_rect.d_height = h; };

            //////////////////////////////////////////////
            /// \fn GLfloat &getHeight()
            /// \brief Get the height of the GLTransformable.
            /// \return GLfloat & - reference to the height
            /// of the GLTransformable.
            //////////////////////////////////////////////
            GLfloat &getHeight(){ return m_data.d_rect.d_height; };

            //////////////////////////////////////////////
            /// \fn void setOrigin(glm::vec2 origin)
            /// \brief Set the origin of the GLTransformable
            /// in screen coordinates (NOT normalized coordinates
            /// such as clip coordinates for example).
            /// \param glm::vec2 origin - a glm::vec2
            // specifying the origin to set.
            //////////////////////////////////////////////
            void setOrigin(glm::vec2 origin){ m_data.d_origin = origin; };

            //////////////////////////////////////////////
            /// \fn glm::vec2 &getOrigin()
            /// \brief Get the origin of the GLTransformable
            /// in screen coordinates (NOT normalized coordinates
            /// such as clip coordinates for example).
            /// \return glm::vec2 - a glm::vec2 vector of floats
            /// corresponding to the origin of the GLTransformable.
            //////////////////////////////////////////////
            glm::vec2 &getOrigin(){ return m_data.d_origin; };

            //////////////////////////////////////////////
            /// \fn void setPosition(glm::vec2 position)
            /// \brief Set the position of the GLTransformable
            /// in screen coordinates (NOT normalized coordinates
            /// such as clip coordinates for example).
            /// \param glm::vec2 position - a glm::vec2
            // specifying the position to set.
            //////////////////////////////////////////////
            void setPosition(glm::vec2 position){ m_data.d_position = position; };

            //////////////////////////////////////////////
            /// \fn const glm::vec2 &getPosition()
            /// \brief Get the position of the GLTransformable
            /// in screen coordinates (NOT normalized coordinates
            /// such as clip coordinates for example).
            /// \return glm::vec2 - a glm::vec2 vector of floats
            /// corresponding to the position of the GLTransformable.
            //////////////////////////////////////////////
            const glm::vec2 &getPosition(){ return m_data.d_position; };

            //////////////////////////////////////////////
            /// \fn void move(glm::vec2 offset)
            /// \brief Move the GLTransformable by a constant
            /// offset value in screen coordinates (NOT normalized coordinates
            /// such as clip coordinates for example).
            /// \param glm::vec2 offset - the offset you
            /// wish to move the GLTransformable by.
            //////////////////////////////////////////////
            void move(glm::vec2 offset){ setPosition(m_data.d_position + offset); };

            //////////////////////////////////////////////
            /// \fn void setAngle(float angle)
            /// \brief Set the angle of the GLTransformable
            /// (in degrees, NOT radians).
            /// \param float angle - degrees specifying
            /// the angle of the GLTransformable.
            //////////////////////////////////////////////
            void setAngle(float angle){ m_data.d_angle = angle; };

            //////////////////////////////////////////////
            /// \fn float getAngle()
            /// \brief Get the angle of the GLTransformable
            /// (in degrees, NOT radians).
            /// \return float - a plain old float.
            //////////////////////////////////////////////
            float getAngle(){ return m_data.d_angle; };

            //////////////////////////////////////////////
            /// \fn void rotate(float degrees)
            /// \brief Rotate the GLTransformable by a constant
            /// value (in degrees, NOT radians).
            /// (in degrees, NOT radians).
            /// \param float degrees - degrees specifying
            /// the value to rotate the GLTransformable by.
            //////////////////////////////////////////////
            void rotate(float degrees){ setAngle(m_data.d_angle + degrees); };

            //////////////////////////////////////////////
            /// \fn void setScale(glm::vec2 scale)
            /// \brief Set the scale of the GLTransformable.
            /// \param glm::vec2 scale - the scale you wish
            /// to assign to the GLTransformable.
            //////////////////////////////////////////////
            void setScale(glm::vec2 scale){ m_data.d_scale = scale; };

            //////////////////////////////////////////////
            /// \fn glm::vec2 getScale()
            /// \brief Get the scale of the GLTransformable.
            /// \return glm::vec2 - a glm::vec2 of floats.
            //////////////////////////////////////////////
            glm::vec2 getScale(){ return m_data.d_scale; };

            //////////////////////////////////////////////
            /// \fn void scale(glm::vec2 scale)
            /// \brief Scale the GLTransformable by a constant
            /// factor specified as a glm::vec2 of floats.
            /// \param glm::vec2 scale - the factor you wish
            /// to scale the GLTransformable by.
            //////////////////////////////////////////////
            void scale(glm::vec2 scale){ setScale(m_data.d_scale + scale); };

            //////////////////////////////////////////////
            /// \fn void clear()
            /// \brief Clear the buffers and reset the
            /// GLTransformable to an uninitialized state.
            //////////////////////////////////////////////
            void clear();

        public:
            GLTransformData m_data; ///< Internal transform data for GLTransformable inherited classes.
    };
}

#endif // GLTRANSFORMABLE_HPP
