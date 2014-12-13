/* 
 * File:   TDGame.cpp
 * Author: lsv
 * 
 * Created on 10 декабря 2014 г., 21:59
 */

#include "TDGame.h"
#include <Utils/ProcessLogger.h>
#include <GL/gl.h> // Библиотека OpenGL
#include <GL/glu.h> // Библиотека GLU
#include <algorithm>

TDGame::TDGame(int width, int height, int map_ui_width, int map_ui_height) {
    m_width = width;
    m_height = height;
    m_map_ui_height = map_ui_height;
    m_map_ui_width = map_ui_width;

    core::GameMap::instance.setLogicalSize(map_width,map_height);
    core::GameMap::instance.setUiSize(map_ui_width,map_ui_height);
    core::GameMap::instance.generateMap();
    
    generateUnits();
}

TDGame::~TDGame() {
}

void TDGame::OnActivate() {
}

void TDGame::OnDeactivate() {
}

void TDGame::OnLoop() {
}

void TDGame::OnRender() {
    core::GameMap::instance.draw();
    for (auto punit:m_units) {
        punit->draw();
    }
}



void TDGame::generateUnits() {
    auto sunit = std::make_shared<core::SimpleUnit>();
    sunit->point={0,0};
    m_units.push_back(sunit);
}