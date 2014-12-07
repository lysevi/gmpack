/* 
 * File:   AppStateManager.cpp
 * Author: lsv
 * 
 * Created on 5 декабря 2014 г., 20:16
 */

#include "AppStateManager.h"
#include "ProcessLogger.h"
#include "Exception.h"
using namespace core;
AppState* AppStateManager::ActiveAppState = 0;
std::map<int, AppState*> AppStateManager::m_states;

void AppStateManager::AddState(int type, AppState*st) {
    m_states[type] = st;
}

void AppStateManager::OnEvent(SDL_Event* EventHolder) {
    if (ActiveAppState) ActiveAppState->OnEvent(EventHolder);
}

void AppStateManager::OnLoop() {
    if (ActiveAppState) ActiveAppState->OnLoop();
}

void AppStateManager::OnRender(SDL_Surface* Surf_Display) {
    if (ActiveAppState) {
        //logger << "AppStateManager::OnRender\n";
        ActiveAppState->OnRender(Surf_Display);
    }
}

void AppStateManager::SetActiveAppState(int AppStateID) {
    if (ActiveAppState) ActiveAppState->OnDeactivate();

    if (AppStateID == APPSTATE_NONE) ActiveAppState = 0;
    else {
        logger << " state=" << AppStateID << endl;
        if (m_states.find(AppStateID) != m_states.end())
            ActiveAppState = m_states[AppStateID];
        else {
            logger << " state not found" << endl;
            return;
        }
    }
    if (ActiveAppState)
        ActiveAppState->OnActivate();
    //else
    //    throw Exception::CreateAndLog(POSITION, "ActiveAppState is nullptr");
}

AppState* AppStateManager::GetActiveAppState() {
    return ActiveAppState;
}