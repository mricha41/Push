#ifndef SHADER_HPP
#define SHADER_HPP

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

namespace pk
{
    //////////////////////////////////////
    /// \class Shader
    /// \brief Class for supporting OpenGL
    /// GLSL shaders.
    //////////////////////////////////////
    class Shader
    {
        private:
            //////////////////////////////////////////////
            /// \fn void compile(const char* vertexCode, const char* fragmentCode)
            /// \brief Internal function that compiles
            /// and validates the GLSL shaders being loaded.
            //////////////////////////////////////////////
            void compile(const char* vertexCode, const char* fragmentCode);

            //////////////////////////////////////////////
            /// \fn void attach(GLuint theProgram, const char* shaderCode, GLenum shaderType)
            /// \brief Internal function that performs the
            /// necessary actions to attach a shader to the
            /// OpenGL program.
            //////////////////////////////////////////////
            void attach(GLuint theProgram, const char* shaderCode, GLenum shaderType);

        public:
            //////////////////////////////////////////////
            /// \fn Shader()
            /// \brief Default constructor - in most cases
            /// you should be using the other constructor!
            /// Use this in the event you need to load
            /// shaders directly from a C-string rather
            /// than a file.
            //////////////////////////////////////////////
            Shader();

            //////////////////////////////////////////////
            /// \fn Shader(const char* vertexLocation, const char* fragmentLocation)
            /// \brief Preferred constructor for the Shader
            /// class. All OpenGL shader programs need at least a
            /// vertex and fragment shader to work correctly.
            //////////////////////////////////////////////
            Shader(const char* vertexLocation, const char* fragmentLocation);

            ~Shader();

            //////////////////////////////////////////////
            /// \fn void loadFromString(const char* vertexCode, const char* fragmentCode)
            /// \brief Load OpenGL shader programs from
            /// C-strings.
            /// \param const char* vertexCode - a C-style string containing the vertex shader code.
            /// \param const char* fragmentCode - a C-style string containing the fragment shader code.
            //////////////////////////////////////////////
            void loadFromString(const char* vertexCode, const char* fragmentCode);

            //////////////////////////////////////////////
            /// \fn void load(const char* vertexLocation, const char* fragmentLocation)
            /// \brief Load OpenGL shader programs from
            /// file locations specified with C-style strings.
            /// \param const char* vertexLocation - a C-style string containing the vertex shader file location.
            /// \param const char* fragmentLocation - a C-style string containing the fragment shader file location.
            //////////////////////////////////////////////
            void load(const char* vertexLocation, const char* fragmentLocation);

            //////////////////////////////////////////////
            /// \fn std::string read(const char* fileLocation)
            /// \brief Read the contents of a shader file
            /// and output a std::string to be loaded as
            /// an OpenGL GLSL shader.
            //////////////////////////////////////////////
            std::string read(const char* fileLocation);

            //////////////////////////////////////////////
            /// \fn GLuint &getProjectionLocation()
            /// \brief Get the memory location of the OpenGL
            /// Projection matrix in use.
            /// \return GLuint - an OpenGL unsigned integer
            /// mapped to the address of the Projection matrix.
            //////////////////////////////////////////////
            GLuint &getProjectionLocation() { return m_uniformProjection; };

            //////////////////////////////////////////////
            /// \fn GLuint &getModelLocation()
            /// \brief Get the memory location of the OpenGL
            /// Model matrix in use.
            /// \return GLuint - an OpenGL unsigned integer
            /// mapped to the address of the Model matrix.
            //////////////////////////////////////////////
            GLuint &getModelLocation() { return m_uniformModel; };

            //////////////////////////////////////////////
            /// \fn GLuint &getViewLocation()
            /// \brief Get the memory location of the OpenGL
            /// View matrix in use.
            /// \return GLuint - an OpenGL unsigned integer
            /// mapped to the address of the View matrix.
            //////////////////////////////////////////////
            GLuint &getViewLocation() { return m_uniformView; };

