#include "states/MenuScreen.hpp"

#include <windows.h>

#include <stdio.h>

#include "core/GameController.hpp"

MenuScreen::MenuScreen()
:
    ScreenState(),
    m_texture(),
    m_sprite(),
    m_font(),
    m_textTexture(),
    m_screenTitle(nullptr, nullptr, {0,0,0,0}, "PUSH!!!"),
    m_music(nullptr),
    m_selectSound(nullptr),
    m_selectedSound(nullptr)
{
    m_running = false;

    setState(menuState::s_uninitialized);
}

MenuScreen::~MenuScreen()
{
    if(m_font.getFont() != nullptr)
        TTF_CloseFont(m_font.getFont());

    Mix_FreeChunk(m_selectSound);
    m_selectSound = nullptr;

    Mix_FreeChunk(m_selectedSound);
    m_selectedSound = nullptr;

    Mix_HaltMusic();
    Mix_FreeMusic(m_music);

    m_music = nullptr;
}

void MenuScreen::display()
{
    setState(menuState::s_running);
    m_running = true;

    SDL_Event e;

    pk::Window* pkWin = pk::Game::getWindow();
    SDL_Window* win = pk::Game::getWindow()->getWindow();
    SDL_GLContext* context = &pk::Game::getWindow()->getContext();

    SDL_GL_MakeCurrent(win, *context);

    if(!m_texture.loadTexture("images/menus/menu.png", pk::Game::getWindow()->getRenderer()))
        printf("Could not load texture!");

    SDL_Rect sprRect;
    sprRect.x = 0;
    sprRect.y = 0;
    sprRect.w = m_texture.getWidth()*pk::Game::getScalingFactor().x;
    sprRect.h = m_texture.getHeight()*pk::Game::getScalingFactor().y;
    m_sprite = pk::Sprite(&m_texture, sprRect);

    m_font = pk::Font();

    if(!m_font.loadFont("fonts/Sansation_Regular.ttf", (int)116*pk::Game::getScalingFactor().x))
    {
        printf("Could not load the font! Error:%s\n", SDL_GetError());
    }

    m_music = Mix_LoadMUS("sound/tracks/title_theme.mp3");
    if(!m_music)
    {
        printf("Mix_LoadMUS(\"title_theme.mp3\"): %s\n", Mix_GetError());
    }

    Mix_VolumeMusic(pk::Game::getMusicVolume());

    Mix_PlayMusic(m_music, -1);

    m_selectSound = Mix_LoadWAV("sound/select.wav");
    Mix_VolumeChunk(m_selectSound, pk::Game::getSoundEffectVolume());

    m_selectedSound = Mix_LoadWAV("sound/selection.wav");
    Mix_VolumeChunk(m_selectedSound, pk::Game::getSoundEffectVolume());

    m_screenTitle = pk::Text(&m_font, &m_textTexture, {0,0,0,0}, "PUSH!!!");

    m_screenTitle.setRenderMode(pk::Text::renderMode::blendedWrapped, pk::Game::getInstance().getWindow()->getWindowRect().w/2);
    m_screenTitle.setPosition(glm::vec2(pk::Game::getInstance().getWindow()->getWindowRect().w/2 - m_screenTitle.getBoundsRect().w/2,20.f));

    //a method for getting an outline
    //with a different color than the inside
    //of the text. Just need to alter properties
    //of the Font and then give it a separate
    //Texture.
    pk::Text screenTitle2 = pk::Text(&m_font, &m_textTextureOutline, {0,0,0,0}, "PUSH!!!");
    m_font.setOutline((int)4*pk::Game::getScalingFactor().x);
    screenTitle2.setColor({155,78,0,255});

    screenTitle2.setRenderMode(pk::Text::renderMode::blendedWrapped, pk::Game::getInstance().getWindow()->getWindowRect().w/2);
    screenTitle2.getTextData().d_transform.setPosition(glm::vec2(pk::Game::getInstance().getWindow()->getWindowRect().w/2 - screenTitle2.getBoundsRect().w/2 - 4.f,16.f));

    //set up text options and
    //housekeeping variables
    m_font.setOutline(0);
    m_font.setFontSize((int)84*pk::Game::getScalingFactor().x);

    pk::Texture playTex;
    pk::Text play = pk::Text(&m_font, &playTex, {0,0,0,0}, "PLAY");
    play.setColor({255, 255, 0, 255});
    play.setPosition({10.f*pk::Game::getScalingFactor().x, 225.f*pk::Game::getScalingFactor().y});
    pk::Texture optionsTex;
    pk::Text options = pk::Text(&m_font, &optionsTex, {0,0,0,0}, "OPTIONS");
    options.setPosition({10.f*pk::Game::getScalingFactor().x, 350.f*pk::Game::getScalingFactor().y});
    pk::Texture creditsTex;
    pk::Text credits = pk::Text(&m_font, &creditsTex, {0,0,0,0}, "CREDITS");
    credits.setPosition({10.f*pk::Game::getScalingFactor().x, 475.f*pk::Game::getScalingFactor().y});

    pk::GameController controller1 = pk::GameController(0);

    bool pressedUp = false;
    bool pressedDown = false;
    double pressDelay = 50;
    double pressTime = 0;
    int pressCounter = 0;
    bool ready = false;
    unsigned int selection = 0;

    while(isRunning())
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                setState(menuState::s_exit);
                return;
            }

            if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.scancode)
                {
                default:
                break;
                }
            }

            if(e.type == SDL_KEYUP)
            {
                switch(e.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                {
                    setState(menuState::s_exit);
                    return;
                }
                break;
                default:
                break;
                }
            }
        }

        //update selection visual
        switch(selection)
        {
            case 0:
            {
                play.setColor({255, 255, 0, 255});
                options.setColor({255, 255, 255, 255});
                credits.setColor({255, 255, 255, 255});
            }
            break;
            case 1:
            {
                play.setColor({255, 255, 255, 255});
                options.setColor({255, 255, 0, 255});
                credits.setColor({255, 255, 255, 255});
            }
            break;
            case 2:
            {
                play.setColor({255, 255, 255, 255});
                options.setColor({255, 255, 255, 255});
                credits.setColor({255, 255, 0, 255});
            }
            break;
            default:
                break;
        }

        if(controller1.getAxisState(pk::GameControllerAxis::LEFT_Y) > 8000
           || controller1.getButtonState(pk::GameControllerButton::DPAD_DOWN) == 1)
        {
            pressTime = SDL_GetTicks();
            pressedDown = true;
        }
        if(controller1.getAxisState(pk::GameControllerAxis::LEFT_Y) < 8000
           && controller1.getButtonState(pk::GameControllerButton::DPAD_DOWN) == 0)
        {
            pressedDown = false;
            pressCounter++;
        }

        if(controller1.getAxisState(pk::GameControllerAxis::LEFT_Y) < -8000
           || controller1.getButtonState(pk::GameControllerButton::DPAD_UP) == 1)
        {
            pressTime = SDL_GetTicks();
            pressedUp = true;
        }
        if(controller1.getAxisState(pk::GameControllerAxis::LEFT_Y) > -8000
           && controller1.getButtonState(pk::GameControllerButton::DPAD_UP) == 0)
        {
            pressedUp = false;
            pressCounter++;
        }

        if(controller1.getButtonState(pk::GameControllerButton::A)
           || controller1.getButtonState(pk::GameControllerButton::START))
        {
            Mix_PlayChannel(-1, m_selectedSound, 0);
            ready = true;
        }

        if(controller1.getButtonState(pk::GameControllerButton::B))
        {
            setState(menuState::s_exit);
            return;
        }

        if(pressedDown && pressCounter == 1)
        {
            if(selection < 2)
                selection++;

            Mix_PlayChannel(-1, m_selectSound, 0);
        }

        if(pressedUp && pressCounter == 1)
        {
            if(selection > 0)
                selection--;

            Mix_PlayChannel(-1, m_selectSound, 0);
        }

        if(SDL_GetTicks() - pressTime > pressDelay)
            pressCounter = 0;

        if(ready)
        {
            if(selection == 0)
            {
                setState(menuState::s_play);
                if(!Mix_Playing(-1))
                    return;
            }

            else if(selection == 1)
            {
                setState(menuState::s_options);
                if(!Mix_Playing(-1))
                    return;
            }
            else if(selection == 2)
            {
                ShellExecute(NULL, "open", "https://markrichards.ninja/push#dev", NULL, NULL, SW_SHOWNORMAL);
                if(!Mix_Playing(-1))
                    return;
            }
        }

        pkWin->clear();

        pkWin->draw(m_sprite);

        pkWin->draw(screenTitle2);
        pkWin->draw(m_screenTitle);

        pkWin->draw(play);
        pkWin->draw(options);
        pkWin->draw(credits);

        pkWin->render();
    }
}
