
#include <SDL2/SDL_video.h>

#include <iostream>
#include <utility>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <GL/gl.h> // Библиотека OpenGL
#include <GL/glu.h> // Библиотека GLU

#include "Event.h"
#include "../UI/Animation.h"
#include "Application.h"
#include "AppStateManager.h"
#include "../Utils/ProcessLogger.h"
#include "../UI/Surface.h"
#include "../UI/FPS.h"

using namespace core;


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

    m_win = SDL_CreateWindow("tdg", 100, 100, m_width, m_height, SDL_WINDOW_OPENGL);
    if (m_win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    m_context=SDL_GL_CreateContext(m_win);
    SDL_GL_SetSwapInterval(1);
    SDL_DisableScreenSaver();
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // устанавливаем фоновый цвет на черный
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST); // включаем тест глубины
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,m_width,m_height);
    glOrtho(-10,m_width-10,-10,m_height-10,-100,100);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Сглаживание точек
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
    // Сглаживание линий
    //glEnable(GL_LINE_SMOOTH);
    //glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
    // Сглаживание полигонов
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

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
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_win);
    SDL_Quit();
}
