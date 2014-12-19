/* 
 * File:   TDGame.h
 * Author: lsv
 *
 * Created on 10 декабря 2014 г., 21:59
 */

#pragma once
#include <App/AppState.h>
#include <UI/GameMap.h>
#include <Utils/PathFinder.h>
#include <UI/Units/SimpleUnit.h>
#include <UI/Towers/BaseTower.h>
#include <list>
#include <memory>
const int map_width = 20;
const int map_height = 20;
const int unit_move_time = 25;

class TDGame : public core::AppState {
    int m_width; // ширина и высота окна
    int m_height;
    int m_map_ui_width; // ширина и высота карты на окне
    int m_map_ui_height;

    int m_cell_height;
    int m_cell_width;
    Uint32 m_curMoveTime;
public:
    TDGame(int width, int height, int map_ui_width, int map_ui_height);
    virtual ~TDGame();

    void OnActivate();
    void OnDeactivate();
    void OnLoop();
    void OnRender();
    void OnLButtonDown(int mX, int mY);
    void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);

    void placeTower(int line, int column, core::PtrTower tower);
private:
    void OnMapClick(int line, int column, core::Object3d*obj);
private:
    void moveUnits();
    void generateUnits();
    void calcNewTargets();
    void calcTowersAngles();

};

