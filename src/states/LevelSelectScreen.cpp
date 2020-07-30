#include "states/LevelSelectScreen.hpp"

#include <stdio.h>

#include "core/GameController.hpp"
#include "graphics/Camera.hpp"
#include "graphics/Shader.hpp"
#include "lighting/DiffuseLight.hpp"
#include "lighting/Material.hpp"

using namespace pk;

LevelSelectScreen::LevelSelectScreen()
:
    ScreenState(),
    m_music(nullptr),
    m_selectSound(nullptr),
    m_selectedSound(nullptr),
    m_levelTexture("levels/spikes/spikes_arena_final.png"),
    m_levelSprite(m_levelTexture, {0.f, 0.f, 800.f, 608.f}),
    m_leftArrowTexture("images/menus/leftarrow.png"),
    m_rightArrowTexture("images/menus/rightarrow.png"),
    m_leftArrow(m_leftArrowTexture, {0.f, 0.f, 200.f, 608.f}),
    m_rightArrow(m_rightArrowTexture, {0.f, 0.f, 200.f, 608.f})
{
    m_running = false;

    setState(levelSelectState::s_uninitialized);

    m_selection = 0;
}

LevelSelectScreen::~LevelSelectScreen()
{
    Mix_HaltMusic();
    Mix_FreeMusic(m_music);

    m_music = nullptr;

    Mix_FreeChunk(m_selectSound);
    m_selectSound = nullptr;

    Mix_FreeChunk(m_selectedSound);
    m_selectedSound = nullptr;
}

void LevelSelectScreen::levelSelectionMade()
{
    //handle the level selection
    switch(m_selection)
    {
    case 0:
    {
        setState(levelSelectState::s_spikes);
    }
    break;
    case 1:
    {
        setState(levelSelectState::s_ice);
    }
    break;
    case 2:
    {
        setState(levelSelectState::s_desert);
    }
    break;
    case 3:
    {
        setState(levelSelectState::s_jungle);
    }
    break;
    case 4:
    {
        setState(levelSelectState::s_castle);
    }
    break;
    case 5:
    {
        setState(levelSelectState::s_fireDungeon);
    }
    break;
    case 6:
    {
        setState(levelSelectState::s_greenDungeon);
    }
    break;
    case 7:
    {
        setState(levelSelectState::s_pinkDungeon);
    }
    break;
    case 8:
    {
        setState(levelSelectState::s_purpleDungeon);
    }
    break;
    default:
        break;
    }
}

