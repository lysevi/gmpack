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
#include <UI/Units/SimpleUnit.h>
#include <UI/Towers/BaseTower.h>
#include <list>
#include <memory>
const int map_width=20;
const int map_height=20;

class TDGame: public core::AppState  {
    int m_width;         // ширина и высота окна
    int m_height;
    int m_map_ui_width;  // ширина и высота карты на окне
    int m_map_ui_height;
    std::list<std::shared_ptr<core::BaseUnit>>  m_units;
    std::list<std::shared_ptr<core::BaseTower>> m_towers;

    int m_cell_height;
    int m_cell_width;
public:
    TDGame(int width, int height, int map_ui_width, int map_ui_height);
    virtual ~TDGame();

    void OnActivate();
    void OnDeactivate();
    void OnLoop();
    void OnRender();
private:
    void generateUnits();
};

