#include "lighting/AmbientLight.hpp"

using namespace pk;

AmbientLight::AmbientLight(glm::vec4 color, GLfloat ambientIntensity)
{
	m_color = color;
	m_ambientIntensity = ambientIntensity;
}

AmbientLight::~AmbientLight()
{

}

void AmbientLight::update(GLuint ambientIntensityLocation, GLuint ambientColorLocation)
{
    glUniform4f(ambientColorLocation, m_color.r, m_color.g, m_color.b, m_color.a);
    glUniform1f(ambientIntensityLocation, m_ambientIntensity);
}
