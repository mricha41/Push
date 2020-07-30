#include "graphics/Font.hpp"

using namespace pk;

Font::Font()
:
    m_font(nullptr),
    m_path(nullptr),
    m_hinting(hinting::h_normal),
    m_kerning(1), //kerning on by default...
    m_outline(0), //off by default
    m_style(style::normal)
{

}

Font::~Font()
{

}

void Font::setFontSize(int s)
{
    TTF_CloseFont(m_font);
    loadFont(m_path, s);
}

bool Font::loadFont(char *file, int fontSize)
{
    m_path = file;
    m_font = TTF_OpenFont(m_path, fontSize);
    if(m_font == nullptr)
    {
        printf("Could not load font: %s\n", TTF_GetError());
        return false;
    }
    return true;
}
