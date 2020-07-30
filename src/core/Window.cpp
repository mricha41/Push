#include "core/Window.hpp"

#include "GL/glew.h"

using namespace pk;

Window::Window(const char *windowTitle, glm::ivec2 position, int width, int height, Uint32 windowFlags)
:
    m_title(windowTitle),
    m_position(position),
    m_width(width),
    m_height(height),
    m_flags(windowFlags),
    m_rect({0, 0, width, height}),
    m_clearColor(glm::vec4(0,0,0,1))
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL_Init failed! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        //OpenGL init
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetSwapInterval(1); // Enable vsync

        m_window = SDL_CreateWindow(windowTitle, m_position.x, m_position.y, m_width, m_height, m_flags);

        if(m_window == NULL)
        {
            printf("SDL_CreateWindow failed! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

            if(m_renderer == NULL)
            {
                printf("SDL_CreateRenderer failed! SDL_Error: %s\n", SDL_GetError());
            }
            else
            {
                SDL_DisplayMode current;
                SDL_GetCurrentDisplayMode(0, &current);
                m_context = SDL_GL_CreateContext(m_window);

                glewExperimental = GL_TRUE;
                GLenum err = glewInit();
                if(err != GLEW_OK)
                {
                    printf("Could not initialize glew: %s", glewGetErrorString(err));
                }

                SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
                SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
                SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

                //initialize IMG
                int imgFlags = IMG_INIT_PNG;
                int imgInitted = IMG_Init(imgFlags);
                if((imgInitted&imgFlags) != imgFlags)
                {
                    printf( "IMG_Init failed!\n IMG Error: %s\n", IMG_GetError() );
                }

                //initialize TTF
                if(TTF_Init() == -1)
                    printf("TTF_Init failed!\n TTF Error: %s\n", TTF_GetError());

                //initialize SDL_mixer
                int mixerFlags=MIX_INIT_OGG|MIX_INIT_MP3;
                int mixerInitted=Mix_Init(mixerFlags);
                if((mixerInitted&mixerFlags) != mixerFlags) {
                    printf("Mix_Init: Failed to init required ogg and mp3 support!\n");
                    printf("Mix_Init: %s\n", Mix_GetError());
                }
                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
                    printf("Mix_OpenAudio: %s\n", Mix_GetError());
                }

                //initialize game controllers
                SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
            }
        }
    }
}

Window::~Window()
{
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);

    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO);

    Mix_CloseAudio();

    //shut down SDL...
    while(Mix_Init(0))
        Mix_Quit();

    TTF_Quit();

    IMG_Quit();
    SDL_Quit();
}

void Window::draw(Drawable& drawable)
{
    drawable.draw(m_renderer, &m_rect);
}

void Window::draw(Drawable * drawables)
{
    //probably naive...but for now meh
    size_t limit = sizeof(drawables)/sizeof(drawables[0]);
    for(size_t i = 0; i<limit; ++i)
        drawables[i].draw(m_renderer, &m_rect);
}

void Window::draw(GLDrawable &drawable, GLStates &states)
{
    drawable.draw(states);
}

void Window::clear(glm::ivec4 color)
{
    m_clearColor = color;
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_renderer);
}

void Window::render()
{
    SDL_RenderPresent(m_renderer);
}
