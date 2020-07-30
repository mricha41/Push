#include "states/LevelScreen.hpp"

#include "states/LevelSelectScreen.hpp"
#include "states/Arena.hpp"

LevelScreen::LevelScreen()
:
    ScreenState(),
    m_winnerTexture("images/characters/player1_wins.png"),
    m_winner(m_winnerTexture, {0.f, 0.f, 256.f, 256.f})
{
    m_running = false;

    setState(levelState::s_uninitialized);

    m_levelToLoad = pk::levelSelection::SPIKES;

    m_triggerOutro = false;
    m_outroDelay = 1600;
    m_outroTime = 0;
    m_outroSpeed = 20.f;

    m_winner.setPosition({pk::Game::getWindow()->getSize().x/2.f, pk::Game::getWindow()->getSize().y/2.f});
    m_winner.setScale(pk::Game::getScalingFactor()*2.f);
    m_winnerTexture.setTextureFilterParameters(pk::GLTextureFilter::NEAREST, pk::GLTextureFilter::NEAREST);

    m_matchTime = SDL_GetTicks();
}

LevelScreen::LevelScreen(Uint32 level)
:
    ScreenState(),
    m_winnerTexture("images/characters/player1_wins.png"),
    m_winner(m_winnerTexture, {0.f, 0.f, 256.f, 256.f})
{
    m_running = false;

    setState(levelState::s_uninitialized);

    m_levelToLoad = level;

    m_triggerOutro = false;
    m_outroDelay = 1600;
    m_outroTime = 0;
    m_outroSpeed = 20.f;

    m_winner.setPosition({pk::Game::getWindow()->getSize().x/2.f, pk::Game::getWindow()->getSize().y/2.f});
    m_winner.setScale(pk::Game::getScalingFactor()*2.f);

    m_matchTime = SDL_GetTicks();
}

LevelScreen::~LevelScreen()
{
    Mix_HaltMusic();
    Mix_FreeMusic(m_music);

    m_music = nullptr;

    delete m_arena;
}

