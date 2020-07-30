#ifndef STATICPLATFORM_HPP
#define STATICPLATFORM_HPP

#include <Box2D/Box2D.h>

#include "graphics/GLTransformable.hpp"
#include "physics/PhysicsHelpers.hpp"

namespace pk
{

/////////////////////////
/// \class StaticBody
/// \brief A class wrapper to
/// ease the instantiation and use of Box2D static bodies.
/// It also performs conversions between
/// meters in physics space and pixels in
/// screen space automatically.
/////////////////////////
class StaticPlatform
{
    private:
        ///////////////////////////////////////////////
        /// \fn StaticPlatform()
        /// \brief Default constructor - Inaccessible.
        ///////////////////////////////////////////////
        StaticPlatform(){};
    public:
        //////////////////////////////////////////
        /// \fn StaticPlatform(b2World* world, GLRect rect)
        /// \brief Preferred constructor for a
        /// StaticBody.
        //////////////////////////////////////////
        StaticPlatform(b2World* world, GLRect rect);

        virtual ~StaticPlatform();

        /////////////////////////////////
        /// \fn b2World* getWorld()
        /// \brief Get a pointer to the Box2D world
        /// the static platform is tied to.
        /////////////////////////////////
        b2World* getWorld(){ return m_world; };

    private:
        b2World* m_world; ///< A pointer to the Box2D world.
        b2BodyDef m_bodyDef; ///< A Box2D body definition structure.
        b2PolygonShape m_shape; ///< A Box2D polygon shape.
        b2FixtureDef m_fixtureDef; ///< A Box2D fixture definition structure.
        b2Body* m_body; ///< A Box2D body.
        GLRect m_rect; ///< A GLRect structure.
};

}

#endif // STATICPLATFORM_HPP
