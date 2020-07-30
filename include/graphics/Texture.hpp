#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace pk
{

///////////////////////////////////////////////////////////////
/// \class Texture
/// \brief A class implemented using the Facade pattern
/// used for loading SDL_Texture data.
//////////////////////////////////////////////////////////////
class Texture
{
    public:

        ////////////////////////////////
        /// \fn Texture()
        /// \brief Default constructor.
        ////////////////////////////////
        Texture();
        virtual ~Texture();

        /////////////////////////////////////////////////////////////////////////////////////////////
        /// \fn bool loadTexture(const char *path, SDL_Renderer * const renderTarget, int w, int h)
        /// \brief Load the texture from a path.
        /// \param const char *path - path to the texture.
        /// \param SDL_Renderer * const renderTarget - pointer to the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////
        bool loadTexture(const char *path, SDL_Renderer * const renderTarget);

        /////////////////////////////////////////////////////////////////////////////////////////////
        /// \fn bool loadTexture(SDL_Texture * const texture)
        /// \brief Load the texture from an existing SDL_Texture.
        /// \param SDL_Texture * const texture - const pointer to an SDL_Texture.
        /////////////////////////////////////////////////////////////////////////////////////////////
        bool loadTexture(SDL_Texture * const texture);

        /////////////////////////////////////////////////////////////////////////////////////////////
        /// \fn SDL_Texture * getTexture()
        /// \brief Get the SDL_Texture from the Texture.
        /// \return SDL_Texture * - a pointer to an SDL_Texture object.
        /////////////////////////////////////////////////////////////////////////////////////////////
        SDL_Texture * getTexture(){return m_texture;};

        //////////////////////////////////////////////////////
        /// \fn int getWidth()
        /// \brief Get the width of the SDL_Texture.
        /// \return int - the width of the texture.
        //////////////////////////////////////////////////////
        int getWidth(){ return m_width; };

        //////////////////////////////////////////////////////
        /// \fn int getHeight()
        /// \brief Get the height of the SDL_Texture.
        /// \return int - the height of the texture.
        //////////////////////////////////////////////////////
        int getHeight(){ return m_height; };


    private:
        SDL_Texture* m_texture; ///< Pointer to the SDL_Texture data.
        int m_width; ///< The width of the Texture in pixels.
        int m_height; ///< The height of the Texture in pixels.
};

} //end namespace pk

#endif // TEXTURE_HPP
