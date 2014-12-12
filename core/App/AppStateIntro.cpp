/* 
 * File:   AppStateIntro.cpp
 * Author: lsv
 * 
 * Created on 5 декабря 2014 г., 20:20
 */

#include "AppStateIntro.h"
#include "AppStateManager.h"
#include "../Utils/ProcessLogger.h"
using namespace core;
AppStateIntro::AppStateIntro(const std::string FileName, uint _time) {
    Surf_Logo = NULL;
    m_FileName = FileName;
    m_time=_time;
}

void AppStateIntro::OnActivate() {
    Surf_Logo = Surface::OnLoad(m_FileName);

    StartTime = SDL_GetTicks();
}

void AppStateIntro::OnDeactivate() {
    if (Surf_Logo) {
        SDL_FreeSurface(Surf_Logo);
        Surf_Logo = NULL;
    }
}

void AppStateIntro::OnLoop() {
    if (StartTime + m_time < SDL_GetTicks()) {
        AppStateManager::SetActiveAppState(APPSTATE_GAME);
    }
}

void AppStateIntro::OnRender() {
    /*if (Surf_Logo) {
        //logger << "intro OnRender" << endl;
        Surface::OnDraw(Surf_Display, Surf_Logo, 0, 0);
    } else {
        logger << "intro OnRender fail" << endl;
    }*/
}

