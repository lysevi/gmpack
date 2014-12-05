#include <iostream>
#include <utility>
#include <stdexcept>

#include <SDL/SDL.h>

#include "Event.h"
#include "Animation.h"
#include "Application.h"
#include "AppStateManager.h"
#include "Surface.h"

Application::Application(int width, int height) {
    Surf_Display = NULL;
    Running = true;
    m_width = width;
    m_height = height;
}

int Application::OnExecute() {
    if (OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while (Running) {
        while (SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

bool Application::OnInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if ((Surf_Display = SDL_SetVideoMode(m_width, m_height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
    std::cerr << "Init video mode done." << std::endl;

    AppStateManager::SetActiveAppState(APPSTATE_INTRO);

    std::cerr << "OnInit() done." << std::endl;
    return true;
}

void Application::OnEvent(SDL_Event* Event) {
    Event::OnEvent(Event);

    AppStateManager::OnEvent(Event);
}

void Application::OnExit() {
    Running = false;
}

void Application::OnLoop() {
    AppStateManager::OnLoop();
}

void Application::OnRender() {
    AppStateManager::OnRender(Surf_Display);
    SDL_Flip(Surf_Display);
}

void Application::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
    std::cerr << "mx=" << mX << " mY" << mY
            << " relX" << relX << " relY" << relY
            << " left" << Left << " Right" << Right << " Midle" << Middle
            << std::endl;
}

void Application::OnLButtonDown(int mX, int mY) {
}

void Application::OnRButtonDown(int mX, int mY) {
}

void Application::OnCleanup() {
    AppStateManager::SetActiveAppState(APPSTATE_NONE);
    SDL_FreeSurface(Surf_Display);
    SDL_Quit();
}
