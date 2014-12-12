/* 
 * File:   TDGame.h
 * Author: lsv
 *
 * Created on 10 декабря 2014 г., 21:59
 */

#pragma once
#include <App/AppState.h>
#include <Utils/GameMap.h>
const int map_width=20;
const int map_height=20;

class TDGame: public core::AppState  {
    core::map_cell m_gamemap[map_height][map_width];
    int m_width;
    int m_height;
public:
    TDGame(int width, int height);
    virtual ~TDGame();

    void OnActivate();
    void OnDeactivate();
    void OnLoop();
    void OnRender();
private:
    void drawMap();
};

