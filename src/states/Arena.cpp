#include "states/Arena.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"

#include "states/HUD.hpp"
#include "core/Game.hpp"

using namespace pk;

Arena::Arena(b2World* world, std::string level)
:
    m_world(world),
    m_level(level),
    m_backgroundTexture(std::string("levels/" + level + "/" + level + "_arena_final.png")),
    m_backgroundSprite(m_backgroundTexture, {0, 0, 800.f, 600.f}),
    m_shortPlatformTexture(std::string("images/" + level + " arena/short_platform.png")),
    m_mediumPlatformTexture(std::string("images/" + level + " arena/medium_platform.png")),
    m_longPlatformTexture(std::string("images/" + level + " arena/long_platform.png")),
    m_thwompTexture(std::string("images/" + level + " arena/thwomp.png")),
    m_fishTexture("images/fish/fish.png"),
    m_groundEnemyTexture("images/blobs/blue_blob.png"),
    m_playerOneTexture(pk::Game::getPlayerCharacters()[0]),
    m_playerTwoTexture(pk::Game::getPlayerCharacters()[1]),
    m_playerThreeTexture(pk::Game::getPlayerCharacters()[2]),
    m_playerFourTexture(pk::Game::getPlayerCharacters()[3]),
    m_controllerMappingTexture("images/controller/mappings.png"),
    m_controllerMapping(m_controllerMappingTexture, {0.f, 0.f, 474.f, 302.f})
{
    m_window = pk::Game::getWindow();
    m_SDLWindow = pk::Game::getWindow()->getWindow();
    m_context = &pk::Game::getWindow()->getContext();
    const glm::vec2 scale = pk::Game::getScalingFactor();

    m_backgroundSprite.setScale(pk::Game::getScalingFactor());
    m_backgroundSprite.setPosition({m_window->getSize().x/2.f, m_window->getSize().y/2.f});

    m_controllerMapping.setScale(pk::Game::getScalingFactor());
    m_controllerMapping.setPosition({m_window->getSize().x/2.f, m_window->getSize().y - 452.f});

    //////////////////////////////////////
    //platforms and level entity setup
    //////////////////////////////////////

    //static platforms
    m_platformData.configure_dialect("no headers")
        .header(false)
        .column_names("top", "left", "width", "height");
    m_platformData.read(std::string("levels/" + level + "/arena.csv"));
    auto rows = m_platformData.rows();
    for(auto& row : rows)
    {
        m_platforms.push_back(
            pk::StaticPlatform(
                m_world,
                {
                    ::atof(row["top"].c_str()),
                    ::atof(row["left"].c_str()),
                    ::atof(row["width"].c_str()),
                    ::atof(row["height"].c_str())
                }
            )
        );
    }

    //special platform data
    //moving platforms, etc.
    m_specialPlatformData.configure_dialect("no headers")
        .header(false)
        .column_names("top", "left", "endPositionX", "endPositionY", "platformSpeed", "type", "size");
    m_specialPlatformData.read(std::string("levels/" + level + "/platforms.csv"));
    auto specialPlatformRows = m_specialPlatformData.rows();
    for(auto& row : specialPlatformRows)
    {
        std::string type = std::string(row["type"].c_str());
        std::string s = std::string(row["size"].c_str());

        if(type == "moving")
        {
            if(s == "short")
            {
                m_movingPlatforms.push_back(
                    new pk::MovingPlaform(
                        m_world,
                        m_shortPlatformTexture,
                            {
                                ::atof(row["top"].c_str()),
                                ::atof(row["left"].c_str()),
                                32.f,
                                15.f
                            },
                            {
                                ::atof(row["endPositionX"].c_str()),
                                ::atof(row["endPositionY"].c_str())
                            },
                            ::atof(row["platformSpeed"].c_str())
                    )
                );
            }
            else if(s == "medium")
            {
                m_movingPlatforms.push_back(
                    new pk::MovingPlaform(
                        m_world,
                        m_mediumPlatformTexture,
                            {
                                ::atof(row["top"].c_str()),
                                ::atof(row["left"].c_str()),
                                64.f,
                                16.f
                            },
                            {
                                ::atof(row["endPositionX"].c_str()),
                                ::atof(row["endPositionY"].c_str())
                            },
                            ::atof(row["platformSpeed"].c_str())
                    )
                );
            }
            else if(s == "long")
            {
                m_movingPlatforms.push_back(
                    new pk::MovingPlaform(
                        m_world,
                        m_longPlatformTexture,
                            {
                                ::atof(row["top"].c_str()),
                                ::atof(row["left"].c_str()),
                                128.f,
                                15.f
                            },
                            {
                                ::atof(row["endPositionX"].c_str()),
                                ::atof(row["endPositionY"].c_str())
                            },
                            ::atof(row["platformSpeed"].c_str())
                    )
                );
            }
        }
    }

    //thwomp data
    m_thwompData.configure_dialect("no headers")
        .header(false)
        .column_names("top", "left", "width", "height", "crushX", "crushY", "crushSpeed");
    m_thwompData.read(std::string("levels/" + level + "/thwomps.csv"));
    auto thwomprows = m_thwompData.rows();
    for(auto& row : thwomprows)
    {
        m_thwomps.push_back(
            new pk::Thwomp(
                m_world,
                m_thwompTexture,
                    {
                        ::atof(row["top"].c_str()),
                        ::atof(row["left"].c_str()),
                        ::atof(row["width"].c_str()),
                        ::atof(row["height"].c_str())
                    },
                    {
                        ::atof(row["crushX"].c_str()),
                        ::atof(row["crushY"].c_str())
                    },
                    ::atof(row["crushSpeed"].c_str())
            )
        );
    }

    //set up enemies
    m_fishParams.radius = 4.f;
    m_fishParams.SeekWeight = 10.f;
    m_fishParams.MaxSpeed = 100.f;
    m_fishParams.MaxForce = 500.f;
    m_fishParams.SteeringForceTweaker = 200.f;

    m_ghostData.configure_dialect("no headers")
        .header(false)
        .column_names("top", "left");
    m_ghostData.read(std::string("levels/" + level + "/ghosts.csv"));
    auto ghostrows = m_ghostData.rows();
    for(auto& row : ghostrows)
    {
        m_fish.push_back(
            new pk::Ghost(
                m_world,
                m_fishTexture,
                {
                    ::atof(row["top"].c_str()),
                    ::atof(row["left"].c_str()),
                    24.f,
                    16.f
                },
                &m_fishParams
            )
        );
    }

    m_groundEnemyParams.radius = 4.f;
    m_groundEnemyParams.SeekWeight = 5.f;
    m_groundEnemyParams.MaxSpeed = 100.f;
    m_groundEnemyParams.MaxForce = 500.f;
    m_groundEnemyParams.SteeringForceTweaker = 200.f;

    m_walkerData.configure_dialect("no headers")
        .header(false)
        .column_names("top", "left", "begin", "end");
    m_walkerData.read(std::string("levels/" + level + "/walkers.csv"));
    auto walkerrows = m_walkerData.rows();
    for(auto& row : walkerrows)
    {
        m_groundEnemies.push_back(
            new pk::Walker(
                m_world,
                m_groundEnemyTexture,
                {
                    ::atof(row["top"].c_str()),
                    ::atof(row["left"].c_str()),
                    16.f,
                    16.f
                },
                {
                    ::atof(row["begin"].c_str()),
                    ::atof(row["end"].c_str())
                },
                &m_groundEnemyParams
            )
        );
    }

    if(level == "jungle")
        m_beeManager = new pk::BeeColonyManager(30000);
    else
        m_beeManager = nullptr;

    //////////////////////////////////////
    //end platform and level entity setup
    //////////////////////////////////////

    /////////////////////////////////
    //death zones
    /////////////////////////////////
    m_deathZoneData.configure_dialect("no headers")
        .header(false)
        .column_names("top", "left", "width", "height");
    m_deathZoneData.read(std::string("levels/" + level + "/death_zones.csv"));
    auto deathzonerows = m_deathZoneData.rows();
    for(auto& row : deathzonerows)
    {
        m_deathZones.push_back(
            pk::GLRect(
                {
                    ::atof(row["top"].c_str())*scale.y,
                    ::atof(row["left"].c_str())*scale.x,
                    ::atof(row["width"].c_str())*scale.x,
                    ::atof(row["height"].c_str())*scale.y
                }
            )
        );
    }

    /////////////////////////////////
    //spawn zones
    /////////////////////////////////
    m_spawnZoneData.configure_dialect("no headers")
        .header(false)
        .column_names("x", "y");
    m_spawnZoneData.read(std::string("levels/" + level + "/spawn_zones.csv"));
    auto spawnzonerows = m_spawnZoneData.rows();
    for(auto& row : spawnzonerows)
    {
        m_spawnZones.push_back(
            glm::vec2(
                {
                    ::atof(row["x"].c_str()),
                    ::atof(row["y"].c_str())
                }
            )
        );
    }

    //initialize positions of players
    //using the first 4 spawn zones available
    //could add more and randomize re-spawns...
    m_p1 = new pk::CharacterController(m_world, m_playerOneTexture, 0, {m_spawnZones[0].y, m_spawnZones[0].x, 16.f, 16.f});
    m_p2 = new pk::CharacterController(m_world, m_playerTwoTexture, 1, {m_spawnZones[1].y, m_spawnZones[1].x, 16.f, 16.f});
    m_p3 = new pk::CharacterController(m_world, m_playerThreeTexture, 2, {m_spawnZones[2].y, m_spawnZones[2].x, 16.f, 16.f});
    m_p4 = new pk::CharacterController(m_world, m_playerFourTexture, 3, {m_spawnZones[3].y, m_spawnZones[3].x, 16.f, 16.f});

    //set up contact listeners for
    //character controllers
    m_world->SetContactListener(m_p1);
    m_world->SetContactListener(m_p2);
    m_world->SetContactListener(m_p3);
    m_world->SetContactListener(m_p4);

    /////////////////////////////
    //ImGui setup
    /////////////////////////////
    IMGUI_CHECKVERSION();
    ImGuiContext* imcon = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->AddFontFromFileTTF("fonts/Sansation_Regular.ttf", 12.f*pk::Game::getScalingFactor().x);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(m_SDLWindow, *m_context);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImGui::SetCurrentContext(imcon);

    /////////////////////////////
    //end ImGui setup
    /////////////////////////////

    //HUD...
    m_hud = new pk::HUD("Deaths", 4);
    m_hud->setPosition((glm::fvec2)pk::Game::getWindow()->getSize()/2.f);
    m_hud->setSize((glm::fvec2)pk::Game::getWindow()->getSize()/3.f);
}

