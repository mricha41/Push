#include "graphics/Camera.hpp"

using namespace pk;

Camera::Camera(glm::vec2 position)
{
	setPosition(position);
}

Camera::~Camera()
{

}

void Camera::update(GLStates &states, glm::mat4 &view)
{
    glm::mat4 scale = glm::scale(m_data.d_model, glm::vec3(m_data.d_scale, 1.0f));
    glm::mat4 rot = glm::rotate(m_data.d_model, glm::radians(m_data.d_angle), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 tran = glm::translate(glm::mat4(1.0f), glm::vec3(m_data.d_position, 0.0f));
    tran = glm::translate(glm::mat4(1.0f), glm::vec3(getOrigin(), 0.f));
    view = tran * rot * scale * view;
    view = glm::translate(view, glm::vec3(-getOrigin(), 0.f));

    glUniformMatrix4fv(*states.viewLocation, 1, GL_FALSE, glm::value_ptr(view));
}
