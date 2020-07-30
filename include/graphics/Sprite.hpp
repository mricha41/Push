#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "graphics/Drawable.hpp"
#include "graphics/Texture.hpp"
#include "graphics/Transform.hpp"

namespace pk
{

////////////////////////////////////////////////////////
/// \struct spriteData
/// \brief Data necessary for representing the Sprite.
////////////////////////////////////////////////////////
struct spriteData
{
    Texture* d_texture; ///< Pointer to a Texture object (memory NOT managed in this class!).
    SDL_Rect d_boundsRect; ///< SDL_Rect setting the bounding rectangle for the Sprite object.
    SDL_Point d_center; ///< An SDL_Point used to set the center of the Text object.
    SDL_RendererFlip d_flip; ///< An SDL_RendererFlip value setting how to flip the Text (default is SDL_FLIP_NONE).
    SDL_Color d_backgroundColor; ///< The color of the background (bounding box) of the Text.
    Transform d_transform; ///< The raw transform data for the Text object.
    int d_width; ///< The width of the Text object.
    int d_height; ///< The height of the Text object.
};

///////////////////////////////////////////////////////////////
/// \class Sprite
/// \brief Drawable sprite using a Texture as its drawable resource.
/// Part of the Decorator pattern along with the Drawable class.
///////////////////////////////////////////////////////////////
class Sprite : public Drawable
{
    private:
        /////////////////////////////////////////
        /// \fn updateSprite()
        /// \brief Used internally when the render mode is
        /// initialized or changed.
        /////////////////////////////////////////
        void updateSprite();

    public:
        //////////////////////////////////////////////////////////
        /// \fn Sprite()
        /// \brief Default constructor.
        //////////////////////////////////////////////////////////
        Sprite();

        //////////////////////////////////////////////////////////
        /// \fn Sprite(const Texture &texture)
        /// \brief Construct a Sprite from a texture.
        /// \param Texture * const texture - the texture for the Sprite.
        //////////////////////////////////////////////////////////
        Sprite(Texture * const texture);

        //////////////////////////////////////////////////////////
        /// \fn Sprite(const Texture &texture, const SDL_Rect &rect)
        /// \brief Construct a Sprite from a texture.
        /// \param Texture * const texture - the texture for the Sprite.
        /// \param const SDL_Rect &rect - the rect used to draw the Sprite texture.
        //////////////////////////////////////////////////////////
        Sprite(Texture * const texture, const SDL_Rect &rect);

        virtual ~Sprite();

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setSpriteData(spriteData &s)
        /// \brief Set the data for the Sprite object.
        /// \param spriteData &s - a spriteData struct to set for the Sprite object.
        /////////////////////////////////////////////////////////////////////////////
        void setSpriteData(spriteData &s){ m_data = s; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn spriteData &getSpriteData()
        /// \brief Get the current spriteData for the Sprite object.
        /// \return spriteData & - sprite data for the Sprite object.
        /////////////////////////////////////////////////////////////////////////////
        spriteData &getSpriteData(){ return m_data; };

        //////////////////////////////////////////////////////////
        /// \fn setTexture(Texture * const texture)
        /// \brief Set the Sprite texture.
        /// \param Texture * const texture - the texture for the Sprite.
        //////////////////////////////////////////////////////////
        void setTexture(Texture * const texture){ m_data.d_texture = texture; };

        //////////////////////////////////////////////////////////
        /// \fn Texture * const getTexture()
        /// \brief Get the Sprite texture.
        //////////////////////////////////////////////////////////
        Texture * const getTexture(){ return m_data.d_texture; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setBoundsRect(SDL_Rect &rect)
        /// \brief Set the bounding rectangle for the Sprite.
        /// \param SDL_Rect &rect - an SDL_Rect you want to set the bounding rectangle of the Sprite to.
        /////////////////////////////////////////////////////////////////////////////
        void setBoundsRect(SDL_Rect &rect)
        {
            m_data.d_transform.setPosition({rect.x, rect.y});
            m_data.d_width = rect.w;
            m_data.d_height = rect.h;
            m_data.d_boundsRect = {rect.x, rect.y, rect.w, rect.h};
            updateSprite();
        };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn const SDL_Rect & getBoundsRect()
        /// \brief Get the current bounding rectangle of the Sprite.
        /// \return SDL_Point - an SDL_Rect corresponding to the bounding rectangle of the Sprite.
        /////////////////////////////////////////////////////////////////////////////
        const SDL_Rect & getBoundsRect()
        {
            m_data.d_boundsRect = {m_data.d_transform.getPosition().x, m_data.d_transform.getPosition().y, m_data.d_width, m_data.d_height};
            return m_data.d_boundsRect;
        };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn SDL_Point getCenter()
        /// \brief Get the current center point of the Sprite.
        /// \return SDL_Point - an SDL_Point corresponding to the current center point of the Sprite.
        /////////////////////////////////////////////////////////////////////////////
        const SDL_Point &getCenter()
        {
            m_data.d_center = {(int)m_data.d_transform.getCenter().x, (int)m_data.d_transform.getCenter().y};
            return m_data.d_center;
        };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setFlip(SDL_RendererFlip &type)
        /// \brief Set the flip type for the Sprite (SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL).
        /// \param SDL_RendererFlip type - an integer corresponding to an SDL_RendererFlip constant.
        /////////////////////////////////////////////////////////////////////////////
        void setFlip(SDL_RendererFlip &type){ m_data.d_flip = type; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn const SDL_RendererFlip & getFlip()
        /// \brief Get the current flip type for the Sprite (default is SDL_FLIP_NONE).
        /// \return SDL_RendererFlip & - a const reference to an SDL_RendererFlip constant (SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL).
        /////////////////////////////////////////////////////////////////////////////
        const SDL_RendererFlip & getFlip(){ return m_data.d_flip; };

        ////////////////////////////////////////////////////////////////////////////////////////////
        /// \fn void draw(SDL_Renderer * const renderTarget, SDL_Rect * const renderTargetRect)
        /// \brief Draw the Sprite to a render target.
        /// \param SDL_Renderer * const renderTarget - the renderer to draw with.
        /// \param SDL_Rect * const renderTargetRect - the area of the render target to draw to.
        ////////////////////////////////////////////////////////////////////////////////////////////
        void draw(SDL_Renderer * const renderTarget, SDL_Rect * const renderTargetRect) override;

    private:
        spriteData m_data; ///< Data important to the construction and state maintenance of a Sprite.
};

} //end namespace pk

#endif // SPRITE_HPP
