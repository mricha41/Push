#ifndef GLSTATES_HPP
#define GLSTATES_HPP

#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace pk
{
    ///////////////////////////////////
    /// \struct GLStates
    /// \brief Stores the states used
    /// to draw OpenGL objects.
    ///////////////////////////////////
    struct GLStates
    {
        GLuint* modelLocation; ///< Used to bind a uniform value to a location in memory for the GLSL Model matrix.
        GLuint* viewLocation; ///< Used to bind a uniform value to a location in memory for the GLSL View matrix.
        GLuint* projectionLocation; ///< Used to bind a uniform value to a location in memory for the GLSL Projection matrix.
        GLuint* ambientIntensityLocation; ///< Used to bind a uniform value to a location in memory for the ambient intensity of the lighting.
        GLuint* ambientColorLocation; ///< Used to bind a uniform value to a location in memory for the ambient color of the lighting.
        GLuint* diffuseIntensityLocation; ///< Used to bind a uniform value to a location in memory for the diffuse intensity of the lighting.
        GLuint* directionLocation; ///< Used to bind a uniform value to a location in memory for the direction of the lighting.
        GLuint* specularIntensityLocation; ///< Used to bind a uniform value to a location in memory for the specular intensity of the lighting.
        GLuint* shininessLocation; ///< Used to bind a uniform value to a location in memory for the shininess of the lighting.
        GLuint* eyePositionLocation; ///< Used to bind a uniform value to a location in memory for the eye position of the lighting.
    };
}

#endif // GLSTATES_HPP
