#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <GL\glew.h>
#include <glm\glm.hpp>

namespace pk
{

/////////////////////////////////////////
/// \class AmbientLight
/// \brief Class for initializing and
/// using OpenGL ambient lighting.
/////////////////////////////////////////
class AmbientLight
{
public:

    //////////////////////////////////////////////
    /// \fn AmbientLight()
    /// \brief Default constructor - this is probably
    /// not the constructor you want to use - see below.
    //////////////////////////////////////////////
    AmbientLight(){};

    //////////////////////////////////////////////
    /// \fn AmbientLight(glm::vec4 color, GLfloat ambientIntensity)
    /// \brief Construct an OpenGL light source
    /// from a glm::vec4 color and float value
    /// for ambient intensity.
    /// \param glm::vec4 color - the color of the ambient light.
    /// \param GLfloat ambientIntensity - the value
    /// determining the intensity of the ambient light.
    //////////////////////////////////////////////
	AmbientLight(glm::vec4 color, GLfloat ambientIntensity);

	~AmbientLight();

    //////////////////////////////////////////////
    /// \fn virtual void update(GLuint ambientIntensityLocation, GLuint ambientColorLocation)
    /// \brief Use an OpenGL ambient light source.
    /// \param GLuint ambientIntensityLocation - a
    /// value corresponding to a memory location for
    /// ambient intensity.
    /// \param GLuint ambientColorLocation - a value
    /// corresponding to a memory location for ambient
    /// color.
    //////////////////////////////////////////////
	void update(GLuint ambientIntensityLocation, GLuint ambientColorLocation);

private:
	glm::vec4 m_color; ///< Color of the ambient lighting.
	GLfloat m_ambientIntensity; ///< Intensity value for the ambient lighting.
};

}

#endif // LIGHT_HPP
