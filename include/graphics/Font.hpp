#ifndef FONT_HPP
#define FONT_HPP

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace pk
{

///////////////////////////////////////////////////////////////
/// \class Font
/// \brief A class implemented using the Facade pattern
/// used for loading SDL TTF_Font data.
//////////////////////////////////////////////////////////////
class Font
{
    public:

        ///////////////////////////////
        /// \fn Font()
        /// \brief Default constructor.
        ///////////////////////////////
        Font();
        virtual ~Font();

        /////////////////////////////////////////////////
        /// \fn loadFont(const char *file, int fontSize)
        /// \brief Load a font from a file.
        /// \param const char *file - a character constant path to a file
        /// \param int fontSize - the size of the font in points.
        /// \return bool - true on success, false on failure.
        /////////////////////////////////////////////////
        bool loadFont(char *file, int fontSize);

        ///////////////////////////////////////////////////
        /// \fn void setFont(TTF_Font *font)
        /// \brief Set the internal TTF_Font for the Font.
        /// \param TTF_Font *font - a pointer to a TTF_Font.
        ///////////////////////////////////////////////////
        void setFont(TTF_Font *font){ m_font = font; };

        /////////////////////////////////////////////////
        /// \fn TTF_Font * getFont()
        /// \brief Get a pointer to the TTF_Font data.
        /// \return TTF_Font * - pointer to TTF_Font data.
        /////////////////////////////////////////////////
        TTF_Font * getFont(){ return m_font; };

        /////////////////////////////////////
        /// \enum hinting
        /// \brief From SDL_ttf docs:
        /// Hinting Font hinting is the use of mathematical instructions
        /// to adjust the display of an outline font so that it lines up
        /// with a rasterized grid. At small screen sizes, with or without
        /// antialiasing, hinting is critical for producing a clear,
        /// legible text for human readers.
        /////////////////////////////////////
        enum hinting
        {
            h_normal = TTF_HINTING_NORMAL,
            h_light = TTF_HINTING_LIGHT,
            h_mono = TTF_HINTING_MONO,
            h_none = TTF_HINTING_NONE
        };

        /////////////////////////////////////
        /// \enum style
        /// \brief Set the style of the font.
        /////////////////////////////////////
        enum style
        {
            normal = TTF_STYLE_NORMAL,
            bold = TTF_STYLE_BOLD,
            italic = TTF_STYLE_ITALIC,
            underline = TTF_STYLE_UNDERLINE,
            strikethrough = TTF_STYLE_STRIKETHROUGH
        };

        ///////////////////////////////////////////////////
        /// \fn void setHinting(Uint32 hinting)
        /// \brief Set the hinting of the font (use Font::hinting enum to set valid values).
        /// \param Uint32 hinting - a 32 bit unsigned integer mapped to Font::hinting.
        ///////////////////////////////////////////////////
        void setHinting(Uint32 hinting){ m_hinting = hinting; TTF_SetFontHinting(m_font, m_hinting); };

        ///////////////////////////////////////////////////
        /// \fn const Uint32 &getHinting()
        /// \brief Get the current hinting of the font.
        /// \return Uint32 - a 32 bit unsigned integer corresponding to an integer mapped to Font::hinting.
        ///////////////////////////////////////////////////
        const Uint32 &getHinting(){ return m_hinting; };

        ///////////////////////////////////////////////////
        /// \fn void setKerning(int allowed)
        /// \brief Turn on/off font kerning (on by default).
        ///////////////////////////////////////////////////
        void setKerning(int allowed){ m_kerning = allowed; TTF_SetFontKerning(m_font, m_kerning); };

        ///////////////////////////////////////////////////
        /// \fn void getOutline()
        /// \brief Get the outline for the font (in pixels).
        /// \param int - a plain integer value for number of pixels for the outline.
        ///////////////////////////////////////////////////
        int getOutline(){ return m_outline; };

        ///////////////////////////////////////////////////
        /// \fn void setOutline(int outline)
        /// \brief Set the outline for the font (in pixels).
        /// \param int outline - a plain integer value for number of pixels to outline by.
        ///////////////////////////////////////////////////
        void setOutline(int outline){ m_outline = outline; TTF_SetFontOutline(m_font, m_outline); };

        ///////////////////////////////////////////////////
        /// \fn void setFontStyle(int style)
        /// \brief Set the style for the font. Use Font::style enum flags to combine styles.
        /// \param int style - a plain integer used as flag variable for font style.
        ///////////////////////////////////////////////////
        void setFontStyle(int style){ m_style = style; TTF_SetFontStyle(m_font, style); };

        ///////////////////////////////////////////////////
        /// \fn const int &getStyle()
        /// \brief Get the current style of the font.
        /// \return int - a plain integer corresponding to Font::style enum value(s).
        ///////////////////////////////////////////////////
        const int &getStyle(){ return m_style; };

        ///////////////////////////////////////////////////
        /// \fn void setFontSize(int s)
        /// \brief Set the size for the font (in pixels).
        /// \param int s - a plain integer value for font size (in pixels).
        ///////////////////////////////////////////////////
        void setFontSize(int s);

    private:
        TTF_Font* m_font; ///< Pointer to TTF_Font data - memory managed outside class.
        char * m_path; ///< The path to the Font file.
        Uint32 m_hinting; ///< Hinting for the font.
        int m_kerning; ///< Kerning for the font (set to 1, or on, by default.
        int m_outline; ///< Font outline (set to 0, or off, by default).
        int m_style; ///< Font style (defaults to style::normal).

};

} //end namespace pk

#endif // FONT_HPP
