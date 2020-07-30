#ifndef GLFRAMEANIMATION_HPP
#define GLFRAMEANIMATION_HPP

#include <stdio.h>

#include <vector>

#include "graphics/GLSprite.hpp"

namespace pk
{

class GLFrameAnimation
{
    public:

        GLFrameAnimation();

        virtual ~GLFrameAnimation();

        void printFrames();

        void addFrame(GLRect frame);

        void loop(bool l){ m_loop = l; };

        void play(GLSprite &sprite);

    private:
        std::vector<GLRect> m_frames;
        bool m_loop;
};

}

#endif // GLFRAMEANIMATION_HPP
