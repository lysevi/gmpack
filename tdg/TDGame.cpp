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

void TDGame::OnLButtonDown(int mX, int mY){
  GLint    viewport[4];    // параметры viewport-a.
  GLdouble projection[16]; // матрица проекции.
  GLdouble modelview[16];  // видовая матрица.
  GLdouble vx,vy,vz;       // координаты курсора мыши в системе координат viewport-a.
  GLdouble wx,wy,wz;       // возвращаемые мировые координаты.

  glGetIntegerv(GL_VIEWPORT,viewport);           // узнаём параметры viewport-a.
  glGetDoublev(GL_PROJECTION_MATRIX,projection); // узнаём матрицу проекции.
  glGetDoublev(GL_MODELVIEW_MATRIX,modelview);   // узнаём видовую матрицу.
  // переводим оконные координаты курсора в систему координат viewport-a.
  vx = mX;
  vy =m_height- mY; // где height - текущая высота окна.

  // вычисляем ближний конец селектирующего отрезка.
  vz = -1;
  gluUnProject(vx, vy, vz, modelview, projection, viewport, &wx, &wy, &wz);
  logger<<"x1="<<wx<<" y1="<<wy<<" z1"<<wz<<std::endl;


  for(auto&ptower:m_towers){
        if((ptower->coord.x<wx) && (ptower->coord.y<wy)
          && (ptower->coord.y+ptower->size.height>wy)
          && (ptower->coord.x+ptower->size.width>wy)){
            ptower->isSelected=!ptower->isSelected;
        }
    }
    OnRender();
}

void TDGame::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle){
   
}

void TDGame::generateUnits() {
    auto sunit = std::make_shared<core::SimpleUnit>();
    sunit->point={0,0};
    m_units.push_back(sunit);

    auto stower=std::make_shared<core::BaseTower>();
    stower->point.column=2;
    stower->point.line=1;

    stower->isSelected=true;
    m_towers.push_back(stower);
}