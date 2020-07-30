#include "graphics/GLFrameAnimation.hpp"

#include <algorithm>

#include "SDL2/SDL.h"

using namespace pk;

GLFrameAnimation::GLFrameAnimation()
{

}

GLFrameAnimation::~GLFrameAnimation()
{

}

void GLFrameAnimation::addFrame(GLRect frame)
{
    m_frames.push_back(frame);
}

void GLFrameAnimation::printFrames()
{
    for(auto &&f : m_frames)
        printf("frame top: %f\nframe left: %f\nframe width: %f\nframe height: %f\n", f.d_top, f.d_left, f.d_width, f.d_height);
}

void GLFrameAnimation::play(GLSprite &sprite)
{
    //while(m_loop)
    //{

    for(auto &&f : m_frames)
    {
        sprite.setTextureRect(f);
    }

    std::reverse(m_frames.begin(), m_frames.end());

    //}
}
