#ifndef DIFFUSELIGHT_HPP
#define DIFFUSELIGHT_HPP

#include <GL\glew.h>
#include <glm\glm.hpp>

namespace pk
{
//////////////////////////////////
/// \class DiffuseLight
/// \brief Class for creating an
/// OpenGL diffuse light.
//////////////////////////////////
class DiffuseLight
{
    public:
        //////////////////////////////////////////////
        /// \fn DiffuseLight()
        /// \brief Default constructor - this is probably
        /// not the constructor you want to use - see below.
        //////////////////////////////////////////////
        DiffuseLight(){};

        //////////////////////////////////////////////
        /// \fn DiffuseLight(glm::vec4 color, GLfloat ambientIntensity,
        ///          GLfloat x, GLfloat y, GLfloat z, GLfloat diffuseIntensity);
        /// \brief Construct an OpenGL diffuse light source
        /// from parameters for ambient and diffuse lights.
        /// \param glm::vec4 color - the color of the ambient light.
        /// \param GLfloat ambientIntensity - the value
        /// determining the intensity of the ambient light.
        /// \param GLfloat x - the direction of the light on the x-axis.
        /// \param GLfloat y - the direction of the light on the y-axis.
        /// \param GLfloat z - the direction of the light on the z-axis.
        /// \param GLfloat diffuseIntensity - the value determining
        /// the intensity of the diffuse light.
        //////////////////////////////////////////////
        DiffuseLight(glm::vec4 color, GLfloat ambientIntensity,
                     GLfloat x, GLfloat y, GLfloat z, GLfloat diffuseIntensity);

        virtual ~DiffuseLight();

        //////////////////////////////////////////////
        /// \fn void update(GLuint ambientIntensityLocation, GLuint ambientColorLocation
        ///      GLfloat diffuseIntensityLocation, GLfloat directionLocation);
        /// \brief Use an OpenGL diffuse light source.
        /// \param GLuint ambientIntensityLocation - a
        /// value corresponding to a memory location for
        /// ambient intensity.
        /// \param GLuint ambientColorLocation - a value
        /// corresponding to a memory location for ambient
        /// color.
        /// \param GLuint diffuseIntensityLocation - a value
        /// corresponding to a memory location for diffuse intensity.
        /// \param GLuint directionLocation - a value
        /// corresponding to a memory location for the light's
        /// direction.
        //////////////////////////////////////////////
        void update(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
                 GLuint diffuseIntensityLocation, GLuint directionLocation);

    private:
        glm::vec4 m_color; ///< Color of the ambient lighting.
        GLfloat m_ambientIntensity; ///< Intensity value for the ambient lighting.
        glm::vec3 m_direction; ///< The direction that the light points.
        GLfloat m_diffuseIntensity; ///< Intensity value for the diffuse lighting.
};

}

#endif // DIFFUSELIGHT_HPP
