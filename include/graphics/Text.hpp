#ifndef TEXT_HPP
#define TEXT_HPP

#include "graphics/Texture.hpp"
#include "graphics/Font.hpp"
#include "graphics/Drawable.hpp"
#include "graphics/Transform.hpp"

namespace pk
{

////////////////////////////////////////////////////////
/// \struct textData
/// \brief Data necessary for representing the Text.
////////////////////////////////////////////////////////
struct textData
{
    Font* d_font; ///< Pointer to a Font object (memory NOT managed in this class!).
    Texture* d_texture; ///< Pointer to a Texture object (memory NOT managed in this class!).
    SDL_Rect d_boundsRect; ///< SDL_Rect setting the bounding rectangle for the Text object.
    const char* d_text; ///< The character string to render to the texture.
    SDL_Color d_color; ///< The color set to the font of the Text string (default is white).
    Uint32 d_renderMode; ///< The rendering mode used to render the Text (default is renderMode::blendedWrapped).
    SDL_Point d_center; ///< An SDL_Point used to set the center of the Text object.
    SDL_RendererFlip d_flip; ///< An SDL_RendererFlip value setting how to flip the Text (default is SDL_FLIP_NONE).
    SDL_Color d_backgroundColor; ///< The color of the background (bounding box) of the Text.
    Transform d_transform; ///< The raw transform data for the Text object.
    int d_width; ///< The width of the Text object.
    int d_height; ///< The height of the Text object.
};

///////////////////////////////////////////////////////////////
/// \class Text
/// \brief Drawable text using a Texture as its drawable resource.
/// Part of the Decorator pattern along with the Drawable class.
///////////////////////////////////////////////////////////////
class Text : public Drawable
{
    private:
        //inaccessible - use another constructor!
        /////////////////////////////////////////
        /// \fn Text()
        /// \brief Inaccessible - Text needs a Font at a minimum.
        /////////////////////////////////////////
        Text(){};

        /////////////////////////////////////////
        /// \fn updateTexture()
        /// \brief Used internally when the render mode is
        /// initialized or changed. Never call this
        /// in a loop unless you want memory leaks!!!
        /// This function calls SDL_CreateTextureFromSurface(...)
        /// which will keep allocating memory on each call.
        /////////////////////////////////////////
        void updateTexture();
    public:

        //////////////////////////////////////////////////////////
        /// \fn Text(Font* font)
        /// \brief Construct a Text from a Font.
        /// \param Font* font - a pointer to a Font object already loaded.
        /// \param const char * text - a C-style string.
        //////////////////////////////////////////////////////////
        Text(Font * const font, const char * text);

        //////////////////////////////////////////////////////////
        /// \fn Text(const Texture &texture)
        /// \brief Construct a Text from a Font and a Texture.
        /// \param Font* font - a pointer to a Font object already loaded.
        /// \param Texture * const texture - the texture for the Text.
        /// \param const char * text - a C-style string.
        //////////////////////////////////////////////////////////
        Text(Font * const font, Texture * const texture, const char * text);

        //////////////////////////////////////////////////////////
        /// \fn Text(const Texture &texture, const SDL_Rect &rect)
        /// \brief Construct a Text from a Font, a Texture, and a rect.
        /// \param Font* font - a pointer to a Font object already loaded.
        /// \param Texture * const texture - the texture for the Sprite.
        /// \param const SDL_Rect &rect - the rect used to draw the Sprite texture.
        /// \param const char * text - a C-style string.
        //////////////////////////////////////////////////////////
        Text(Font * const font, Texture * const texture, const SDL_Rect &rect, const char * text);

        //////////////////////////////////////////////////////////
        /// \fn Text(textData td)
        /// \brief Construct a Text from a textData struct.
        /// \param textData td - a struct with key data components of a Text.
        //////////////////////////////////////////////////////////
        Text(textData td);

