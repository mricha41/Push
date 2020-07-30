#include "states/OptionsScreen.hpp"

#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>

#include <SDL2/SDL_opengl.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"

#include "core/Game.hpp"
#include "core/GameController.hpp"
#include "utilities/DisplayInfo.hpp"
#include "utilities/ImGuiUtilities.hpp"

using namespace pk;

OptionsScreen::OptionsScreen()
:
    ScreenState()
{
    m_running = false;

    setState(optionsState::s_uninitialized);

    std::ifstream jsonInput("data/options.json");
    cereal::JSONInputArchive inputOptions(jsonInput);

    pk::options::load(inputOptions, m_options);
}

OptionsScreen::~OptionsScreen()
{
    //set the global options
    pk::Game::setMusicVolume(m_options.d_musicVolume);
    pk::Game::setSoundEffectVolume(m_options.d_soundEffectVolume);
    pk::Game::setScalingFactor({m_options.d_resolutionX/800.f, m_options.d_resolutionY/600.f});

    //set the window size and window rect
    pk::Game::getWindow()->setSize({m_options.d_resolutionX, m_options.d_resolutionY});
    SDL_Rect w = {0, 0, m_options.d_resolutionX, m_options.d_resolutionY};
    pk::Game::getWindow()->setWindowRect(w);
    pk::Game::setScalingFactor({m_options.d_resolutionX/800.f, m_options.d_resolutionY/600.f});
    if(m_options.d_fullscreen)
    {
        SDL_SetWindowFullscreen(pk::Game::getWindow()->getWindow(), SDL_WINDOW_FULLSCREEN);
        SDL_RaiseWindow(pk::Game::getWindow()->getWindow());
    }
    else
    {
        SDL_SetWindowFullscreen(pk::Game::getWindow()->getWindow(), 0);
        pk::Game::getWindow()->setPosition({0,0});
        SDL_RaiseWindow(pk::Game::getWindow()->getWindow());
    }

    //serialize the data
    std::ofstream jsonOutput("data/options.json");
    cereal::JSONOutputArchive outputOptions(jsonOutput);
    pk::options::save(outputOptions, m_options);

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void OptionsScreen::display()
{
    setState(optionsState::s_running);
    m_running = true;

    SDL_Event e;

    pk::utilities::DisplayInfo info;

    pk::Window* pkWin = pk::Game::getWindow();
    SDL_Window* win = pk::Game::getWindow()->getWindow();
    SDL_GLContext* context = &pk::Game::getWindow()->getContext();

    SDL_GL_MakeCurrent(win, *context);

    //gui
    IMGUI_CHECKVERSION();
    ImGuiContext* imcon = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.Fonts->AddFontFromFileTTF("fonts/Sansation_Regular.ttf", (int)24*pk::Game::getScalingFactor().x);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();


    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(win, *context);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImGui::SetCurrentContext(imcon);

    bool show_demo_window = false;

    //wrangle the available video modes
    //and format them for use with ImGui
    //use the first display at index zero
    //info.printDisplayModes();
    std::vector<SDL_DisplayMode> mainModes = info.getDisplayModes()[0];
    std::vector<std::string> modes;

    for(int i=0; i<mainModes.size(); ++i)
    {
        std::string s = std::to_string(mainModes[i].w) + " x " + std::to_string(mainModes[i].h);
        modes.push_back(s);
    }

    pk::ImGuiUtilities::removeDuplicatesSorted(modes);

    //"map" values back to a vector with actual
    //screen size values
    //ugliest thing i ever did see lol
    std::vector<glm::vec2> modeValues;
    {
        for(int i=0; i<modes.size(); ++i)
        {
            int a = 0;
            int b = 0;
            int j = 0;
            std::string number_str;
            int number;
            std::istringstream all_numbers_iss( modes[i] );
            while ( std::getline( all_numbers_iss, number_str, 'x' ) && std::istringstream( number_str ) >> number ) {
                if(j==0)
                    a = number;
                else
                    b = number;
                ++j;
            }
            modeValues.push_back({a, b});
        }
    }

    //set up first player controller
    //no other players to minimize confusion
    pk::GameController controller1 = pk::GameController(0);
    //printf("Controller name: %s\n", controller1.getControllerName());

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
        int x,y;
        SDL_GetMouseState(&x, &y);

        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                setState(optionsState::s_exit);
                return;
            }

            if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.scancode)
                {
                case SDL_SCANCODE_P:
                {
                    cereal::JSONOutputArchive printArchive( std::cout );
                    printArchive( m_options );
                }
                break;
                case SDL_SCANCODE_M:
                {
                    info.printNumberOfDisplayModes();
                }
                break;
                case SDL_SCANCODE_D:
                {
                    show_demo_window = true;
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
                    setState(optionsState::s_menu);
                    m_running = false;
                    return;
                }
                break;
                default:
                    break;
                }
            }
        }

        //get gamepad events
        if(controller1.getButtonState(pk::GameControllerButton::B) == 1)
        {
            setState(optionsState::s_menu);
            m_running = false;
            return;
        }

        currentTime = SDL_GetTicks();
        updateIterations = ((currentTime - lastFrameTime) + cyclesLeftOver);

        if (updateIterations > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL)) {
            updateIterations = (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL);
        }

        while (updateIterations > UPDATE_INTERVAL) {
            updateIterations -= UPDATE_INTERVAL;

            //updates go here...
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame(win);
            ImGui::NewFrame();

            ImGui::Begin("Options");

            ImGui::Checkbox("Fullscreen", &m_options.d_fullscreen);
            ImGui::SliderInt("Music Volume", &m_options.d_musicVolume, 0, 100);
            ImGui::SliderInt("Sound Effect Volume", &m_options.d_soundEffectVolume, 0, 100);

            static int item_current = 0;
            pk::ImGuiUtilities::Combo("Video Mode", &item_current, modes);
            ImGui::SameLine(); pk::ImGuiUtilities::HelpMarker("Refer to the \"Combo\" section below for an explanation of the full BeginCombo/EndCombo API, and demonstration of various flags.\n");

            //store the gui selection
            m_options.d_resolutionX = modeValues[item_current].x;
            m_options.d_resolutionY = modeValues[item_current].y;

            //in this case, tie the ImGui window size
            //to the SDL window size
            ImGui::SetWindowSize(ImVec2(pk::Game::getWindow()->getSize().x, pk::Game::getWindow()->getSize().y));

            ImGui::End();

            if(show_demo_window)
            {
                ImGui::ShowDemoWindow(&show_demo_window);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glClearColor(1.f, 0.5f, 0.f, 1.f);

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(win);
    }
}
