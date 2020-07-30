#include "Material.hpp"

using namespace pk;

Material::Material()
{
    m_specularIntensity = 0.f;
    m_shininess = 0.f;
}

Material::Material(GLfloat specularIntensity, GLfloat shininess)
{
    m_specularIntensity = specularIntensity;
    m_shininess = shininess;
}

Material::~Material()
{

}

void Material::use(GLuint specularIntensityLocation, GLuint shininessLocation)
{
    glUniform1f(specularIntensityLocation, m_specularIntensity);
    glUniform1f(shininessLocation, m_shininess);
}
