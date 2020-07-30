#include "CharacterBody.hpp"
#include "physics/SensorData.hpp"

using namespace pk;

CharacterBody::CharacterBody(b2World* world, GLRect rect, int id)
:
    m_world(world),
    m_characterID(id)
{
    using namespace physics;

    m_rect = {(rect.d_top - (rect.d_height/2.f))/PPM, (rect.d_left + (rect.d_width/2.f))/PPM,
                (rect.d_width/2.f)/PPM, (rect.d_height/2.f)/PPM};
    m_bodyDef.type = b2_dynamicBody;
    m_bodyDef.position.Set(m_rect.d_left, m_rect.d_top);
    m_bodyDef.fixedRotation = true;
    m_bodyDef.allowSleep = false;

    m_shape.SetAsBox(m_rect.d_width, m_rect.d_height);
    m_fixtureDef.shape = &m_shape;
    m_fixtureDef.density = 1.f;
    m_fixtureDef.friction = 1.f;

    m_body = m_world->CreateBody(&m_bodyDef);

    m_body->CreateFixture(&m_fixtureDef);

    m_shape.SetAsBox(m_rect.d_width*0.8f, m_rect.d_height*0.1f, b2Vec2(m_rect.d_width*0.1f, m_rect.d_height), 0);
    m_fixtureDef.isSensor = true;
    b2Fixture* footSensorFixture = m_body->CreateFixture(&m_fixtureDef);
    m_footSensorData = new SensorData(SensorType::FOOT);
    footSensorFixture->SetUserData(static_cast<void*>(m_footSensorData));

    m_shape.SetAsBox(m_rect.d_width*0.1f, m_rect.d_height*0.1f, b2Vec2(-0.6f, m_rect.d_height*0.5f), 0);
    m_fixtureDef.isSensor = true;
    b2Fixture* leftSensorFixture = m_body->CreateFixture(&m_fixtureDef);
    m_leftSensorData = new SensorData(SensorType::LEFT);
    leftSensorFixture->SetUserData(static_cast<void*>(m_leftSensorData));

    m_shape.SetAsBox(m_rect.d_width*0.1f, m_rect.d_height*0.1f, b2Vec2(m_rect.d_width, m_rect.d_height*0.5f), 0);
    m_fixtureDef.isSensor = true;
    b2Fixture* rightSensorFixture = m_body->CreateFixture(&m_fixtureDef);
    m_rightSensorData = new SensorData(SensorType::RIGHT);
    rightSensorFixture->SetUserData(static_cast<void*>(m_rightSensorData));

    m_shape.SetAsBox(m_rect.d_width*0.1f, m_rect.d_height*0.1f, b2Vec2(m_rect.d_width*0.5f, -0.6f), 0);
    m_fixtureDef.isSensor = true;
    b2Fixture* topSensorFixture = m_body->CreateFixture(&m_fixtureDef);
    m_topSensorData = new SensorData(SensorType::TOP);
    topSensorFixture->SetUserData(static_cast<void*>(m_topSensorData));
}

bool CharacterBody::canJump()
{
    return m_footSensorData->getContacts() > 0;
}

bool CharacterBody::touchingWall()
{
    /*if(m_leftSensorData->getContacts() > 0)
        printf("left: %i\n", m_leftSensorData->getContacts());

    if(m_rightSensorData->getContacts() > 0)
        printf("right: %i\n", m_rightSensorData->getContacts());

    if(m_topSensorData->getContacts() > 0)
        printf("top: %i\n", m_topSensorData->getContacts());*/

    if(m_leftSensorData->getContacts() > 0 || m_rightSensorData->getContacts() > 0
            || m_topSensorData->getContacts() > 0)
    {
        //m_fixtureDef.friction = 0.f;
        return true;
    }
    //m_fixtureDef.friction = 1.f;
    return false;
}

void CharacterBody::destroyBody()
{
    m_world->DestroyBody(m_body);
    m_body = NULL;

    delete m_footSensorData;
    delete m_leftSensorData;
    delete m_rightSensorData;
    delete m_topSensorData;
}

CharacterBody::~CharacterBody()
{

}