Arena::~Arena()
{
    for(auto& platform : m_movingPlatforms)
        delete platform;

    for(auto& thwomp : m_thwomps)
        delete thwomp;

    for(auto& fish : m_fish)
        delete fish;

    for(auto& enemy : m_groundEnemies)
        delete enemy;

    if(m_beeManager)
        delete m_beeManager;

    delete m_p1;
    delete m_p2;
    delete m_p3;
    delete m_p4;

    delete m_hud;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Arena::handleInput()
{
    m_p1->handleInput();
    m_p2->handleInput();
    m_p3->handleInput();
    m_p4->handleInput();
}

void Arena::update(float dt)
{
    ///////////////////////////
    //player updates
    ///////////////////////////
    m_p1->update();
    m_p2->update();
    m_p3->update();
    m_p4->update();

    //check for deaths...
    for(auto& death : m_deathZones)
    {
        glm::vec2 p1 = m_p1->getPosition();
        glm::vec2 p2 = m_p2->getPosition();
        glm::vec2 p3 = m_p3->getPosition();
        glm::vec2 p4 = m_p4->getPosition();
        float padding = 4.f;
        if(p1.x > (death.d_left + padding)
           && p1.x < (death.d_left + (death.d_width - padding))
           && p1.y > (death.d_top + padding)
           && p1.y < (death.d_top + (death.d_height - padding)))
        {
            m_p1->died(m_spawnZones[0]);
            printf("p1 deaths: %i\n", m_p1->deaths());
            m_hud->increaseDeaths(0, 1);
        }

        if(p2.x > (death.d_left + padding)
           && p2.x < (death.d_left + (death.d_width - padding))
           && p2.y > (death.d_top + padding)
           && p2.y < (death.d_top + (death.d_height - padding)))
        {
            m_p2->died(m_spawnZones[1]);
            printf("p2 deaths: %i\n", m_p2->deaths());
            m_hud->increaseDeaths(1, 1);
        }

        if(p3.x > (death.d_left + padding)
           && p3.x < (death.d_left + (death.d_width - padding))
           && p3.y > (death.d_top + padding)
           && p3.y < (death.d_top + (death.d_height - padding)))
        {
            m_p3->died(m_spawnZones[2]);
            printf("p3 deaths: %i\n", m_p3->deaths());
            m_hud->increaseDeaths(2, 1);
        }

        if(p4.x > (death.d_left + padding)
           && p4.x < (death.d_left + (death.d_width - padding))
           && p4.y > (death.d_top + padding)
           && p4.y < (death.d_top + (death.d_height - padding)))
        {
            m_p4->died(m_spawnZones[3]);
            printf("p4 deaths: %i\n", m_p4->deaths());
            m_hud->increaseDeaths(3, 1);
        }
    }

    for(auto& thwomp : m_thwomps)
        thwomp->update();

    for(auto& platform : m_movingPlatforms)
        platform->update();

    m_fish[0]->update(dt, m_p1->getSprite().getPosition());
    m_fish[1]->update(dt, m_p2->getSprite().getPosition());
    m_fish[2]->update(dt, m_p3->getSprite().getPosition());
    m_fish[3]->update(dt, m_p4->getSprite().getPosition());

    for(auto& enemy : m_groundEnemies)
        enemy->update(dt);

    if(m_level == "jungle")
        m_beeManager->update(dt, m_hud, m_p1, m_p2, m_p3, m_p4, m_spawnZones);

    ////////////////////////////////////
    //update bullet sprites
    //for each player
    ////////////////////////////////////
    if(m_p1->getBullets().size() > 0)
    {
        for(auto& bullet : m_p1->getBullets())
        {
            bullet.update();
        }
    }

    if(m_p2->getBullets().size() > 0)
    {
        for(auto& bullet : m_p2->getBullets())
        {
            bullet.update();
        }
    }

    if(m_p3->getBullets().size() > 0)
    {
        for(auto& bullet : m_p2->getBullets())
        {
            bullet.update();
        }
    }

    if(m_p4->getBullets().size() > 0)
    {
        for(auto& bullet : m_p3->getBullets())
        {
            bullet.update();
        }
    }
}

void Arena::renderHUD()
{
    //gui updates
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_SDLWindow);
    ImGui::NewFrame();

    m_hud->update(requestPause());

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Arena::render(pk::GLStates& states)
{
    const glm::vec2 scale = pk::Game::getScalingFactor();

    m_window->draw(m_backgroundSprite, states);

    for(auto& thwomp : m_thwomps)
        m_window->draw(thwomp->getSprite(), states);

    for(auto& platform : m_movingPlatforms)
        m_window->draw(platform->getSprite(), states);

    for(auto& fish : m_fish)
        m_window->draw(fish->getSprite(), states);

    for(auto& enemy : m_groundEnemies)
        m_window->draw(enemy->getSprite(), states);

    m_window->draw(m_p1->getSprite(), states);
    m_window->draw(m_p2->getSprite(), states);
    m_window->draw(m_p3->getSprite(), states);
    m_window->draw(m_p4->getSprite(), states);

    ////////////////////////////////////
    //draw bullet sprites
    //for each player
    ////////////////////////////////////
    if(m_p1->getBullets().size() > 0)
    {
        for(auto& bullet : m_p1->getBullets())
        {
            m_window->draw(bullet.getSprite(), states);
        }
    }

    if(m_p2->getBullets().size() > 0)
    {
        for(auto& bullet : m_p2->getBullets())
        {
            m_window->draw(bullet.getSprite(), states);
        }
    }

    if(m_p3->getBullets().size() > 0)
    {
        for(auto& bullet : m_p2->getBullets())
        {
            m_window->draw(bullet.getSprite(), states);
        }
    }

    if(m_p4->getBullets().size() > 0)
    {
        for(auto& bullet : m_p3->getBullets())
        {
            m_window->draw(bullet.getSprite(), states);
        }
    }

    if(m_level == "jungle")
        m_beeManager->render(states);

    if(requestPause())
    {
        m_window->draw(m_controllerMapping, states);
    }
}
