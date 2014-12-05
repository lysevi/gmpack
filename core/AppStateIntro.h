/* 
 * File:   AppStateIntro.h
 * Author: lsv
 *
 * Created on 5 декабря 2014 г., 20:20
 */

#pragma once

#include "AppState.h"
#include "Surface.h"

class AppStateIntro : public AppState {
private:
    SDL_Surface* Surf_Logo;
    int StartTime;
    std::string m_FileName;
public:
    AppStateIntro(const std::string FileName);
    void OnActivate();
    void OnDeactivate();
    void OnLoop();
    void OnRender(SDL_Surface* Surf_Display);
};

