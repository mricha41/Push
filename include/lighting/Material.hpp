#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <GL\glew.h>
#include <glm\glm.hpp>

namespace pk
{
//////////////////////////////////
/// \class Material
/// \brief Class for creating an
/// OpenGL material with specular
/// lighting (reflection).
//////////////////////////////////
class Material
{
    public:
        //////////////////////////////////////////////
        /// \fn Material()
        /// \brief Default constructor - this is probably
        /// not the constructor you want to use - see below.
        //////////////////////////////////////////////
        Material();

        Material(GLfloat specularIntensity, GLfloat shininess);

        virtual ~Material();

        void use(GLuint specularIntensityLocation, GLuint shininessLocation);

    private:
        GLfloat m_specularIntensity; ///< The intensity of the reflection.
        GLfloat m_shininess; ///< The specular "power" or shininess of the material.
};

}

#endif // MATERIAL_HPP
