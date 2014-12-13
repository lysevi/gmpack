/* 
 * File:   TDGame.h
 * Author: lsv
 *
 * Created on 10 декабря 2014 г., 21:59
 */

#pragma once
#include <App/AppState.h>
#include <Utils/GameMap.h>
#include <Utils/PathFinder.h>
const int map_width=20;
const int map_height=20;

class TDGame: public core::AppState  {
    core::map_cell m_gamemap[map_height][map_width];
    core::PathFinder::Point m_startPoint;
    core::PathFinder::Point m_endPoint;
    int m_width;         // ширина и высота окна
    int m_height;
    int m_map_ui_width;  // ширина и высота карты на окне
    int m_map_ui_height;
public:
    TDGame(int width, int height, int map_ui_width, int map_ui_height);
    virtual ~TDGame();

    void OnActivate();
    void OnDeactivate();
    void OnLoop();
    void OnRender();
private:
    void drawMap();
    void drawQUAD(int x,int y, int width, int height);
};

