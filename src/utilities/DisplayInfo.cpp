#include "utilities/DisplayInfo.hpp"

using namespace pk::utilities;

DisplayInfo::DisplayInfo()
{
    m_numberOfDisplays = SDL_GetNumVideoDisplays();
    std::vector<SDL_DisplayMode> modeContainer;
    SDL_DisplayMode mode;
    Uint32 f;

    for(int i = 0; i<m_numberOfDisplays; ++i)
    {
        int modes = SDL_GetNumDisplayModes(i);

        if (modes < 1)
        {
            SDL_Log("SDL_GetNumDisplayModes failed: %s", SDL_GetError());
        }

        else
        {
            m_numberOfDisplayModes.push_back(SDL_GetNumDisplayModes(i));

            for (int j = 0; j < modes; ++j)
            {
                if (SDL_GetDisplayMode(i, j, &mode) != 0)
                {
                    SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
                }

                f = mode.format;

                SDL_GetDisplayMode(i, j, &mode);
                modeContainer.push_back(mode);
            }
        }
        m_displayModes.push_back(modeContainer);
    }
}

DisplayInfo::~DisplayInfo()
{

}

void DisplayInfo::printDisplayModes()
{
    printf("---------------------------------------------------------------------------\n");
    printf("---------------------------------------------------------------------------\n");
    SDL_Log("SDL_GetNumVideoDisplays(): %i", m_numberOfDisplays);
    printf("---------------------------------------------------------------------------\n");
    printf("---------------------------------------------------------------------------\n");
    int i = 0;
    int d = 0;
    for(auto &j : m_displayModes)
    {
        printf("###########################################################################\n");
        printf("###########################################################################\n");
        SDL_Log("Screen #%i - SDL_GetNumDisplayModes: %i", d, SDL_GetNumDisplayModes(d));
        printf("---------------------------------------------------------------------------\n");
        for(auto &m : j)
        {
            SDL_Log("Mode %i\tbpp %i\t%s\t%i x %i refresh %i", i, SDL_BITSPERPIXEL(m.format), SDL_GetPixelFormatName(m.format), m.w, m.h, m.refresh_rate);
            ++i;
        }
        printf("###########################################################################\n");
        printf("###########################################################################\n");
        ++d;
    }
}
