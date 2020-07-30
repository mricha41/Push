#ifndef SAWBLADE_HPP
#define SAWBLADE_HPP

#include "steeriously/libinc.hpp"

#include "graphics/GLSprite.hpp"

namespace pk
{

class SawBlade
{
    public:
        SawBlade();

        SawBlade(GLTexture& texture, GLRect rect, float speed, steer::Path& path, steer::BehaviorParameters* params);

        virtual ~SawBlade();

        pk::GLSprite& getSprite(){ return m_sprite; };

        void update(float dt);

    private:
        pk::GLSprite m_sprite;
        steer::PathFollowingComponent m_pathFollowing;
        steer::Path m_path;
};

}

#endif // SAWBLADE_HPP
