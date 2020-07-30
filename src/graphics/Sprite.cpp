#include "graphics/Sprite.hpp"
#include "core/Game.hpp"

using namespace pk;

Sprite::Sprite()
:
    Drawable(),
    m_data(spriteData())
{

}

Sprite::Sprite(Texture * const texture)
:
    Drawable()
{
    m_data = spriteData();
    m_data.d_texture = texture;
    m_data.d_width = texture->getWidth();
    m_data.d_height = texture->getHeight();
    Window* win = Game::getInstance().getWindow();
    m_data.d_transform.setPosition({((win->getWindowRect().w - m_data.d_width) / 2), ((win->getWindowRect().h - m_data.d_height) / 2)});

    //copy into SDL_Rect
    //for conversion to ints at render time
    m_data.d_boundsRect = {m_data.d_transform.getPosition().x, m_data.d_transform.getPosition().y, m_data.d_width, m_data.d_height};

    //set default center on the Text
    glm::vec2 c = {m_data.d_width/2, m_data.d_height/2};
    m_data.d_transform.setCenter(c);
}

Sprite::Sprite(Texture * const texture, const SDL_Rect &rect)
:
    Drawable()
{
    m_data = spriteData();
    m_data.d_texture = texture;
    m_data.d_boundsRect = rect;
    m_data.d_width = rect.w;
    m_data.d_height = rect.h;
    m_data.d_transform.setPosition({rect.x, rect.y});

    //set default center on the Text
    glm::vec2 c = {m_data.d_width/2, m_data.d_height/2};
    m_data.d_transform.setCenter(c);
}

Sprite::~Sprite()
{

}

void Sprite::updateSprite()
{

}

void Sprite::draw(SDL_Renderer * const renderTarget, SDL_Rect * const renderTargetRect)
{
    SDL_RenderCopyEx(renderTarget, m_data.d_texture->getTexture(), renderTargetRect, &getBoundsRect(), (double)m_data.d_transform.getAngle(), &getCenter(), m_data.d_flip);
}