            //////////////////////////////////////////////
            /// \fn GLuint &getAmbientIntensityLocation()
            /// \brief Get the memory location of the ambient
            /// intensity for lighting.
            /// \return GLuint - an OpenGL unsigned integer
            /// mapped to the address of the ambient intensity.
            //////////////////////////////////////////////
            GLuint &getAmbientIntensityLocation() { return m_uniformAmbientIntensity; };

            //////////////////////////////////////////////
            /// \fn GLuint &getAmbientColorLocation()
            /// \brief Get the memory location of the ambient
            /// color for lighting.
            /// \return GLuint - an OpenGL unsigned integer
            /// mapped to the address of the ambient color.
            //////////////////////////////////////////////
            GLuint &getAmbientColorLocation() { return m_uniformAmbientColor; };

            //////////////////////////////////////////////
            /// \fn GLuint &getDiffuseIntensityLocation()
            /// \brief Get the memory location of the diffuse
            /// intensity for lighting.
            /// \return GLuint - an OpenGL unsigned integer
            /// mapped to the address of the diffuse intensity.
            //////////////////////////////////////////////
            GLuint &getDiffuseIntensityLocation() { return m_uniformDiffuseIntensity; };

            //////////////////////////////////////////////
            /// \fn GLuint &getDirectionLocation()
            /// \brief Get the memory location of the direction
            /// of the lighting.
            /// \return GLuint - an OpenGL unsigned integer
            /// mapped to the address of the light's direction.
            //////////////////////////////////////////////
            GLuint &getDirectionLocation() { return m_uniformDirection; };

            //////////////////////////////////////////////
            /// \fn GLuint &getEyePositionLocation()
            /// \brief Get the memory location of the eye position
            /// of the lighting.
            /// \return GLuint - an OpenGL unsigned integer
            /// mapped to the address of the light's eye position.
            //////////////////////////////////////////////
            GLuint &getEyePositionLocation() { return m_uniformEyePosition; };

            //////////////////////////////////////////////
            /// \fn GLuint &getSpecularIntensityLocation()
            /// \brief Get the memory location of the specular
            /// intensity of the lighting.
            /// \return GLuint - an OpenGL unsigned integer
            /// mapped to the address of the light's specular intensity.
            //////////////////////////////////////////////
            GLuint &getSpecularIntensityLocation() { return m_uniformSpecularIntensity; };

            //////////////////////////////////////////////
            /// \fn GLuint &getShininessLocation()
            /// \brief Get the memory location of the shininess
            /// of the lighting.
            /// \return GLuint - an OpenGL unsigned integer
            /// mapped to the address of the light's shininess.
            //////////////////////////////////////////////
            GLuint &getShininessLocation() { return m_uniformShininess; };

            //////////////////////////////////////////////
            /// \fn void use()
            /// \brief Call the necessary OpenGL code
            /// to use the shader. Needs to be called before
            /// drawing occurs in the game loop.
            //////////////////////////////////////////////
            void use();

            //////////////////////////////////////////////
            /// \fn void clear()
            /// \brief Resets all states and data contained
            /// in the Shader class. Calls glDeleteProgram(...)
            /// because Shader class owns the shader program.
            //////////////////////////////////////////////
            void clear();

        private:
            GLuint m_shaderID; ///< The OpenGL GLSL shader ID.
            GLuint m_uniformProjection; ///< An OpenGL Projection matrix memory location.
            GLuint m_uniformModel; ///< An OpenGL Model matrix memory location.
            GLuint m_uniformView; ///< An OpenGL View matrix memory location.
            GLuint m_uniformAmbientIntensity; ///< A memory location for ambient intensity.
            GLuint m_uniformAmbientColor; ///< A memory location for lighting ambient color.
            GLuint m_uniformDiffuseIntensity; ///< A memory location for diffuse intensity.
            GLuint m_uniformDirection; ///< A memory location for direction.
            GLuint m_uniformEyePosition; ///< A memory location for eye position (camera).
            GLuint m_uniformSpecularIntensity; ///< A memory location for the specular intensity of the material.
            GLuint m_uniformShininess; ///< A memory location for the shininess of the material.
    };
}

#endif // SHADER_HPP
