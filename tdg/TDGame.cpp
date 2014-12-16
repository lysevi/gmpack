/* 
 * File:   TDGame.cpp
 * Author: lsv
 * 
 * Created on 10 декабря 2014 г., 21:59
 */

#include "TDGame.h"
#include <Utils/ProcessLogger.h>
#include <Math/Vector3d.h>
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
}

void TDGame::OnDeactivate() {
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
    for (auto punit:m_units) {
        punit->draw();
    }

    for (auto pt:m_towers) {
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
    
    TowerList::value_type selectedTower;
    for (auto&ptower:m_towers) {
        if ((ptower->coord.x < wx) && (ptower->coord.y < wy)
                && (ptower->coord.y + ptower->size.height > wy)
                && (ptower->coord.x + ptower->size.width > wx)) {
            ptower->isSelected = !ptower->isSelected;
            selectedTower=ptower;
            break;
        }
    }
    OnMapClick(p.line,p.column,selectedTower.get());
    for (auto&p:m_units) {
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

void TDGame::generateUnits() {
    auto sunit = std::make_shared<core::SimpleUnit>();
    sunit->point = {0, 0};
    m_units.push_back(sunit);

    auto stower = std::make_shared<core::BaseTower>();
    stower->point.column = 2;
    stower->point.line = 1;
    stower->id_of_target=sunit->id;
    m_towers.push_back(stower);

    auto stower2 = std::make_shared<core::BaseTower>();
    stower2->point.column = 2;
    stower2->point.line = 5;
    stower2->id_of_target=sunit->id;
    m_towers.push_back(stower2);

    auto stower3 = std::make_shared<core::BaseTower>();
    stower3->point.column = 2;
    stower3->point.line = 10;
    stower3->id_of_target=sunit->id;
    m_towers.push_back(stower3);

    auto stower4 = std::make_shared<core::BaseTower>();
    stower4->point.column = 2;
    stower4->point.line = 15;
    stower4->id_of_target=sunit->id;
    m_towers.push_back(stower4);
}

core::PtrUnit TDGame::getUnitById(const UnitList&ul, int id){
    auto res=std::find_if(ul.cbegin(),ul.cend(),
                    [id](const core::PtrUnit pu)
                    {return pu->id==id;});
    if(res==ul.cend())
        return nullptr;
    else
        return *res;
}

void TDGame::moveUnits() {
    UnitList removedUnits;
    for (auto&punit:m_units) {
        auto res = std::find_if(core::GameMap::instance.map_way.cbegin(),
                core::GameMap::instance.map_way.cend(),
                [punit](const core::Point & p) {
                    return p.line == punit->point.line && p.column == punit->point.column;
                });
        res++;
        if (res != core::GameMap::instance.map_way.cend()) {
            punit->point.line = res->line;
            punit->point.column = res->column;
            punit->coord=core::GameMap::instance.Point2Coord(punit->point);

        } else {
            removedUnits.push_back(punit);
        }
    }
    for (auto p:removedUnits) {
        m_units.remove(p);
    }
}

void TDGame::calcNewTargets(){
    for(auto pt:m_towers){
        UnitList closesUnit;// досягаемые враги.
        core::Coord towerCoord=pt->coord;
        for(auto pu:m_units){
            core::Coord unit_coord=core::GameMap::instance.Point2Coord(pu->point);
            if(core::Coord::distance(towerCoord,unit_coord)<pt->getRadius()){
                closesUnit.push_back(pu);
            }
        }
        if(closesUnit.size()==0){
            pt->id_of_target=-1;
            continue;
        }
        if(pt->id_of_target==-1){
            pt->id_of_target=closesUnit.front()->id;
        }
        // если уже целимся в кого то.
        if(pt->id_of_target!=-1){
            // проверяем, что он все еще досягаем.
            auto id_of_target=pt->id_of_target;
            auto res=getUnitById(closesUnit,id_of_target);
            // если все еще досягаем
            if(res!=nullptr){
                continue;
            }else{
                pt->id_of_target=closesUnit.front()->id;
            }
        }
    }
}

void TDGame::calcTowersAngles(){
    
    for(auto &pt:m_towers){
        if(pt->id_of_target==-1){
            continue;
        }

        auto pu=getUnitById(m_units,pt->id_of_target);

        core::Vector3d gunface_orig=pt->gun_vector;
	core::Vector3d gunface=gunface_orig;
	auto gun_pos = pt->getLogicalCenter();
        auto hero_pos = pu->getLogicalCenter();
	gunface.norm();
	auto guard_to_her = hero_pos - gun_pos;
	guard_to_her.norm();
	float angle = acosf(dot(gunface, guard_to_her))*(180/3.14159265358979323846264338327);
        
        if ((pt->getVector().y>pu->getVector().y))
            angle = -angle;

        pt->angle=angle;
    }

}

void TDGame::OnMapClick(int line,int column, core::Object3d*obj){
    if(obj!=nullptr)
        return;
    
    if(core::GameMap::instance(line,column)!= core::CellType::ROCK){
        core::GameMap::instance.setValue(line,column,core::CellType::ROCK);
        bool flag=core::GameMap::instance.checkNewPath();
        

        if(!flag){
            core::GameMap::instance.setValue(line,column,core::CellType::GROUND);
            return;
        }
        
        auto stower = std::make_shared<core::BaseTower>();
        stower->point.column = column;
        stower->point.line = line;
        m_towers.push_back(stower);
        core::GameMap::instance.updateWay();
    }
}