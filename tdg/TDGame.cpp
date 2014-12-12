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

TDGame::TDGame(int width, int height) {
    m_width=width;
    m_height=height;
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

    //glTranslatef(0.0f, 0.0f, -7.0f); // Сдвинуть вглубь экрана

    glBegin(GL_LINES);
    glColor3ub(47, 54, 152);
    for (int i = 0; i < map_height; ++i) {
        auto cell_height = (m_height / map_height);
        auto y = i*cell_height;

        glVertex3f(0, y, 0);
        glVertex3f(640, y, 0);
        for (int j = 0; j < map_width; ++j) {
            auto cell_width = (m_width / map_width);

            auto x = j*cell_width;


            glVertex3f(x, y, 0);
            glVertex3f(x, m_width, 0);
        }
    }
    glEnd();
    
    for (int i = 0; i < map_height; ++i) {
        auto cell_height = (m_height / map_height);
        auto y = i*cell_height;

        for (int j = 0; j < map_width; ++j) {
            auto cell_width = (m_width / map_width);

            auto x = j*cell_width;
            if (m_gamemap[i][j] == core::CellType::ROCK) {
                glBegin(GL_QUADS);
                glVertex3d(x, y, 0);
                glVertex3d(x + cell_width, y, 0);

                glVertex3d(x + cell_width, y + cell_height, 0);
                glVertex3d(x, y + cell_height, 0);

                glVertex3d(x, y + cell_height, 0);
                glVertex3d(x, y, 0);

                glVertex3d(x + cell_width, y, 0);
                glVertex3d(x + cell_width, y + cell_height, 0);
                glEnd();
            }
        }
    }
}