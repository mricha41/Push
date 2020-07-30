#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>

namespace pk
{

//////////////////////////////////////
/// \struct transformData
/// \brief Data used for transformations.
//////////////////////////////////////
struct transformData
{
    glm::vec2 d_position; ///< The position of the transformable object.
    glm::vec2 d_center; ///< The center position of the transformable object.
    float d_angle; ///< The angle at which the transformable is oriented (in degrees).
    float d_scale; ///< The scale at which the transformable is sized.
};

///////////////////////////////////////////////////////////////
/// \class Transform
/// \brief Transform used to manipulate the position, scale, center,
/// and rotation of objects.
///////////////////////////////////////////////////////////////
class Transform
{
    public:

        ///////////////////////////////////////
        /// \fn Transform()
        /// \brief Default constructor.
        ///////////////////////////////////////
        Transform();
        virtual ~Transform();

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setTransformData(transformData t)
        /// \brief Set the transform data for the transformable object.
        /// \param transformData &t - a transformData struct to set for the transformable object.
        /////////////////////////////////////////////////////////////////////////////
        void setTransformData(transformData &t){ m_data = t; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn const transformData &getTransformData()
        /// \brief Get the current transform data for the transformable.
        /// \return const transformData & - transform data for the transformable.
        /////////////////////////////////////////////////////////////////////////////
        const transformData &getTransformData(){ return m_data; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setCenter(SDL_Point point)
        /// \brief Set the center point for the transformable object.
        /// \param glm::vec2 &point - a glm::vec2 you want to set the center point of the transformable object to.
        /////////////////////////////////////////////////////////////////////////////
        void setCenter(glm::vec2 &point){ m_data.d_center = point; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn glm::vec2 * const getCenter()
        /// \brief Get the current center point of the transformable.
        /// \return glm::vec2 - a glm::vec2 corresponding to the current center point of the transformable.
        /////////////////////////////////////////////////////////////////////////////
        const glm::vec2 &getCenter(){ return m_data.d_center; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setAngle(float angle)
        /// \brief Set the angle for the transformable (in degrees).
        /// \param float angle - a float corresponding to an angle (in degrees).
        /////////////////////////////////////////////////////////////////////////////
        void setAngle(float angle){ m_data.d_angle = angle; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn float getAngle()
        /// \brief Get the current angle of the transformable object (in degrees).
        /// \return float - a plain float corresponding to an angle (in degrees).
        /////////////////////////////////////////////////////////////////////////////
        float getAngle(){ return m_data.d_angle; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setPosition(glm::ivec2 position)
        /// \brief Set the position of the transformable in the Window.
        /// \param glm::ivec2 position - a glm::ivec2 specifying a position.
        /////////////////////////////////////////////////////////////////////////////
        void setPosition(glm::vec2 position){ m_data.d_position.x = position.x; m_data.d_position.y = position.y; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn glm::vec2 getPosition()
        /// \brief Get the current position of the transformable.
        /// \return glm::vec2 - a glm::vec2 corresponding to a position.
        /////////////////////////////////////////////////////////////////////////////
        glm::vec2 getPosition(){ return m_data.d_position; };

    private:
        transformData m_data; ///< The raw transform data.
};

} // end namespace pk

#endif // TRANSFORM_HPP
