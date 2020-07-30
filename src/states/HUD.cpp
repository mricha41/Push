#include "states/HUD.hpp"

#include "core/Game.hpp"

using namespace pk;

HUD::HUD(char* title, unsigned int numberOfPlayers)
{
    m_title = title;
    //initialize the scores
    for(int i=0; i<numberOfPlayers; ++i)
        m_deaths.push_back(0);
}

HUD::~HUD()
{

}

void HUD::update(bool open)
{
    IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear ImGui context. Refer to ImGui examples app!");

    //ImGui typically relies on persistent state
    //across function calls, hence all the static variables
    static bool no_titlebar = false;
    static bool no_scrollbar = false;
    static bool no_menu = false;
    static bool no_move = false;
    static bool no_resize = false;
    static bool no_collapse = false;
    static bool no_close = false;
    static bool no_nav = false;
    static bool no_background = false;
    static bool no_bring_to_front = false;

    ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if (no_close)           open = NULL;

    if(open)
    {
        ImGui::Begin(m_title, &open, window_flags);

        unsigned int n = 1;
        for(auto& i : m_deaths)
        {
            ImGui::Text("Player %i: %i", n, i);
            ++n;
        }

        ImGui::SetWindowSize(ImVec2(m_size.x, m_size.y));
        ImGui::SetWindowPos(ImVec2(m_position.x - m_size.x/2.f, m_position.y - m_size.y/1.25f));

        ImGui::End();
    }
}
