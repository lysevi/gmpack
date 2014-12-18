#include "GameMap.h"
#include "../Utils/PathFinder.h"
#include "../Utils/Exception.h"
#include "../Utils/Coord.h"
#include "Units/UnitManager.h"
#include "Helpers.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <algorithm>
#include <assert.h>

using namespace core;

GameMap GameMap::instance;

void GameMap::setLogicalSize(int width, int height) {
    m_logigal_height = height;
    m_logigal_width = width;
}

void GameMap::setUiSize(int width, int height) {
    m_ui_height = height;
    m_ui_width = width;
}

void GameMap::generateMap(){
    cell_height = (m_ui_height / m_logigal_height);
    cell_width = (m_ui_width / m_logigal_width);

    m_gamemap = new core::map_cell*[m_logigal_height];
    for (int i = 0; i < m_logigal_height; ++i) {
        m_gamemap[i] = new core::map_cell[m_logigal_width];
    }

    for (int i = 0; i < m_logigal_height - 1; ++i) {
        m_gamemap[i][1] = core::CellType::ROCK;
    }
    
    startPoint = {0, 0};
    endPoint = {0, m_logigal_width - 1};
}

void GameMap::draw()const{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // рисуем сетку
    glBegin(GL_LINES);
    glColor3ub(47, 54, 152);
    
    // очерчиваем поле линиями (квадрат)
    glVertex3f(0, 0, 0);
    glVertex3f(m_ui_width, 0, 0);

    glVertex3f(0, m_ui_height, 0);
    glVertex3f(m_ui_width, m_ui_height, 0);

    glVertex3f(m_ui_width, m_ui_height, 0);
    glVertex3f(m_ui_width, 0, 0);

    for (int i = 0; i < m_logigal_height; ++i) {

        auto y = i*cell_height;

        glVertex3f(0, y, 0);
        glVertex3f(m_ui_width, y, 0);

        for (int j = 0; j < m_logigal_width; ++j) {
            auto x = j*cell_width;

            glVertex3f(x, y, 0);
            glVertex3f(x, m_ui_height, 0);
        }
    }
    glEnd();

    // рисуем ячейки - скалы.
    for (int i = 0; i < m_logigal_height; ++i) {
        auto y = i*cell_height;

        for (int j = 0; j < m_logigal_width; ++j) {

            auto x = j*cell_width;
            if (m_gamemap[i][j] == core::CellType::ROCK) {
                glColor3ub(47, 54, 152);
                drawQUAD(x, y,0, cell_width, cell_height);
            }

            if ((startPoint.line == i && startPoint.column == j) ||
                    (endPoint.line == i && endPoint.column == j)) {

                glColor3ub(147, 154, 152);
                drawQUAD(x, y,0, cell_width, cell_height);
            }

            for(auto pu:core::UnitManager::get()->units){
                if(std::find_if(pu->path.cbegin(), pu->path.cend(),
                    [i,j](const Point&p){return p.line==i && p.column==j;})!= pu->path.cend()) {
                        glColor3ub(147, 154, 152);
                        drawQUAD(x, y,0, cell_width, cell_height);
                    }
            }
        }
    }
}

core::Coord GameMap::Point2Coord(const core::Point&point)const{
    core::Coord result;
    result.x=point.column*cell_width;
    result.y=point.line*cell_height;
    return result;
}

Point GameMap::Coord2Point(const core::Coord&c)const{
    Point result;
    result.line=c.y/cell_height;
    result.column=c.x/cell_width;
    return result;
}

CellType GameMap::operator()(int line,int column)const{
    return m_gamemap[line][column];
}

void GameMap::setValue(int line,int column,CellType v){
    m_gamemap[line][column]=v;
}

core::PointList GameMap::getWay(core::Point _startPoint){
    return  core::PathFinder::astar_flow(m_gamemap,
            m_logigal_height,
            m_logigal_width,
            _startPoint,
            endPoint);
}

void GameMap::changeCell(int line,int column, CellType ctype){
    assert(line<m_logigal_height);
    assert(column<m_logigal_width);

    m_gamemap[line][column]=ctype;
}