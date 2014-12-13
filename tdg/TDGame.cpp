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

TDGame::TDGame(int width, int height,int map_ui_width, int map_ui_height) {
    m_width=width;
    m_height=height;
    m_map_ui_height=map_ui_height;
    m_map_ui_width=map_ui_width;

    m_startPoint={0,0};
    m_endPoint={map_width-1,map_height-1};
    for (int i = 0; i < map_height - 1; ++i)
        m_gamemap[i][1] = core::CellType::ROCK;
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
    drawMap();
}

void TDGame::drawMap() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_LINES);
    glColor3ub(47, 54, 152);
    glVertex3f(0, 0, 0);
    glVertex3f(m_map_ui_width, 0, 0);

    glVertex3f(0, m_map_ui_height, 0);
    glVertex3f(m_map_ui_width, m_map_ui_height, 0);

    glVertex3f(m_map_ui_width, m_map_ui_height, 0);
    glVertex3f(m_map_ui_width, 0, 0);

    for (int i = 0; i < map_height; ++i) {
        auto cell_height = (m_map_ui_height / map_height);
        auto y = i*cell_height;

        glVertex3f(0, y, 0);
        glVertex3f(m_map_ui_width, y, 0);

        for (int j = 0; j < map_width; ++j) {
            auto cell_width = (m_map_ui_width / map_width);
            auto x = j*cell_width;

            glVertex3f(x, y, 0);
            glVertex3f(x, m_map_ui_height, 0);
        }
    }
    glEnd();
    
    for (int i = 0; i < map_height; ++i) {
        auto cell_height = (m_map_ui_height / map_height);
        auto y = i*cell_height;

        for (int j = 0; j < map_width; ++j) {
            auto cell_width = (m_map_ui_width / map_width);

            auto x = j*cell_width;
            if (m_gamemap[i][j] == core::CellType::ROCK) {
                glColor3ub(47, 54, 152);
                drawQUAD(x,y,cell_width,cell_height);
            }

            if((m_startPoint.line==i && m_endPoint.column==j)||
                    (m_startPoint.line==i && m_startPoint.column==j)){

                glColor3ub(147, 154, 152);
                drawQUAD(x,y,cell_width,cell_height);
            }
        }
    }
}

void TDGame::drawQUAD(int x, int y, int width, int height) {
    glBegin(GL_QUADS);
    glVertex3d(x, y, 0);
    glVertex3d(x + width, y, 0);

    glVertex3d(x + width, y + height, 0);
    glVertex3d(x, y + height, 0);

    glVertex3d(x, y + height, 0);
    glVertex3d(x, y, 0);

    glVertex3d(x + width, y, 0);
    glVertex3d(x + width, y + height, 0);
    glEnd();
}