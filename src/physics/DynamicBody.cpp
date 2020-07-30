#include "DynamicBody.hpp"

using namespace pk;

DynamicBody::DynamicBody(b2World* world, GLRect rect)
:
    m_world(world)
{
    using namespace physics;

    m_rect = {(rect.d_top - (rect.d_height/2.f))/PPM, (rect.d_left + (rect.d_width/2.f))/PPM,
                (rect.d_width/2.f)/PPM, (rect.d_height/2.f)/PPM};
    m_bodyDef.type = b2_dynamicBody;
    m_bodyDef.position.Set(m_rect.d_left, m_rect.d_top);
    m_bodyDef.fixedRotation = true;
    m_body = m_world->CreateBody(&m_bodyDef);
    m_shape.SetAsBox(m_rect.d_width, m_rect.d_height);
    m_fixtureDef.shape = &m_shape;
    m_fixtureDef.density = 1.f;
    m_fixtureDef.friction = 1.f;
    m_fixtureDef.restitution = 0.f;
    m_body->CreateFixture(&m_fixtureDef);
}

DynamicBody::~DynamicBody()
{

}
