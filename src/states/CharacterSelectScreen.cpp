#include "states/CharacterSelectScreen.hpp"

#include <stdio.h>

#include "core/GameController.hpp"
#include "graphics/Camera.hpp"
#include "graphics/Shader.hpp"
#include "lighting/DiffuseLight.hpp"
#include "lighting/Material.hpp"

using namespace pk;

CharacterSelectScreen::CharacterSelectScreen()
:
    ScreenState(),
    m_music(nullptr),
    m_selectSound(nullptr),
    m_selectionSound(nullptr),
    m_selectedSound(nullptr),
    m_p1LabelTexture("images/characters/player1.png"),
    m_p2LabelTexture("images/characters/player2.png"),
    m_p3LabelTexture("images/characters/player3.png"),
    m_p4LabelTexture("images/characters/player4.png"),
    m_playerOneTexture("images/characters/fluffy_coral.png"),
    m_playerTwoTexture("images/characters/fluffy_purple.png"),
    m_playerThreeTexture("images/characters/fluffy_black.png"),
    m_playerFourTexture("images/characters/fluffy_green.png"),
    m_playerOne(m_playerOneTexture, {0.f, 0.f, 16.f, 16.f}),
    m_playerTwo(m_playerTwoTexture, {0.f, 0.f, 16.f, 16.f}),
    m_playerThree(m_playerThreeTexture, {0.f, 0.f, 16.f, 16.f}),
    m_playerFour(m_playerFourTexture, {0.f, 0.f, 16.f, 16.f}),
    m_p1Label(m_p1LabelTexture, {0.f, 0.f, 256.f, 128.f}),
    m_p2Label(m_p2LabelTexture, {0.f, 0.f, 256.f, 128.f}),
    m_p3Label(m_p3LabelTexture, {0.f, 0.f, 256.f, 128.f}),
    m_p4Label(m_p4LabelTexture, {0.f, 0.f, 256.f, 128.f}),
    m_p1Selection(0),
    m_p2Selection(0),
    m_p3Selection(0),
    m_p4Selection(0),
    m_p1Path("images/characters/fluffy_coral.png"),
    m_p2Path("images/characters/fluffy_purple.png"),
    m_p3Path("images/characters/fluffy_black.png"),
    m_p4Path("images/characters/fluffy_green.png")
{
    m_running = false;

    setState(characterSelectState::s_uninitialized);
}

CharacterSelectScreen::~CharacterSelectScreen()
{
    Mix_HaltMusic();
    Mix_FreeMusic(m_music);

    m_music = nullptr;

    Mix_FreeChunk(m_selectSound);
    m_selectSound = nullptr;

    Mix_FreeChunk(m_selectionSound);
    m_selectionSound = nullptr;

    Mix_FreeChunk(m_selectedSound);
    m_selectedSound = nullptr;

    pk::Game::setPlayerCharacters(m_p1Path, m_p2Path, m_p3Path, m_p4Path);
}

