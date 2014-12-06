/* 
 * File:   TetraGameState.h
 * Author: lsv
 *
 * Created on 6 декабря 2014 г., 16:57
 */

#pragma once

#include <AppState.h>

const int map_width=10;
const int map_height=20;

class TetraGameState: public AppState {
    char m_map[map_height][map_width];
public:
    TetraGameState();
    void OnActivate();
    void OnDeactivate();
    void OnLoop();
    void OnRender(SDL_Surface* Surf_Display);
};

