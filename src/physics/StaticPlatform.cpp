#include "physics/StaticPlatform.hpp"

#include <stdio.h>
#include <cmath>

#include "core/Game.hpp"

using namespace pk;

StaticPlatform::StaticPlatform(b2World* world, GLRect rect)
:
    m_world(world)
{
    using namespace physics;

    m_rect = {(rect.d_top - (rect.d_height/2.f))/PPM, (rect.d_left + (rect.d_width/2.f))/PPM,
                (rect.d_width/2.f)/PPM, (rect.d_height/2.f)/PPM};

    m_fixtureDef.shape = &m_shape;
    m_fixtureDef.density = 1.f;
    m_fixtureDef.friction = 1.f;
    m_fixtureDef.restitution = 0.f;
    m_bodyDef.type = b2_staticBody;
    m_shape.SetAsBox(m_rect.d_width, m_rect.d_height);

    //box2d coordinates are flipped relative
    //to rendering coordinates on the y axis
    //an adjustment is necessary to place objects
    //as they are expected to be. Renderer grows objects
    //from the top-left corner down, box2d grows objects
    //from the top-left corner up.
    if(m_rect.d_height > ((tiley/2.f)/PPM))//greater than one tile high...
    {
        float atile = tiley/PPM;//a tile
        float fix = ((m_rect.d_height*2.f)/atile);//number of tiles in height
        //float fix = numtiles - atile;//difference in tiles
        m_bodyDef.position.Set(m_rect.d_left, m_rect.d_top + fix);
    }
    else//otherwise leave it alone if it's one tile high
        m_bodyDef.position.Set(m_rect.d_left, m_rect.d_top);

    m_body = m_world->CreateBody(&m_bodyDef);
    m_body->CreateFixture(&m_fixtureDef);
}

StaticPlatform::~StaticPlatform()
{

}
