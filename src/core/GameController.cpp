#include "GameController.hpp"
#include <stdio.h>

using namespace pk;

GameController::GameController(int id)
{
    m_id = id;
    m_controller = nullptr;

    m_deadzone = 100.f;

    if(SDL_IsGameController(id))
        m_controller = SDL_GameControllerOpen(id);
    else
        printf("Index at %d is not an SDL_GameController.\n", id);

    if (m_controller == nullptr) {
        printf("Could not open SDL_GameController at index: %d\n%s\n", id, SDL_GetError());
    }

    m_name = SDL_GameControllerNameForIndex(id);
}

GameController::~GameController()
{

    if(m_controller != nullptr)
    {
        close();
    }
}

void GameController::close()
{
    SDL_GameControllerClose(m_controller);
}
