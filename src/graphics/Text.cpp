#include "graphics/Text.hpp"
#include "core/Game.hpp"

using namespace pk;

Text::Text(Font * const font, const char * text)
:
    Drawable()
{
    m_data.d_font = font;
    m_data.d_texture = nullptr;
    m_data.d_boundsRect = {0,0,0,0};
    m_data.d_text = text;
    m_data.d_color = {0xff, 0xff, 0xff, 0xff};
    m_data.d_renderMode= renderMode::solid;
    m_data.d_center = SDL_Point();
    m_data.d_flip = SDL_FLIP_NONE;
    m_data.d_transform = Transform();

    updateTexture();
}

Text::Text(Font * const font, Texture * const texture, const char * text)
:
    Drawable()
{
    m_data.d_font = font;
    m_data.d_texture = texture;
    m_data.d_boundsRect = {0,0,0,0};
    m_data.d_text = text;
    m_data.d_color = {0xff, 0xff, 0xff, 0xff};
    m_data.d_renderMode= renderMode::solid;
    m_data.d_center = SDL_Point();
    m_data.d_flip = SDL_FLIP_NONE;
    m_data.d_transform = Transform();

    updateTexture();
}

Text::Text(Font * const font, Texture * const texture, const SDL_Rect &rect, const char * text)
:
    Drawable()
{
    m_data.d_font = font;
    m_data.d_texture = texture;
    m_data.d_boundsRect = rect;
    m_data.d_text = text;
    m_data.d_color = {0xff, 0xff, 0xff, 0xff};
    m_data.d_renderMode= renderMode::solid;
    m_data.d_center = SDL_Point();
    m_data.d_flip = SDL_FLIP_NONE;
    m_data.d_transform = Transform();

    updateTexture();
}

Text::Text(textData td)
:
    Drawable()
{
    m_data = td;
    updateTexture();
}

Text::~Text()
{

}

void Text::setColor(const SDL_Color &color)
{
    m_data.d_color = color;
    SDL_SetTextureColorMod(m_data.d_texture->getTexture(), color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(m_data.d_texture->getTexture(), color.a);
}

//private!
void Text::updateTexture()
{
    //there's no point in updating the texture
    //if there's no texture or no font
    if(m_data.d_font == nullptr || m_data.d_texture == nullptr)
        return;

    //set up an SDL_Surface for renderer
    SDL_Surface* surf = NULL;

    switch(m_data.d_renderMode)
    {
        case renderMode::solid:
        {
            surf = TTF_RenderText_Solid(m_data.d_font->getFont(), m_data.d_text, m_data.d_color);
        }
        break;
        case renderMode::shaded:
        {
            surf = TTF_RenderText_Shaded(m_data.d_font->getFont(), m_data.d_text, m_data.d_color, m_data.d_backgroundColor);
        }
        break;
        case renderMode::blended:
        {
            surf = TTF_RenderText_Blended(m_data.d_font->getFont(), m_data.d_text, m_data.d_color);
        }
        break;
        case renderMode::blendedWrapped:
        {
            surf = TTF_RenderText_Blended_Wrapped(m_data.d_font->getFont(), m_data.d_text, m_data.d_color, m_wrapLength);
        }
        break;
    default:
        break;
    }

    if(surf == NULL)
    {
        printf( "TTF_RenderTextSolid failed! Error: %s\n", TTF_GetError());
    }
    else
    {
        //Window* win = Game::getInstance().getWindow();
        SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::getInstance().getWindow()->getRenderer(), surf);
        m_data.d_texture->loadTexture(tex);
        if(m_data.d_texture->getTexture() == NULL)
        {
            printf( "Texture creation from rendered text failed! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //set default bounds on the Text
            //centered in the window with a
            //width and height corresponding to
            //the texture width and height
            m_data.d_width = surf->w;
            m_data.d_height = surf->h;
            m_data.d_transform.setPosition({m_data.d_transform.getPosition().x, m_data.d_transform.getPosition().y});

            //copy into SDL_Rect
            //for conversion to ints at render time
            m_data.d_boundsRect = {m_data.d_transform.getPosition().x, m_data.d_transform.getPosition().y, m_data.d_width, m_data.d_height};

            //set default center on the Text
            glm::vec2 c = {m_data.d_width/2, m_data.d_height/2};
            m_data.d_transform.setCenter(c);
        }

        SDL_FreeSurface(surf);
    }
}

void Text::draw(SDL_Renderer * const renderTarget, SDL_Rect * const renderTargetRect)
{
    SDL_RenderCopyEx(renderTarget, m_data.d_texture->getTexture(), renderTargetRect, &getBoundsRect(), (double)m_data.d_transform.getAngle(), &getCenter(), m_data.d_flip);
}
