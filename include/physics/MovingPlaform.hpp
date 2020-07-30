#ifndef MOVINGPLAFORM_HPP
#define MOVINGPLAFORM_HPP

#include "physics/KinematicBody.hpp"
#include "graphics/GLSprite.hpp"

namespace pk
{

////////////////////////////////
/// \class MovingPlatform
/// \brief A class for creating
/// a moving platform using a
/// Box2D kinematic body and an
/// OpenGL sprite.
////////////////////////////////
class MovingPlaform
{
    public:
        //////////////////////////////////
        /// \fn MovingPlaform(b2World* world, GLTexture& texture, GLRect rect, glm::vec2 endPosition, float platformSpeed)
        /// \brief Preferred constructor.
        //////////////////////////////////
        MovingPlaform(b2World* world, GLTexture& texture, GLRect rect, glm::vec2 endPosition, float platformSpeed);
        virtual ~MovingPlaform();

        ////////////////////////////////
        /// \fn pk::GLSprite& getSprite()
        /// \brief Get the sprite for the
        /// moving platform.
        /// \return GLSprite& - a reference
        /// to a GLSprite object.
        ////////////////////////////////
        pk::GLSprite& getSprite(){ return m_sprite; };

        ////////////////////////////////
        /// \fn void setPlatformSpeed(float speed)
        /// \brief Set the platform speed.
        /// \param float speed - the speed
        /// given as a float.
        ////////////////////////////////
        void setPlatformSpeed(float speed){ m_platformSpeed = speed; };

        ////////////////////////////////
        /// \fn void update()
        /// \brief Update the platform position.
        /// Call this function in the update
        /// portion of the game loop.
        ////////////////////////////////
        void update();

    protected:

    private:
        b2World* m_world; ///< a pointer to a Box2D world.
        pk::KinematicBody m_body; ///< a kinematic body.
        pk::GLSprite m_sprite; ///< an OpenGL sprite.
        int m_direction; ///< facing direction of the platform.
        glm::vec2 m_initialPosition; ///< initial position of the platform.
        glm::vec2 m_endPosition; ///< ending position of the platform.
        float m_platformSpeed; ///< speed of the platform movement.
};

}

#endif // MOVINGPLAFORM_HPP
