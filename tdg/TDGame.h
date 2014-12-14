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
const int map_width=20;
const int map_height=20;
const int unit_move_time=500;
class TDGame: public core::AppState  {
    typedef std::list<std::shared_ptr<core::BaseTower>> TowerList;
    typedef std::list<std::shared_ptr<core::BaseUnit>> UnitList;
    int m_width;         // ширина и высота окна
    int m_height;
    int m_map_ui_width;  // ширина и высота карты на окне
    int m_map_ui_height;
    UnitList  m_units;
    TowerList m_towers;

    int m_cell_height;
    int m_cell_width;
    Uint32 curTime;
public:
    TDGame(int width, int height, int map_ui_width, int map_ui_height);
    virtual ~TDGame();

    void OnActivate();
    void OnDeactivate();
    void OnLoop();
    void OnRender();
    void OnLButtonDown(int mX, int mY);
    void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
private:
    void generateUnits();
};

