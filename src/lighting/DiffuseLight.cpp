#include "lighting/DiffuseLight.hpp"

using namespace pk;

DiffuseLight::DiffuseLight(glm::vec4 color, GLfloat ambientIntensity,
                     GLfloat x, GLfloat y, GLfloat z, GLfloat diffuseIntensity)
{
    m_color = color;
	m_ambientIntensity = ambientIntensity;

	m_direction = glm::vec3(x, y, z);
	m_diffuseIntensity = diffuseIntensity;
}

DiffuseLight::~DiffuseLight()
{

}

void DiffuseLight::update(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
                 GLuint diffuseIntensityLocation, GLuint directionLocation)
{
    glUniform4f(ambientColorLocation, m_color.r, m_color.g, m_color.b, m_color.a);
    glUniform1f(ambientIntensityLocation, m_ambientIntensity);

    glUniform1f(diffuseIntensityLocation, m_diffuseIntensity);
    glUniform3f(directionLocation, m_direction.x, m_direction.y, m_direction.z);
}
