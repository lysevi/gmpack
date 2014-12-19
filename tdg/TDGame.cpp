/* 
 * File:   TDGame.cpp
 * Author: lsv
 * 
 * Created on 10 декабря 2014 г., 21:59
 */

#include "TDGame.h"
#include "UI/Towers/TowerManager.h"
#include <Utils/ProcessLogger.h>
#include <Math/Vector3d.h>
#include <UI/Units/UnitManager.h>
#include <GL/gl.h> // Библиотека OpenGL
#include <GL/glu.h> // Библиотека GLU
#include <algorithm>
#include <cmath>

TDGame::TDGame(int width, int height, int map_ui_width, int map_ui_height) {
    m_width = width;
    m_height = height;
    m_map_ui_height = map_ui_height;
    m_map_ui_width = map_ui_width;

    core::GameMap::instance.setLogicalSize(map_width, map_height);
    core::GameMap::instance.setUiSize(map_ui_width, map_ui_height);
    core::GameMap::instance.generateMap();

    generateUnits();
}

TDGame::~TDGame() {
}

void TDGame::OnActivate() {
    core::ProcessLogger::start();
    core::UnitManager::start();
    core::TowerManager::start();
}

void TDGame::OnDeactivate() {
    core::UnitManager::stop();
    core::TowerManager::stop();
    core::ProcessLogger::stop();
}

void TDGame::OnLoop() {
    if (m_curMoveTime == 0) {
        m_curMoveTime = SDL_GetTicks();
    } else if (m_curMoveTime + unit_move_time < SDL_GetTicks()) {
        m_curMoveTime = SDL_GetTicks();

        moveUnits();
        calcNewTargets();
        calcTowersAngles();
        OnRender();
    }
    
}

void TDGame::OnRender() {
    glInitNames();
    glPushName(0);
    core::GameMap::instance.draw();
    for (auto punit:core::UnitManager::get()->units) {
        punit->draw();
    }

    for (auto pt:core::TowerManager::get()->towers) {
        pt->draw();
    }
}

void TDGame::OnLButtonDown(int mX, int mY) {
    GLint viewport[4]; // параметры viewport-a.
    GLdouble projection[16]; // матрица проекции.
    GLdouble modelview[16]; // видовая матрица.
    GLdouble vx, vy, vz; // координаты курсора мыши в системе координат viewport-a.
    GLdouble wx, wy, wz; // возвращаемые мировые координаты.

    glGetIntegerv(GL_VIEWPORT, viewport); // узнаём параметры viewport-a.
    glGetDoublev(GL_PROJECTION_MATRIX, projection); // узнаём матрицу проекции.
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview); // узнаём видовую матрицу.
    // переводим оконные координаты курсора в систему координат viewport-a.
    vx = mX;
    vy = m_height - mY; // где height - текущая высота окна.

    // вычисляем ближний конец селектирующего отрезка.
    vz = -1;
    gluUnProject(vx, vy, vz, modelview, projection, viewport, &wx, &wy, &wz);

    core::Coord coord{(int)wx,(int)wy};
    auto p=core::GameMap::instance.Coord2Point(coord);
    
    core::TowerList::value_type selectedTower;
    for (auto&ptower:core::TowerManager::get()->towers) {
        if ((ptower->coord.x < wx) && (ptower->coord.y < wy)
                && (ptower->coord.y + ptower->size.height > wy)
                && (ptower->coord.x + ptower->size.width > wx)) {
            ptower->isSelected = !ptower->isSelected;
            selectedTower=ptower;
            break;
        }
    }
    OnMapClick(p.line,p.column,selectedTower.get());
    for (auto&p:core::UnitManager::get()->units) {
        if ((p->coord.x < wx) && (p->coord.y < wy)
                && (p->coord.y + p->size.height > wy)
                && (p->coord.x + p->size.width > wx)) {
            p->isSelected = !p->isSelected;
        }
    }

    OnRender();
}

void TDGame::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {

}

void TDGame::placeTower(int line,int column, core::PtrTower tower){
    tower->point.column = column;
    tower->point.line = line;
    tower->updateCoord();
    core::TowerManager::get()->towers.push_back(tower);
    core::GameMap::instance.changeCell(line,column,core::CellType::ROCK);
}

void TDGame::generateUnits() {
    auto sunit = std::make_shared<core::SimpleUnit>();
    sunit->point = {0, 0};
    core::UnitManager::get()->append(sunit);

    auto stower = std::make_shared<core::BaseTower>();
    stower->id_of_target=sunit->id;
    placeTower(1, 2,stower);

    auto stower2 = std::make_shared<core::BaseTower>();
    stower2->id_of_target=sunit->id;
    placeTower(5, 2,stower2);

    auto stower3 = std::make_shared<core::BaseTower>();
    stower3->id_of_target=sunit->id;
    placeTower(10, 2,stower3);

    auto stower4 = std::make_shared<core::BaseTower>();
    
    stower4->id_of_target=sunit->id;
    placeTower(15, 2,stower4);
}

void TDGame::moveUnits() {
    core::UnitManager::get()->nextStep();
}

void TDGame::calcNewTargets(){
    core::TowerManager::get()->calcNewTargets();
}

void TDGame::calcTowersAngles(){
    core::TowerManager::get()->calcTowersAngles();
}

void TDGame::OnMapClick(int line,int column, core::Object3d*obj){
    if(obj!=nullptr)
        return;
    
    if(core::GameMap::instance(line,column)!= core::CellType::ROCK){
        core::GameMap::instance.setValue(line,column,core::CellType::ROCK);
        bool flag=core::UnitManager::get()->tryMakeNewWays();

        if(!flag){
            core::GameMap::instance.setValue(line,column,core::CellType::GROUND);
            core::UnitManager::get()->tryMakeNewWays();
            return;
        }
        
        auto stower = std::make_shared<core::BaseTower>();
        stower->updateCoord();
        placeTower(line,column,stower);
    }
}