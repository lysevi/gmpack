/* 
 * File:   TicTacGameState.h
 * Author: lsv
 *
 * Created on 5 декабря 2014 г., 21:11
 */

#pragma once

#include <AppState.h>

class TicTacGameState : public AppState {
public:
    TicTacGameState();
public:
    void OnActivate();
    void OnDeactivate();
    void OnLoop();
    void OnRender(SDL_Surface* Surf_Display);
};

