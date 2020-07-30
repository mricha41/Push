#ifndef HUD_HPP
#define HUD_HPP

#include <vector>

#include "glm/glm.hpp"

#include "imgui/imgui.h"

namespace pk
{

class HUD
{
    private:
        HUD(){};
    public:
        HUD(char* title, unsigned int numberOfPlayers);
        virtual ~HUD();

        void setSize(glm::vec2 size){ m_size = size; };

        glm::vec2 getSize(){ return m_size; };

        void setPosition(glm::vec2 position){ m_position = position; };

        glm::vec2 getPosition(){ return m_position; };

        void increaseDeaths(int player, int amount){ m_deaths[player] += amount; };

        void setDeaths(int player, int value){ m_deaths[player] = value; };

        void update(bool open);

    private:
        char* m_title;
        glm::vec2 m_size;
        glm::vec2 m_position;
        unsigned int m_numberOfPlayers;
        std::vector<unsigned int> m_deaths;
};

}

#endif // HUD_HPP
