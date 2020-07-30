#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "graphics/GLTransformable.hpp"

namespace pk
{

class Camera : public GLTransformable
{
private:
    Camera() {};
public:

    Camera(glm::vec2 startPosition);

    ~Camera();

    void update(GLStates &states, glm::mat4 &view);

    GLfloat m_zoom;
};

}

#endif // CAMERA_HPP
