#ifndef KINEMATICBODY_HPP
#define KINEMATICBODY_HPP

#include <Box2D/Box2D.h>

#include "graphics/GLTransformable.hpp"
#include "physics/PhysicsHelpers.hpp"

namespace pk
{

/////////////////////////
/// \class KinematicBody
/// \brief A class wrapper to
/// ease the instantiation and use of Box2D kinematic bodies.
/// It also performs conversions between
/// meters in physics space and pixels in
/// screen space automatically.
/////////////////////////
class KinematicBody
{
    private:
        ///////////////////////////////////////////////
        /// \fn KinematicBody()
        /// \brief Default constructor - Inaccessible.
        ///////////////////////////////////////////////
        KinematicBody(){};

    public:

        ///////////////////////////////////////////////
        /// \fn KinematicBody(b2World* world, GLRect rect)
        /// \brief Preferred constructor.
        ///////////////////////////////////////////////
        KinematicBody(b2World* world, GLRect rect);

        virtual ~KinematicBody();

        /////////////////////////////////
        /// \fn b2World* getWorld()
        /// \brief Get a pointer to the Box2D world
        /// the static platform is tied to.
        /////////////////////////////////
        b2World* getWorld(){ return m_world; };

        //////////////////////////////////////////
        /// \fn void setDensity(float density)
        /// \brief Set the density of the body.
        /// \param float density - a plain old float.
        //////////////////////////////////////////
        void setDensity(float density){ m_body->GetFixtureList()[0].SetDensity(density); };

        //////////////////////////////////////////
        /// \fn float getDensity()
        /// \brief Get the density of the body.
        /// \return float - a plain old float.
        //////////////////////////////////////////
        float getDensity(){ return m_body->GetFixtureList()[0].GetDensity(); };

        ///////////////////////////////////////////
        /// \fn void setFriction(float friction)
        /// \brief Set the friction for the body.
        /// \param float friction - a plain old float.
        ///////////////////////////////////////////
        void setFriction(float friction){ m_body->GetFixtureList()[0].SetFriction(friction); };

        ///////////////////////////////////////////
        /// \fn float getFriction()
        /// \brief Get the friction of the body.
        /// \return float - a plain old float.
        ///////////////////////////////////////////
        float getFriction(){ return m_body->GetFixtureList()[0].GetFriction(); };

        ///////////////////////////////////////////
        /// \fn void setRestitution(float restitution)
        /// \brief Set the restitution (bounciness) for the body.
        /// \param float restitution - a plain old float.
        ///////////////////////////////////////////
        void setRestitution(float restitution){ m_body->GetFixtureList()[0].SetRestitution(restitution); };

        ///////////////////////////////////////////
        /// \fn float getRestitution()
        /// \brief Get the restitution of the body.
        /// \return float - a plain old float.
        ///////////////////////////////////////////
        float getRestitution(){ m_body->GetFixtureList()[0].GetRestitution(); };

        ///////////////////////////////////////////
        /// \fn void setFixedRotation(bool r)
        /// \brief Set the body's rotation as fixed (no rotation).
        /// \param bool r - a plain old bool.
        ///////////////////////////////////////////
        void setFixedRotation(bool r){ m_bodyDef.fixedRotation = r; };

        ///////////////////////////////////////////
        /// \fn void allowSleep(bool s)
        /// \brief Set the body to allow sleeping. This
        /// increases efficiency and performance of Box2D
        /// while also preventing bodies from randomly jittering
        /// when they should appear still.
        /// \param bool s - a plain old bool.
        ///////////////////////////////////////////
        void allowSleep(bool s){ m_bodyDef.allowSleep = s; };

        ///////////////////////////////////////////
        /// \fn glm::vec2 getPosition()
        /// \brief Get the position of the body in Box2D units
        /// (meters).
        /// \return b2Vec2 - a Box2D vector of floats.
        ///////////////////////////////////////////
        b2Vec2 getPosition(){ return { m_body->GetPosition().x, m_body->GetPosition().y}; };

        ///////////////////////////////////////////
        /// \fn void setPosition(glm::vec2 position)
        /// \brief Set the position of the KinematicBody.
        /// \param glm::vec2 position - the position given
        /// as a glm::vec2 of floats.
        ///////////////////////////////////////////
        void setPosition(glm::vec2 position){ m_body->SetTransform({position.x, position.y}, m_body->GetAngle()); };

        ////////////////////////////////////////////
        /// \fn float getRotation()
        /// \brief Get the rotation of the KinematicBody.
        /// \return float - the rotation given as a float
        /// in degrees.
        ////////////////////////////////////////////
        float getRotation(){ return m_body->GetAngle(); };

        ////////////////////////////////////////////
        /// \fn void setTransform(b2Vec2 position, float angle)
        /// \brief Set the transform (position and angle) of
        /// the KinematicBody.
        /// \param b2Vec2 position - the position given as
        /// a b2Vec2 of floats.
        /// \param float angle - the angle given as a
        /// float in degrees.
        ////////////////////////////////////////////
        void setTransform(b2Vec2 position, float angle){ m_body->SetTransform(position, angle); };

        ///////////////////////////////////////////
        /// \fn glm::vec2 getPositionInPixels()
        /// \brief Get the position of the body in
        /// screen units (pixels).
        /// \return glm::vec2 - a vector of floats.
        ///////////////////////////////////////////
        glm::vec2 getPositionInPixels(){ return physics::metersToPixels(m_body->GetPosition()); };

        ///////////////////////////////////////////
        /// \fn void setLinearVelocity(glm::vec2 v)
        /// \brief Set the linear velocity of the
        /// body.
        /// \param glm::vec2 v - a vector of floats.
        ///////////////////////////////////////////
        void setLinearVelocity(glm::vec2 v){ m_body->SetLinearVelocity({v.x, v.y}); };

        ///////////////////////////////////////////
        /// \fn glm::vec2 getLinearVelocity()
        /// \brief Get the linear velocity of the
        /// body.
        /// \return glm::vec2 - a vector of floats.
        ///////////////////////////////////////////
        glm::vec2 getLinearVelocity(){ return {m_body->GetLinearVelocity().x, m_body->GetLinearVelocity().y}; };

        ///////////////////////////////////////////
        /// \fn void destroyBody()
        /// \brief Destroy the KinematicBody. Safely
        /// removes the body using Box2D internals.
        ///////////////////////////////////////////
        void destroyBody(){ m_world->DestroyBody(m_body); m_body = NULL; };

    private:
        b2World* m_world; ///< A pointer to the Box2D world.
        b2BodyDef m_bodyDef; ///< A Box2D body definition structure.
        b2PolygonShape m_shape; ///< A Box2D polygon shape.
        b2FixtureDef m_fixtureDef; ///< A Box2D fixture definition structure.
        b2Body* m_body; ///< A Box2D body.
        GLRect m_rect; ///< A GLRect structure.
};

}

#endif // KINEMATICBODY_HPP