        virtual ~Text();

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setTextData(textData &t)
        /// \brief Set the data for the Text object.
        /// \param textData &t - a textData struct to set for the Text object.
        /////////////////////////////////////////////////////////////////////////////
        void setTextData(textData &t){ m_data = t; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn textData &getTextData()
        /// \brief Get the current text data for the Text object.
        /// \return textData & - text data for the Text object.
        /////////////////////////////////////////////////////////////////////////////
        textData &getTextData(){ return m_data; };

        //////////////////////////////////////////
        /// \fn void setFont(Font * const font)
        /// \brief Set the Font for the Text object.
        /// \param Font * const font - a const pointer to a Font.
        //////////////////////////////////////////
        void setFont(Font * const font){ m_data.d_font = font; updateTexture(); };

        //////////////////////////////////////////
        /// \fn const Font * getFont()
        /// \brief Get the Font from the Text object.
        /// \return const Font * - a const pointer to a Font object.
        //////////////////////////////////////////
        Font * getFont(){ return m_data.d_font; };

        //////////////////////////////////////////
        /// \fn void setTexture(Texture * const texture)
        /// \brief Set the Texture for the Text object.
        /// \param Texture * const texture - a const pointer to a Texture.
        //////////////////////////////////////////
        void setTexture(Texture * const texture){ m_data.d_texture = texture; updateTexture(); };

        //////////////////////////////////////////
        /// \fn const Texture * getTexture()
        /// \brief Get the Texture from the Text object.
        /// \return const Texture * - a const pointer to a Texture object.
        //////////////////////////////////////////
        Texture * getTexture(){ return m_data.d_texture; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setBoundsRect(SDL_Rect &rect)
        /// \brief Set the bounding rectangle for the Text.
        /// \param SDL_Rect &rect - an SDL_Rect you want to set the bounding rectangle of the Text to.
        /////////////////////////////////////////////////////////////////////////////
        void setBoundsRect(SDL_Rect &rect)
        {
            m_data.d_transform.setPosition({rect.x, rect.y});
            m_data.d_width = rect.w;
            m_data.d_height = rect.h;
            m_data.d_boundsRect = {rect.x, rect.y, rect.w, rect.h};
            updateTexture();
        };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn const SDL_Rect & getBoundsRect()
        /// \brief Get the current bounding rectangle of the Text.
        /// \return SDL_Point - an SDL_Rect corresponding to the bounding rectangle of the Text.
        /////////////////////////////////////////////////////////////////////////////
        const SDL_Rect & getBoundsRect()
        {
            m_data.d_boundsRect = {m_data.d_transform.getPosition().x, m_data.d_transform.getPosition().y, m_data.d_width, m_data.d_height};
            return m_data.d_boundsRect;
        };


        void setPosition(glm::vec2 pos){ m_data.d_transform.setPosition(pos); };


        glm::vec2 getPosition(){ return m_data.d_transform.getPosition(); };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setString(const char * str)
        /// \brief Set the string for the Text object.
        /// \param const char * str - a C-style string.
        /////////////////////////////////////////////////////////////////////////////
        void setString(const char * str){ m_data.d_text = str; updateTexture(); };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn const char * getString()
        /// \brief Get the string for the Text object.
        /// \return const char * - a C-style string.
        /////////////////////////////////////////////////////////////////////////////
        const char * getString(){ return m_data.d_text; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setColor(const SDL_Color &color)
        /// \brief Set the color of the Font for the Text object.
        /// \param const SDL_Color &color - a const reference to an SDL_Color.
        /////////////////////////////////////////////////////////////////////////////
        void setColor(const SDL_Color &color);

        /////////////////////////////////////////////////////////////////////////////
        /// \fn SDL_Color &getColor()
        /// \brief Get the color of the Font for the Text object (default is white).
        /// \return SDL_Color & - a reference to an SDL_Color.
        /////////////////////////////////////////////////////////////////////////////
        SDL_Color &getColor(){ return m_data.d_color; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setBackgroundColor(SDL_Color c)
        /// \brief Set the color of the Text bounding box (background).
        /// \param SDL_Color c - an SDL_Color struct corresponding to the background color of the Text.
        /////////////////////////////////////////////////////////////////////////////
        void setBackgroundColor(SDL_Color c){ m_data.d_backgroundColor = c; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn const SDL_Color &getBackgroundColor()
        /// \brief Get the SDL_Color corresponding to the Text background color (bounding box).
        /// \return SDL_Color - an SDL_Color struct corresponding to the Text background color.
        /////////////////////////////////////////////////////////////////////////////
        const SDL_Color &getBackgroundColor(){ return m_data.d_backgroundColor; };

        //////////////////////////////////////////////////////////////////
        /// \enum renderMode
        /// \brief Render mode used by SDL internally to draw the Text.
        //////////////////////////////////////////////////////////////////
        enum renderMode
        {
            solid,
            shaded,
            blended,
            blendedWrapped
        };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setRenderMode(Uint32 mode)
        /// \brief Set the mode for rendering the Text (renderMode::solid, renderMode::shaded, or renderMode::blended).
        /// \param Uint32 mode - a plain integer corresponding to a renderMode:: enum value.
        /////////////////////////////////////////////////////////////////////////////
        void setRenderMode(Uint32 mode, Uint32 length = 0){ m_data.d_renderMode = mode; m_wrapLength = length; updateTexture(); };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn Uint32 getRenderMode()
        /// \brief Get the current render mode for the Text (default is renderMode::solid).
        /// \return Uint32 - a plain integer corresponding to a renderMode:: enum value.
        /////////////////////////////////////////////////////////////////////////////
        Uint32 getRenderMode(){ return m_data.d_renderMode;};

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setCenter(SDL_Point point)
        /// \brief Set the center point for the Text.
        /// \param SDL_Point &point - an SDL_Point you want to set the center point of the Text to.
        /////////////////////////////////////////////////////////////////////////////
        void setCenter(SDL_Point &point){ m_data.d_center = point; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn SDL_Point getCenter()
        /// \brief Get the current center point of the Text.
        /// \return SDL_Point - an SDL_Point corresponding to the current center point of the Text.
        /////////////////////////////////////////////////////////////////////////////
        const SDL_Point &getCenter()
        {
            m_data.d_center = {(int)m_data.d_transform.getCenter().x, (int)m_data.d_transform.getCenter().y};
            return m_data.d_center;
        };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn void setFlip(SDL_RendererFlip &type)
        /// \brief Set the flip type for the Text (SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL).
        /// \param SDL_RendererFlip type - an integer corresponding to an SDL_RendererFlip constant.
        /////////////////////////////////////////////////////////////////////////////
        void setFlip(SDL_RendererFlip &type){ m_data.d_flip = type; };

        /////////////////////////////////////////////////////////////////////////////
        /// \fn const SDL_RendererFlip & getFlip()
        /// \brief Get the current flip type for the Text (default is SDL_FLIP_NONE).
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
        textData m_data; ///< Data important to the construction and state maintenance of a Text.
        Uint32 m_wrapLength; ///< If text is rendered in blended and wrapped mode, the width at which lines wrap is required.
};

} //end namespace pk

#endif // TEXT_HPP
