#ifndef GLTEXTURE_HPP
#define GLTEXTURE_HPP

#include <stdio.h>
#include <string>

#include "GL/glew.h"

#include <SDL2/SDL_image.h>

#include "graphics/GLTransformable.hpp"

namespace pk
{

////////////////////////////////////////////////////
/// \enum GLTextureFilter
/// \brief Values for setting the texture filter
/// functions for GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, and
/// GL_TEXTURE_WRAP_R. These values have been
/// aliased with member data (SEE MEMBER DATA FOR DETAILS).
/// For further reference, refer to the OpenGL refpages:
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
////////////////////////////////////////////////////
enum GLTextureWrap
{
    CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
    CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
    MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
    REPEAT = GL_REPEAT,
    MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE
};

////////////////////////////////////////////////////
/// \enum GLTextureFilter
/// \brief Values for setting the texture filter
/// functions for both GL_TEXTURE_MIN_FILTER and
/// GL_TEXTURE_MAG_FILTER. These values have been
/// aliased with member data (SEE MEMBER DATA FOR DETAILS).
/// For further reference, refer to the OpenGL refpages:
/// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
////////////////////////////////////////////////////
enum GLTextureFilter
{
    NEAREST = GL_NEAREST,
    LINEAR = GL_LINEAR,
    NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
    LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
    LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
};

//////////////////////////////////////////
/// \class GLTexture
/// \brief Class for creating textures
/// usable with OpenGL from SDL.
//////////////////////////////////////////
class GLTexture
{
    private:
        //////////////////////////////////////////////
        /// \fn GLTexture()
        /// \brief Default constructor - INACCESSIBLE!
        //////////////////////////////////////////////
        GLTexture(){};

        //////////////////////////////////////////////
        /// \fn void updateParameters()
        /// \brief Internally resets the texture parameters
        /// so that textures render as expected.
        //////////////////////////////////////////////
        void updateParameters();

    public:

        virtual ~GLTexture();

        //////////////////////////////////////////////
        /// \fn GLTexture(char* path)
        /// \brief Constructor for a GLTexture from
        /// a file location.
        /// \param char* path - path to the image file.
        //////////////////////////////////////////////
        GLTexture(std::string path);

        //////////////////////////////////////////////
        /// \fn GLRect getTextureRect()
        /// \brief Get the GLTexture's texture rect with
        /// its bounds.
        /// \return GLRect - a GLRect corresponding to the
        /// internal dimensions of the GLTexture.
        //////////////////////////////////////////////
        GLRect getTextureRect(){ return m_rect; };

        //////////////////////////////////////////////
        /// \fn void setTextureRect(GLRect rect)
        /// \brief Set the GLTexture's texture rect.
        /// \param GLRect rect - a GLRect you wish to assign
        /// to the GLTexture.
        //////////////////////////////////////////////
        void setTextureRect(GLRect rect){ m_rect = rect; updateParameters(); };

        //////////////////////////////////////////////
        /// \fn void setTextureCoordinateWrapParameters(GLint S, GLint T, GLint R)
        /// \brief Set the texture coordinate wrap parameters
        /// for the texture.
        /// \param GLint S - the OpenGL wrap parameter for S texture coordinates.
        /// \param GLint T - the OpenGL wrap parameter for T texture coordinates.
        /// \param GLint R - the OpenGL wrap parameter for R texture coordinates.
        //////////////////////////////////////////////
        void setTextureCoordinateWrapParameters(GLint S, GLint T, GLint R);

        //////////////////////////////////////////////
        /// \fn void setTextureFilterParameters(GLint min, GLint mag)
        /// \brief Set the texture filter parameters
        /// for the texture.
        /// \param GLint min - the OpenGL minifying function parameter for the texture.
        /// \param GLint mag - the OpenGL magnifying function parameter for the texture.
        //////////////////////////////////////////////
        void setTextureFilterParameters(GLint min, GLint mag);

        //////////////////////////////////////////////
        /// \fn load(char* path)
        /// \brief Load the GLTexture from an image
        /// file on the path.
        //////////////////////////////////////////////
        void load(std::string path);

        //////////////////////////////////////////////
        /// \fn use()
        /// \brief Use the GLTexture by activating and
        /// binding it to your OpenGL program.
        //////////////////////////////////////////////
        void use();

        //////////////////////////////////////////////
        /// \fn disable()
        /// \brief Disables the GLTexture by unbinding
        /// the texture and calling glDisable(...).
        //////////////////////////////////////////////
        void disable();

        //////////////////////////////////////////////
        /// \fn clear()
        /// \brief Clear all of the GLTexture data.
        //////////////////////////////////////////////
        void clear();

private:
    SDL_Surface* m_surf; ///< An SDL surface useful for loading pixel data from a file.
    int m_pixelFormat; ///< Stores the pixel format of the image that is loaded.
	GLuint m_textureID; ///< The identifier for the texture.
	GLRect m_rect; ///< The GLRect defining the bounds of the texture.
	int m_bitDepth; ///< The bit depth of the texture.
	GLint m_textureCoordinate_S; ///< The wrap parameter for the S coordinate of the texture.
	GLint m_textureCoordinate_T; ///< The wrap parameter for the T coordinate of the texture.
	GLint m_textureCoordinate_R; ///< The wrap parameter for the R coordinate of the texture.
	GLint m_textureFilter_MIN; ///< The texture parameter for the minifying function.
	GLint m_textureFilter_MAG; ///< The texture parameter for the magnifying function.
};

}

#endif // GLTEXTURE_HPP
