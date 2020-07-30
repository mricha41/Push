#include "graphics/GLTexture.hpp"

using namespace pk;

GLTexture::GLTexture(std::string path)
:
    m_surf(nullptr),
    m_pixelFormat(0),
    m_textureID(0),
    m_rect(),
    m_bitDepth(0),
    m_textureCoordinate_S(GLTextureWrap::REPEAT),
    m_textureCoordinate_T(GLTextureWrap::REPEAT),
    m_textureCoordinate_R(GLTextureWrap::REPEAT),
    m_textureFilter_MIN(GLTextureFilter::LINEAR),
    m_textureFilter_MAG(GLTextureFilter::LINEAR)
{
    load(path);
}

GLTexture::~GLTexture()
{
	clear();
}

void GLTexture::load(std::string path)
{
    m_surf = IMG_Load(path.c_str());

    m_rect.d_left = 0.f;
    m_rect.d_top = 0.f;
    m_rect.d_width = m_surf->w;
    m_rect.d_height = m_surf->h;

    m_pixelFormat = GL_RGB;

    if(m_surf->format->BytesPerPixel == 4) {
        m_pixelFormat = GL_RGBA;
    }

    updateParameters();
}

void GLTexture::updateParameters()
{
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_textureCoordinate_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_textureCoordinate_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_textureFilter_MIN);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_textureFilter_MAG);

    glTexImage2D(GL_TEXTURE_2D, 0, m_pixelFormat, m_surf->w, m_surf->h, 0, m_pixelFormat, GL_UNSIGNED_BYTE, m_surf->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void GLTexture::setTextureCoordinateWrapParameters(GLint S, GLint T, GLint R)
{
    m_textureCoordinate_S = S;
    m_textureCoordinate_T = T;
    m_textureCoordinate_R = R;

    updateParameters();
}

void GLTexture::setTextureFilterParameters(GLint min, GLint mag)
{
    m_textureFilter_MIN = min;
    m_textureFilter_MAG = mag;

    updateParameters();
}


void GLTexture::use()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void GLTexture::disable()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(0);
    glDisable(GL_TEXTURE_2D);
}

void GLTexture::clear()
{
	glDeleteTextures(1, &m_textureID);
	m_textureID = 0;
	m_rect = {0.f, 0.f, 0.f, 0.f};
	m_bitDepth = 0;
}