void LevelScreen::display()
{
    //seed random...
    srand(NULL);

    setState(levelState::s_running);
    m_running = true;

    SDL_Event e;

    pk::Window* pkWin = pk::Game::getWindow();
    SDL_Window* win = pk::Game::getWindow()->getWindow();
    SDL_GLContext* context = &pk::Game::getWindow()->getContext();

    //box2d world setup
    const glm::vec2 scale = pk::Game::getScalingFactor();
    const float PPM = 16.f;
    const float MPP = 1.f/PPM;
    const float tilex = 16.f;
    const float tiley = 16.f;

    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    b2World* world = new b2World({0.f, 100.f});

    //////////////////////////////////////
    //set up arena and character controllers
    //////////////////////////////////////

    switch(m_levelToLoad)
    {
        case pk::levelSelection::SPIKES:
        {
            m_arena = new pk::Arena(world, "spikes");
            m_music = Mix_LoadMUS("sound/tracks/spike_arena_theme.mp3");
        }
        break;
        case pk::levelSelection::ICE:
        {
            m_arena = new pk::Arena(world, "ice");
            m_music = Mix_LoadMUS("sound/tracks/ice_arena_theme.mp3");
        }
        break;
        case pk::levelSelection::DESERT:
        {
            m_arena = new pk::Arena(world, "desert");
            m_music = Mix_LoadMUS("sound/tracks/desert_arena_theme.mp3");
        }
        break;
        case pk::levelSelection::JUNGLE:
        {
            m_arena = new pk::Arena(world, "jungle");
            m_music = Mix_LoadMUS("sound/tracks/jungle_arena_theme.mp3");
        }
        break;
        case pk::levelSelection::CASTLE:
        {
            m_arena = new pk::Arena(world, "castle");
            m_music = Mix_LoadMUS("sound/tracks/castle_arena_theme.mp3");
        }
        break;
        case pk::levelSelection::FIRE:
        {
            m_arena = new pk::Arena(world, "fire");
            m_music = Mix_LoadMUS("sound/tracks/fire_arena_theme.mp3");
        }
        break;
        case pk::levelSelection::GREEN:
        {
            m_arena = new pk::Arena(world, "green");
            m_music = Mix_LoadMUS("sound/tracks/green_arena_theme.mp3");
        }
        break;
        case pk::levelSelection::PINK:
        {
            m_arena = new pk::Arena(world, "pink");
            m_music = Mix_LoadMUS("sound/tracks/pink_arena_theme.mp3");
        }
        break;
        case pk::levelSelection::PURPLE:
        {
            m_arena = new pk::Arena(world, "purple");
            m_music = Mix_LoadMUS("sound/tracks/purple_arena_theme.mp3");
        }
        break;
        default:
        {
            m_arena = new pk::Arena(world, "spikes");
            m_music = Mix_LoadMUS("sound/tracks/spike_arena_theme.mp3");
        }
        break;
    }

    if(!m_music)
    {
        printf("Could not load music for the level: %s\n", Mix_GetError());
    }

    Mix_VolumeMusic(pk::Game::getMusicVolume());

    Mix_PlayMusic(m_music, -1);

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
    cam.setOrigin({400.f*scale.x, 300.f*scale.y});
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

    int outroTriggerCounter = 0;
    m_showWinner = false;

    while(isRunning())
    {
        while(SDL_PollEvent(&e) && m_triggerOutro != true)
        {
            if(SDL_GetTicks() - m_matchTime > 120000)//two minutes
            {
                m_triggerOutro = true;
                m_outroTime = SDL_GetTicks();
                outroTriggerCounter=1;
            }

            if(e.type == SDL_QUIT)
            {
                setState(levelState::s_exit);
                m_running = false;
                return;
            }

            if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.scancode)
                {
                case SDL_SCANCODE_A:
                {
                    cam.move({-10.f, 0.f});
                }
                break;
                case SDL_SCANCODE_D:
                {
                    cam.move({10.f, 0.f});
                }
                break;
                case SDL_SCANCODE_W:
                {
                    cam.move({0.f, -10.f});
                }
                break;
                case SDL_SCANCODE_S:
                {
                    cam.move({0.f, 10.f});
                }
                break;
                case SDL_SCANCODE_KP_4:
                {
                    cam.rotate(-5.f);
                }
                break;
                case SDL_SCANCODE_KP_6:
                {
                    cam.rotate(5.f);
                }
                break;
                case SDL_SCANCODE_KP_8:
                {
                    cam.scale({0.01f, 0.01f});
                }
                break;
                case SDL_SCANCODE_KP_2:
                {
                    cam.scale({-0.01f, -0.01f});
                }
                break;
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
                    //trigger the outro animation
                    m_triggerOutro = true;
                    m_outroTime = SDL_GetTicks();
                    outroTriggerCounter++;
                }
                break;
                default:
                    break;
                }
            }
        }

        //only do the outro once! ;)
        if(outroTriggerCounter > 1)
            m_outroTime = 0;//let them skip the outro...

        //sweet fancy screen rotation and scale
        //outro animation!
        if(m_triggerOutro)
        {
            m_showWinner = true;
            if(SDL_GetTicks() - m_outroTime > m_outroDelay/4.f)
            {
                cam.rotate(m_outroSpeed);
                cam.scale({-0.02f, -0.02f});
            }
            if(SDL_GetTicks() - m_outroTime > m_outroDelay)
            {
                setState(levelState::s_menu);
                m_running = false;
                return;
            }
        }

        m_arena->handleInput();

        if(!m_arena->requestPause())
        {
            currentTime = SDL_GetTicks();
            updateIterations = ((currentTime - lastFrameTime) + cyclesLeftOver);

            if (updateIterations > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL)) {
                updateIterations = (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL);
            }

            while (updateIterations > UPDATE_INTERVAL) {
                updateIterations -= UPDATE_INTERVAL;

                //updates go here...
                world->Step(UPDATE_INTERVAL, velocityIterations, positionIterations);
            }

            //level updates
            m_arena->update(UPDATE_INTERVAL);
        }

        /////////////////////////////
        //RENDERING
        /////////////////////////////
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

        m_arena->render(textured_glStates);

        if(m_showWinner)
        {
            switch(m_arena->getWinner())
            {
                case 0:
                {
                    m_winnerTexture.load("images/characters/player1_wins.png");
                }
                break;
                case 1:
                {
                    m_winnerTexture.load("images/characters/player2_wins.png");
                }
                break;
                case 2:
                {
                    m_winnerTexture.load("images/characters/player3_wins.png");
                }
                break;
                case 3:
                {
                    m_winnerTexture.load("images/characters/player4_wins.png");
                }
                break;
                default:
                    break;
            }
            pkWin->draw(m_winner, textured_glStates);
        }

        glUseProgram(0);

        m_arena->renderHUD();

        SDL_GL_SwapWindow(win);
    }

    //clean up
    delete tgShader;
}

