#include "graphics/Texture.hpp"

using namespace pk;

Texture::Texture()
{

}

Texture::~Texture()
{
    SDL_DestroyTexture(m_texture);
}

bool Texture::loadTexture(const char *path, SDL_Renderer * const renderTarget)
{
    SDL_Surface *surf = IMG_Load(path);
    if(surf == NULL)
    {
        printf( "Unable to load image from path:\n %s\n SDL Error:\n %s\n", path, SDL_GetError() );
        return false;
    }
    else
    {
        m_texture = SDL_CreateTextureFromSurface(renderTarget, surf);
        if(m_texture == NULL)
        {
            printf( "Unable to create texture from image on path:\n %s\n SDL Error:\n %s\n", path, SDL_GetError() );
            return false;
        }
        else
        {
            m_width = surf->w;
            m_height = surf->h;
            SDL_FreeSurface(surf);
            return true;
        }
    }
}

bool Texture::loadTexture(SDL_Texture * const texture)
{
    m_texture = texture;
    if(m_texture == NULL) {
        printf("Unable to assign texture from existing texture.\n SDL Error:\n %s\n", SDL_GetError());
        return false;
    }
    return true;
}