void CharacterSelectScreen::display()
{
    setState(characterSelectState::s_running);
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

    m_selectionSound = Mix_LoadWAV("sound/selection.wav");
    Mix_VolumeChunk(m_selectionSound, pk::Game::getSoundEffectVolume());

    m_selectedSound = Mix_LoadWAV("sound/selected.wav");
    Mix_VolumeChunk(m_selectedSound, pk::Game::getSoundEffectVolume());

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

    /////////////////////////////
    //player selections setup
    /////////////////////////////
    pk::GameController controller1 = pk::GameController(0);
    pk::GameController controller2 = pk::GameController(1);
    pk::GameController controller3 = pk::GameController(2);
    pk::GameController controller4 = pk::GameController(3);

    m_playerOneTexture.setTextureFilterParameters(pk::GLTextureFilter::NEAREST, pk::GLTextureFilter::NEAREST);
    m_playerTwoTexture.setTextureFilterParameters(pk::GLTextureFilter::NEAREST, pk::GLTextureFilter::NEAREST);
    m_playerThreeTexture.setTextureFilterParameters(pk::GLTextureFilter::NEAREST, pk::GLTextureFilter::NEAREST);
    m_playerFourTexture.setTextureFilterParameters(pk::GLTextureFilter::NEAREST, pk::GLTextureFilter::NEAREST);

    m_playerOne.setPosition({pk::Game::getWindow()->getSize().x/4.f, pk::Game::getWindow()->getSize().y/4.f});
    m_playerOne.setScale(pk::Game::getScalingFactor()*4.f);
    m_p1Label.setPosition({m_playerOne.getPosition().x, m_playerOne.getPosition().y - (64.f*pk::Game::getScalingFactor().y)});
    m_p1Label.setScale(pk::Game::getScalingFactor());

    m_playerTwo.setPosition({pk::Game::getWindow()->getSize().x/1.25f, pk::Game::getWindow()->getSize().y/4.f});
    m_playerTwo.setScale(pk::Game::getScalingFactor()*4.f);
    m_p2Label.setPosition({m_playerTwo.getPosition().x, m_playerTwo.getPosition().y - (64.f*pk::Game::getScalingFactor().y)});
    m_p2Label.setScale(pk::Game::getScalingFactor());

    m_playerThree.setPosition({pk::Game::getWindow()->getSize().x/4.f, pk::Game::getWindow()->getSize().y/1.25f});
    m_playerThree.setScale(pk::Game::getScalingFactor()*4.f);
    m_p3Label.setPosition({m_playerThree.getPosition().x, m_playerThree.getPosition().y - (64.f*pk::Game::getScalingFactor().y)});
    m_p3Label.setScale(pk::Game::getScalingFactor());

    m_playerFour.setPosition({pk::Game::getWindow()->getSize().x/1.25f, pk::Game::getWindow()->getSize().y/1.25f});
    m_playerFour.setScale(pk::Game::getScalingFactor()*4.f);
    m_p4Label.setPosition({m_playerFour.getPosition().x, m_playerFour.getPosition().y - (64.f*pk::Game::getScalingFactor().y)});
    m_p4Label.setScale(pk::Game::getScalingFactor());

    std::string selections[12] =
    {
        "images/characters/fluffy_aqua.png",
        "images/characters/fluffy_aquamarine.png",
        "images/characters/fluffy_black.png",
        "images/characters/fluffy_blue.png",
        "images/characters/fluffy_coffee.png",
        "images/characters/fluffy_coral.png",
        "images/characters/fluffy_green.png",
        "images/characters/fluffy_orange.png",
        "images/characters/fluffy_pink.png",
        "images/characters/fluffy_purple.png",
        "images/characters/fluffy_red.png",
        "images/characters/fluffy_yellow.png"
    };

    std::string selectionLarge[12] =
    {
        "images/characters/fluffy_aqua_large.png",
        "images/characters/fluffy_aquamarine_large.png",
        "images/characters/fluffy_black_large.png",
        "images/characters/fluffy_blue_large.png",
        "images/characters/fluffy_coffee_large.png",
        "images/characters/fluffy_coral_large.png",
        "images/characters/fluffy_green_large.png",
        "images/characters/fluffy_orange_large.png",
        "images/characters/fluffy_pink_large.png",
        "images/characters/fluffy_purple_large.png",
        "images/characters/fluffy_red_large.png",
        "images/characters/fluffy_yellow_large.png"
    };

    bool p1PressedRight = false;
    bool p2PressedRight = false;
    bool p3PressedRight = false;
    bool p4PressedRight = false;

    bool p1PressedLeft = false;
    bool p2PressedLeft = false;
    bool p3PressedLeft = false;
    bool p4PressedLeft = false;

    double p1PressTime = 0;
    double p2PressTime = 0;
    double p3PressTime = 0;
    double p4PressTime = 0;

    int p1PressCounter = 0;
    int p2PressCounter = 0;
    int p3PressCounter = 0;
    int p4PressCounter = 0;

    double pressDelay = 50;
    bool ready = false;

    const Uint32 MAXIMUM_FRAME_RATE = 60;
    const Uint32 MINIMUM_FRAME_RATE = 30;
    const double UPDATE_INTERVAL = (1.0 / MAXIMUM_FRAME_RATE);
    const double MAX_CYCLES_PER_FRAME = (MAXIMUM_FRAME_RATE / MINIMUM_FRAME_RATE);

    static double lastFrameTime = 0.0;
    static double cyclesLeftOver = 0.0;
    double currentTime;
    double updateIterations;

    while(isRunning())
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                setState(characterSelectState::s_exit);
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
                    setState(characterSelectState::s_exit);
                    Mix_PlayChannel(-1, m_selectedSound, 0);
                    return;
                }
                break;
                case SDL_SCANCODE_RETURN:
                {

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
            p1PressTime = SDL_GetTicks();
            p1PressedRight = true;
        }
        if(controller1.getAxisState(pk::GameControllerAxis::LEFT_X) < 8000
           && controller1.getButtonState(pk::GameControllerButton::DPAD_RIGHT) == 0)
        {
            p1PressedRight = false;
            p1PressCounter++;
        }

        if(controller1.getAxisState(pk::GameControllerAxis::LEFT_X) < -8000
           || controller1.getButtonState(pk::GameControllerButton::DPAD_LEFT) == 1)
        {
            p1PressTime = SDL_GetTicks();
            p1PressedLeft = true;
        }
        if(controller1.getAxisState(pk::GameControllerAxis::LEFT_X) > -8000
           && controller1.getButtonState(pk::GameControllerButton::DPAD_LEFT) == 0)
        {
            p1PressedLeft = false;
            p1PressCounter++;
        }

        if(controller1.getButtonState(pk::GameControllerButton::A))
        {
            Mix_PlayChannel(-1, m_selectionSound, 0);
        }

        if(controller1.getButtonState(pk::GameControllerButton::START))
        {
            Mix_PlayChannel(-1, m_selectedSound, 0);
            ready = true;
        }

        if(controller2.getAxisState(pk::GameControllerAxis::LEFT_X) > 8000
           || controller2.getButtonState(pk::GameControllerButton::DPAD_RIGHT) == 1)
        {
            p2PressTime = SDL_GetTicks();
            p2PressedRight = true;
        }
        if(controller2.getAxisState(pk::GameControllerAxis::LEFT_X) < 8000
           && controller2.getButtonState(pk::GameControllerButton::DPAD_RIGHT) == 0)
        {
            p2PressedRight = false;
            p2PressCounter++;
        }

        if(controller2.getAxisState(pk::GameControllerAxis::LEFT_X) < -8000
           || controller2.getButtonState(pk::GameControllerButton::DPAD_LEFT) == 1)
        {
            p2PressTime = SDL_GetTicks();
            p2PressedLeft = true;
        }
        if(controller2.getAxisState(pk::GameControllerAxis::LEFT_X) > -8000
           && controller2.getButtonState(pk::GameControllerButton::DPAD_LEFT) == 0)
        {
            p2PressedLeft = false;
            p2PressCounter++;
        }

        if(controller2.getButtonState(pk::GameControllerButton::A)
           || controller2.getButtonState(pk::GameControllerButton::START))
        {
            Mix_PlayChannel(-1, m_selectionSound, 0);
        }

        if(controller3.getAxisState(pk::GameControllerAxis::LEFT_X) > 8000
           || controller3.getButtonState(pk::GameControllerButton::DPAD_RIGHT) == 1)
        {
            p3PressTime = SDL_GetTicks();
            p3PressedRight = true;
        }
        if(controller3.getAxisState(pk::GameControllerAxis::LEFT_X) < 8000
           && controller3.getButtonState(pk::GameControllerButton::DPAD_RIGHT) == 0)
        {
            p3PressedRight = false;
            p3PressCounter++;
        }

        if(controller3.getAxisState(pk::GameControllerAxis::LEFT_X) < -8000
           || controller3.getButtonState(pk::GameControllerButton::DPAD_LEFT) == 1)
        {
            p3PressTime = SDL_GetTicks();
            p3PressedLeft = true;
        }
        if(controller3.getAxisState(pk::GameControllerAxis::LEFT_X) > -8000
           && controller3.getButtonState(pk::GameControllerButton::DPAD_LEFT) == 0)
        {
            p3PressedLeft = false;
            p3PressCounter++;
        }

        if(controller3.getButtonState(pk::GameControllerButton::A)
           || controller3.getButtonState(pk::GameControllerButton::START))
        {
            Mix_PlayChannel(-1, m_selectionSound, 0);
        }

        if(controller4.getAxisState(pk::GameControllerAxis::LEFT_X) > 8000
           || controller4.getButtonState(pk::GameControllerButton::DPAD_RIGHT) == 1)
        {
            p4PressTime = SDL_GetTicks();
            p4PressedRight = true;
        }
        if(controller4.getAxisState(pk::GameControllerAxis::LEFT_X) < 8000
           && controller4.getButtonState(pk::GameControllerButton::DPAD_RIGHT) == 0)
        {
            p4PressedRight = false;
            p4PressCounter++;
        }

        if(controller4.getAxisState(pk::GameControllerAxis::LEFT_X) < -8000
           || controller4.getButtonState(pk::GameControllerButton::DPAD_LEFT) == 1)
        {
            p4PressTime = SDL_GetTicks();
            p4PressedLeft = true;
        }
        if(controller4.getAxisState(pk::GameControllerAxis::LEFT_X) > -8000
           && controller4.getButtonState(pk::GameControllerButton::DPAD_LEFT) == 0)
        {
            p4PressedLeft = false;
            p4PressCounter++;
        }

        if(controller4.getButtonState(pk::GameControllerButton::A)
           || controller4.getButtonState(pk::GameControllerButton::START))
        {
            Mix_PlayChannel(-1, m_selectionSound, 0);
        }

        currentTime = SDL_GetTicks();
        updateIterations = ((currentTime - lastFrameTime) + cyclesLeftOver);

        if (updateIterations > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL)) {
            updateIterations = (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL);
        }

        while (updateIterations > UPDATE_INTERVAL) {
            updateIterations -= UPDATE_INTERVAL;
        }

        if(p1PressedRight && p1PressCounter == 1)
        {
            if(m_p1Selection < 11)
                m_p1Selection++;

            m_playerOneTexture.load(selectionLarge[m_p1Selection]);
            m_p1Path = selections[m_p1Selection];
            Mix_PlayChannel(-1, m_selectSound, 0);
        }

        if(p1PressedLeft && p1PressCounter == 1)
        {
            if(m_p1Selection > 0)
                m_p1Selection--;

            m_playerOneTexture.load(selectionLarge[m_p1Selection]);
            m_p1Path = selections[m_p1Selection];
            Mix_PlayChannel(-1, m_selectSound, 0);
        }

        if(p2PressedRight && p2PressCounter == 1)
        {
            if(m_p2Selection < 11)
                m_p2Selection++;

            m_playerTwoTexture.load(selectionLarge[m_p2Selection]);
            m_p2Path = selections[m_p2Selection];
            Mix_PlayChannel(-1, m_selectSound, 0);
        }

        if(p2PressedLeft && p2PressCounter == 1)
        {
            if(m_p2Selection > 0)
                m_p2Selection--;

            m_playerTwoTexture.load(selectionLarge[m_p2Selection]);
            m_p2Path = selections[m_p2Selection];
            Mix_PlayChannel(-1, m_selectSound, 0);
        }

        if(p3PressedRight && p3PressCounter == 1)
        {
            if(m_p3Selection < 11)
                m_p3Selection++;

            m_playerThreeTexture.load(selectionLarge[m_p3Selection]);
            m_p3Path = selections[m_p3Selection];
            Mix_PlayChannel(-1, m_selectSound, 0);
        }

        if(p3PressedLeft && p3PressCounter == 1)
        {
            if(m_p3Selection > 0)
                m_p3Selection--;

            m_playerThreeTexture.load(selectionLarge[m_p3Selection]);
            m_p3Path = selections[m_p3Selection];
            Mix_PlayChannel(-1, m_selectSound, 0);
        }

        if(p4PressedRight && p4PressCounter == 1)
        {
            if(m_p4Selection < 11)
                m_p4Selection++;

            m_playerFourTexture.load(selectionLarge[m_p4Selection]);
            m_p4Path = selections[m_p4Selection];
            Mix_PlayChannel(-1, m_selectSound, 0);
        }

        if(p4PressedLeft && p4PressCounter == 1)
        {
            if(m_p4Selection > 0)
                m_p4Selection--;

            m_playerFourTexture.load(selectionLarge[m_p4Selection]);
            m_p4Path = selections[m_p4Selection];
            Mix_PlayChannel(-1, m_selectSound, 0);
        }

        if(SDL_GetTicks() - p1PressTime > pressDelay)
        {
            p1PressCounter = 0;
        }

        if(SDL_GetTicks() - p2PressTime > pressDelay)
        {
            p2PressCounter = 0;
        }

        if(SDL_GetTicks() - p3PressTime > pressDelay)
        {
            p3PressCounter = 0;
        }

        if(SDL_GetTicks() - p4PressTime > pressDelay)
        {
            p4PressCounter = 0;
        }

        if(ready)
        {
            setState(characterSelectState::s_exit);
            if(!Mix_Playing(-1))
                return;
        }

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

        pkWin->draw(m_playerOne, textured_glStates);
        pkWin->draw(m_playerTwo, textured_glStates);
        pkWin->draw(m_playerThree, textured_glStates);
        pkWin->draw(m_playerFour, textured_glStates);
        pkWin->draw(m_p1Label, textured_glStates);
        pkWin->draw(m_p2Label, textured_glStates);
        pkWin->draw(m_p3Label, textured_glStates);
        pkWin->draw(m_p4Label, textured_glStates);

        glUseProgram(0);

        SDL_GL_SwapWindow(win);
    }
}
