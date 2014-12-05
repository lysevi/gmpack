/* 
 * File:   TicTacGameState.h
 * Author: lsv
 *
 * Created on 5 декабря 2014 г., 21:11
 */

#pragma once

#include <AppState.h>

enum XOTypes{
    None=0,
    X,
    O
};

class TicTacGameState : public AppState {
    SDL_Surface* m_bg;
    SDL_Surface* m_x;
    SDL_Surface* m_o;
    XOTypes  m_map[3][3];
    XOTypes  m_user;
public:
    TicTacGameState();
    XOTypes getWiner();
public:
    void OnActivate();
    void OnDeactivate();
    void OnLoop();
    void OnRender(SDL_Surface* Surf_Display);
    void OnLButtonDown(int mX, int mY);
};

