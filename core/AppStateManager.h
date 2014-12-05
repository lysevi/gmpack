/* 
 * File:   AppStateManager.h
 * Author: lsv
 *
 * Created on 5 декабря 2014 г., 20:16
 */

#pragma once

#include "AppState.h"
#include <map>

enum {
    APPSTATE_NONE = 0,
    APPSTATE_INTRO,
    APPSTATE_GAME,
    APPSTATE_SCORE
};

class AppStateManager {
private:
    static AppState* ActiveAppState;
    static std::map<int, AppState*> m_states;
public:
    static void OnEvent(SDL_Event* Event);
    static void OnLoop();
    static void OnRender(SDL_Surface* Surf_Display);

public:
    static void SetActiveAppState(int AppStateID);
    static AppState* GetActiveAppState();
    static void AddState(int type, AppState*st);
private:

};
