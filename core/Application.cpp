
#include <SDL2/SDL_video.h>

#include <iostream>
#include <utility>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <GL/gl.h> // Библиотека OpenGL
#include <GL/glu.h> // Библиотека GLU

#include "Event.h"
#include "Animation.h"
#include "Application.h"
#include "AppStateManager.h"
#include "ProcessLogger.h"
#include "Surface.h"
#include "FPS.h"
#include "BaseObject.h"

using namespace core;

const int width = 640; // ширина окна
const int height = 480; // высота окна

Application::Application(int width, int height) {
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
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::cerr << "Init error" << SDL_GetError() << std::endl;
        return false;
    }

    m_win = SDL_CreateWindow("tdg", 100, 100, width, height, SDL_WINDOW_OPENGL);
    if (m_win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    SDL_GL_CreateContext(m_win);
    SDL_GL_SetSwapInterval(1);
    SDL_DisableScreenSaver();
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    /*m_ren = SDL_CreateRenderer(m_win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_ren == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }*/

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // устанавливаем фоновый цвет на черный
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST); // включаем тест глубины
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float) width / (float) height, 0.1f, 100.0f); // настраиваем трехмерную перспективу
    glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим

    std::cerr << "Init video mode done." << std::endl;


    AppStateManager::SetActiveAppState(APPSTATE_GAME);

    std::cerr << "OnInit() done." << std::endl;
    return true;
}

void Application::OnEvent(SDL_Event* Event) {
    Event::OnEvent(Event);

    AppStateManager::OnEvent(Event);
}

void Application::OnExit() {
    logger << "exit()" << std::endl;
    Running = false;
}

void Application::OnLoop() {
    FPS::FPSControl.OnLoop();
    AppStateManager::OnLoop();

    //char Buffer[255];
    //sprintf(Buffer, "FPS: %d", FPS::FPSControl.GetFPS());
    //SDL_SetWindowTitle(m_win, Buffer);
}

void Application::OnRender() {
    AppStateManager::OnRender();
    SDL_GL_SwapWindow(m_win);
    //SDL_Flip(Surf_Display);
}

void Application::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
    /*std::cerr << "mx=" << mX << " mY" << mY
            << " relX" << relX << " relY" << relY
            << " left" << Left << " Right" << Right << " Midle" << Middle
            << std::endl;*/
}


void Application::OnCleanup() {
    AppStateManager::SetActiveAppState(APPSTATE_NONE);
    core::BaseObject::checkMemoryStatus();
    SDL_Quit();
}
