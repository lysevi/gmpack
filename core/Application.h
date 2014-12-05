
#pragma once 

#include "Event.h"
#include <string>

class Application : public Event {
private:
    bool Running;

    SDL_Surface* Surf_Display;
    int m_width;
    int m_height;
public:
    Application(int width, int height);

    int OnExecute();

public:

    bool OnInit();

    void OnExit();

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender();

    void OnCleanup();

    void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
    void OnLButtonDown(int mX, int mY);
    void OnRButtonDown(int mX, int mY);
private:
    SDL_Surface* loadImage(const std::string fName);
};