void LevelSelectScreen::display()
{
    setState(levelSelectState::s_running);
    m_running = true;

    SDL_Event e;

    pk::Window* pkWin = pk::Game::getWindow();
    SDL_Window* win = pk::Game::getWindow()->getWindow();
    SDL_GLContext* context = &pk::Game::getWindow()->getContext();

    SDL_GL_MakeCurrent(win, *context);

    m_music = Mix_LoadMUS("sound/tracks/level_and_character_select_theme.mp3");
    if(!m_music)
    {
        printf("Mix_LoadMUS(\"level_and_character_select_theme.mp3\"): %s\n", Mix_GetError());
    }

    Mix_VolumeMusic(pk::Game::getMusicVolume());

    Mix_PlayMusic(m_music, -1);

    m_selectSound = Mix_LoadWAV("sound/select2.wav");
    Mix_VolumeChunk(m_selectSound, pk::Game::getSoundEffectVolume());

    m_selectedSound = Mix_LoadWAV("sound/selection.wav");
    Mix_VolumeChunk(m_selectedSound, pk::Game::getSoundEffectVolume());

    char levels[9][80] = {
        "levels/spikes/spikes_arena_final.png",
        "levels/ice/ice_arena_final.png",
        "levels/desert/desert_arena_final.png",
        "levels/jungle/jungle_arena_final.png",
        "levels/castle/castle_arena_final.png",
        "levels/fire/fire_arena_final.png",
        "levels/green/green_arena_final.png",
        "levels/pink/pink_arena_final.png",
        "levels/purple/purple_arena_final.png"
    };

    m_levelSprite.setPosition({pk::Game::getWindow()->getSize().x/2.f, pk::Game::getWindow()->getSize().y/2.f});
    m_levelSprite.setScale(pk::Game::getScalingFactor()/2.f);

    m_leftArrow.setPosition({125.f*pk::Game::getScalingFactor().x, pk::Game::getWindow()->getSize().y/2.f});
    m_leftArrow.setScale(pk::Game::getScalingFactor()/2.f);
    m_rightArrow.setPosition({pk::Game::getWindow()->getSize().x - (125.f*pk::Game::getScalingFactor().x), pk::Game::getWindow()->getSize().y/2.f});
    m_rightArrow.setScale(pk::Game::getScalingFactor()/2.f);

    //////////////////////////////////
    //OpenGL and miscellaneous
    //////////////////////////////////

    const char* tgvShader = "shaders/textured geometry/specular lighting/shader.vert";
    const char* tgfShader = "shaders/textured geometry/specular lighting/shader.frag";
	pk::Shader *tgShader = new pk::Shader();
	tgShader->load(tgvShader, tgfShader);

    pk::GLStates textured_glStates;
	textured_glStates.modelLocation = &tgShader->getModelLocation();
    textured_glStates.projectionLocation = &tgShader->getProjectionLocation();
    textured_glStates.viewLocation = &tgShader->getViewLocation();
    textured_glStates.ambientIntensityLocation = &tgShader->getAmbientIntensityLocation();
    textured_glStates.ambientColorLocation = &tgShader->getAmbientColorLocation();
    textured_glStates.diffuseIntensityLocation = &tgShader->getDiffuseIntensityLocation();
    textured_glStates.directionLocation = &tgShader->getDirectionLocation();
    textured_glStates.specularIntensityLocation = &tgShader->getSpecularIntensityLocation();
    textured_glStates.shininessLocation = &tgShader->getShininessLocation();
    textured_glStates.eyePositionLocation = &tgShader->getEyePositionLocation();

    glm::mat4 projection = glm::ortho(0.0f, (float)pkWin->getSize().x, (float)pkWin->getSize().y, 0.0f, 0.1f, 100.0f);

    SDL_GL_MakeCurrent(win, *context);
    glViewport(0.f, 0.f, pkWin->getSize().x, pkWin->getSize().y);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pk::Material shinyMaterial = pk::Material(2.0f, 320);
    pk::Material dullMaterial = pk::Material(0.3f, 4);

    pk::Camera cam = pk::Camera({0.f, 0.f});
    cam.setRect({0.f, 0.f, 800.f, 600.f});
    cam.setOrigin({400.f, 300.f});
    cam.setPosition({400.f, 300.f});
    cam.setScale({1.f, 1.f});

    pk::DiffuseLight mainLight = pk::DiffuseLight({1.0f, 1.0f, 1.0f, 1.0f}, 1.0f, cam.getOrigin().x/2.f, cam.getOrigin().y/2.f, -1.0f, 0.5f);
    pk::DiffuseLight secondLight = pk::DiffuseLight({1.0f, 1.0f, 1.0f, 1.0f}, 1.0f, 100.0f, 100.0f, -1.0f, 1.0f);

    //data for frame calculations
    const Uint32 MAXIMUM_FRAME_RATE = 60;
    const Uint32 MINIMUM_FRAME_RATE = 30;
    const double UPDATE_INTERVAL = (1.0 / MAXIMUM_FRAME_RATE);
    const double MAX_CYCLES_PER_FRAME = (MAXIMUM_FRAME_RATE / MINIMUM_FRAME_RATE);

    static double lastFrameTime = 0.0;
    static double cyclesLeftOver = 0.0;
    double currentTime;
    double updateIterations;

    pk::GameController controller1 = pk::GameController(0);
    pk::GameController controller2 = pk::GameController(1);
    pk::GameController controller3 = pk::GameController(2);
    pk::GameController controller4 = pk::GameController(3);

    bool pressedLeft = false;
    bool pressedRight = false;
    double pressDelay = 50;
    double pressTime = 0;
    int pressCounter = 0;

    while(isRunning())
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                setState(levelSelectState::s_exit);
                Mix_PlayChannel(-1, m_selectedSound, 0);
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
                    setState(levelSelectState::s_exit);
                    Mix_PlayChannel(-1, m_selectedSound, 0);
                    return;
                }
                break;
                default:
                break;
                }
            }
        }

        if(controller1.getAxisState(pk::GameControllerAxis::LEFT_X) > 8000
           || controller1.getButtonState(pk::GameControllerButton::DPAD_RIGHT) == 1)
        {
            pressTime = SDL_GetTicks();
            pressedRight = true;
        }
        if(controller1.getAxisState(pk::GameControllerAxis::LEFT_X) < 8000
           && controller1.getButtonState(pk::GameControllerButton::DPAD_RIGHT) == 0)
        {
            pressedRight = false;
            pressCounter++;
        }

        if(controller1.getAxisState(pk::GameControllerAxis::LEFT_X) < -8000
           || controller1.getButtonState(pk::GameControllerButton::DPAD_LEFT) == 1)
        {
            pressTime = SDL_GetTicks();
            pressedLeft = true;
        }
        if(controller1.getAxisState(pk::GameControllerAxis::LEFT_X) > -8000
           && controller1.getButtonState(pk::GameControllerButton::DPAD_LEFT) == 0)
        {
            pressedLeft = false;
            pressCounter++;
        }

        if(controller1.getButtonState(pk::GameControllerButton::A)
           || controller1.getButtonState(pk::GameControllerButton::START))
        {
            levelSelectionMade();
            Mix_PlayChannel(-1, m_selectedSound, 0);
            return;
        }

        currentTime = SDL_GetTicks();
        updateIterations = ((currentTime - lastFrameTime) + cyclesLeftOver);

        if (updateIterations > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL))
        {
            updateIterations = (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL);
        }

        while (updateIterations > UPDATE_INTERVAL)
        {
            updateIterations -= UPDATE_INTERVAL;
        }

        if(pressedRight && pressCounter == 1)
        {
            if(m_selection < 8)
                m_selection++;

            m_levelTexture.load(levels[m_selection]);
            Mix_PlayChannel(-1, m_selectSound, 0);
        }

        if(pressedLeft && pressCounter == 1)
        {
            if(m_selection > 0)
                m_selection--;

            m_levelTexture.load(levels[m_selection]);
            Mix_PlayChannel(-1, m_selectSound, 0);
        }

        if(SDL_GetTicks() - pressTime > pressDelay)
            pressCounter = 0;

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        tgShader->use();

        mainLight.update(*textured_glStates.ambientIntensityLocation, *textured_glStates.ambientColorLocation, *textured_glStates.diffuseIntensityLocation, *textured_glStates.directionLocation);

        //initialize view with identity matrix...
        glm::mat4 view = glm::mat4(1.0f);
        //view must then be translated "above" the scene on the z-axis
        //by some arbitrary value so that the objects in the scene are not culled by OpenGL
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.1f));

        //pass the view to the camera to perform
        //camera-level (viewport) manipulations
        cam.update(textured_glStates, view);
        glUniform3f(*textured_glStates.eyePositionLocation, cam.getPosition().x, cam.getPosition().y, -0.1f);
        glUniformMatrix4fv(*textured_glStates.viewLocation, 1, GL_FALSE, glm::value_ptr(view));

        glUniformMatrix4fv(*textured_glStates.projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

        //begin model-level (graphical object) manipulations
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(*textured_glStates.modelLocation, 1, GL_FALSE, glm::value_ptr(model));

        shinyMaterial.use(*textured_glStates.specularIntensityLocation, *textured_glStates.shininessLocation);

        pkWin->draw(m_leftArrow, textured_glStates);
        pkWin->draw(m_levelSprite, textured_glStates);
        pkWin->draw(m_rightArrow, textured_glStates);

        glUseProgram(0);

        SDL_GL_SwapWindow(win);
    }
}
