#include "core/Game.hpp"

#include "states/MenuScreen.hpp"
#include "states/OptionsScreen.hpp"
#include "states/LevelSelectScreen.hpp"
#include "states/CharacterSelectScreen.hpp"
#include "states/LevelScreen.hpp"
#include "tables/options.hpp"

using namespace pk;

Game::~Game()
{
    delete m_window;
}

void Game::init()
{
    if(!(m_gameState == gameState::s_uninitialized))
    {
        printf("Game not in an uninitialized state!");
        return;
    }

    //initialize window
    std::ifstream jsonInput("data/options.json");
    cereal::JSONInputArchive inputOptions(jsonInput);
    pk::options::optionsCereal screenOptions;
    pk::options::load(inputOptions, screenOptions);

    setMusicVolume(screenOptions.d_musicVolume);
    setSoundEffectVolume(screenOptions.d_soundEffectVolume);

    SDL_Rect rect;
    rect.w = screenOptions.d_resolutionX;
    rect.h = screenOptions.d_resolutionY;
    rect.x = 0;
    rect.y = 0;

    setScalingFactor({rect.w/800.f, rect.h/600.f});

    if(screenOptions.d_fullscreen)
    {
        m_window = new Window("Game time!", glm::ivec2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED), rect.w, rect.h, SDL_WINDOW_OPENGL);
        SDL_SetWindowFullscreen(m_window->getWindow(), SDL_WINDOW_FULLSCREEN);
        SDL_RaiseWindow(m_window->getWindow());
    }
    else
    {
        m_window = new Window("Game time!", glm::ivec2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED), rect.w, rect.h, SDL_WINDOW_OPENGL);
        SDL_SetWindowFullscreen(m_window->getWindow(), 0);
        m_window->setPosition({0,0});
        SDL_RaiseWindow(m_window->getWindow());
    }

    m_window->setWindowRect(rect);

    m_gameState = gameState::s_menu;
    m_running = true;

    while(isRunning())
    {
        run();
    }
}

Game& Game::getInstance()
{
    static Game* gameInstance = new Game;
    return *gameInstance;
}

void Game::run()
{
    switch(m_gameState)
    {
        case gameState::s_menu:
        {
            menu();
        }
        break;
        case gameState::s_options:
        {
            options();
        }
        break;
        case gameState::s_levelSelect:
        {
            levelSelect();
        }
        break;
        case gameState::s_characterSelect:
        {
            characterSelect();
        }
        break;
        case gameState::s_level:
        {
            level();
        }
        break;
        case gameState::s_quit:
        {
            m_running = false;
        }
        break;
        default:
        break;
    }
}

void Game::menu()
{
    getWindow()->setTitle("Menu");
    if(m_menu != nullptr)
    {
        delete m_menu;
        m_menu = nullptr;
    }

    m_menu = new MenuScreen();
    m_menu->display();

    if(m_menu->getState() == MenuScreen::s_play)
    {
        m_gameState = gameState::s_levelSelect;
    }

    else if(m_menu->getState() == MenuScreen::s_options)
    {
        m_gameState = gameState::s_options;
    }

    else if(m_menu->getState() == MenuScreen::s_exit)
    {
        m_gameState = gameState::s_quit;
    }

    delete m_menu;
    m_menu = nullptr;
}

void Game::options()
{
    getWindow()->setTitle("Options");
    if(m_options != nullptr)
    {
        delete m_options;
        m_options = nullptr;
    }

    m_options = new OptionsScreen();
    m_options->display();

    if(m_options->getState() == OptionsScreen::s_menu)
    {
        m_gameState = gameState::s_menu;
    }

    else if(m_options->getState() == OptionsScreen::s_exit)
    {
        m_gameState = gameState::s_quit;
    }

    delete m_options;
    m_options = nullptr;
}

void Game::levelSelect()
{
    getWindow()->setTitle("Level Select");
    if(m_levelSelect != nullptr)
    {
        delete m_levelSelect;
        m_levelSelect = nullptr;
    }
    m_levelSelect = new LevelSelectScreen();
    m_levelSelect->display();

    if(m_levelSelect->getState() > LevelSelectScreen::s_running)
    {
        m_levelSelected = m_levelSelect->getState();
        m_gameState = gameState::s_characterSelect;
    }

    delete m_levelSelect;
    m_levelSelect = nullptr;
}

void Game::characterSelect()
{
    getWindow()->setTitle("Character Select");
    if(m_characterSelect != nullptr)
    {
        delete m_characterSelect;
        m_characterSelect = nullptr;
    }
    m_characterSelect = new CharacterSelectScreen();
    m_characterSelect->display();

    if(m_characterSelect->getState() == CharacterSelectScreen::s_exit)
    {
        m_gameState = gameState::s_level;
    }

    delete m_characterSelect;
    m_characterSelect = nullptr;
}

void Game::level()
{
    getWindow()->setTitle("Level");
    if(m_level != nullptr)
    {
        delete m_level;
        m_level = nullptr;
    }
    m_level = new LevelScreen(m_levelSelected);
    m_level->display();

    if(m_level->getState() == LevelScreen::s_menu)
    {
        m_gameState = gameState::s_menu;
    }

    else if(m_level->getState() == LevelScreen::s_exit)
    {
        m_gameState = gameState::s_quit;
    }

    delete m_level;
    m_level = nullptr;
}

//static member variable instantiation
//instantiate screen states...
Window* Game::m_window = nullptr;//Window("Game time!", glm::ivec2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED), 800, 600, SDL_WINDOW_OPENGL);
ScreenState * Game::m_menu = nullptr;
ScreenState * Game::m_options = nullptr;
ScreenState * Game::m_levelSelect = nullptr;
ScreenState * Game::m_characterSelect = nullptr;
ScreenState * Game::m_level = nullptr;

ScreenState * Game::m_state = nullptr;
Uint32 Game::m_gameState = Game::gameState::s_uninitialized;
bool Game::m_running = false;
glm::vec2 Game::m_scalingFactor = {1.f, 1.f};
int Game::m_musicVolume = 0;
int Game::m_soundEffectVolume = 0;
Uint32 Game::m_levelSelected = levelSelection::SPIKES;
std::string Game::m_p1 = "";
std::string Game::m_p2 = "";
std::string Game::m_p3 = "";
std::string Game::m_p4 = "";
