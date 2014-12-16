#include "GameMap.h"
#include "../Utils/PathFinder.h"
#include "../Utils/Exception.h"
#include "../Utils/Coord.h"
#include "Helpers.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <algorithm>

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

    map_way = core::PathFinder::astar_flow(m_gamemap,
            m_logigal_height,
            m_logigal_width,
            startPoint,
            endPoint);
    if (map_way.size() == 0) {
        throw core::Exception::CreateAndLog(POSITION, " way not found");
    }
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

            if (std::find_if(map_way.cbegin(), map_way.cend(),
                    [i,j](const Point&p){return p.line==i && p.column==j;})!= map_way.cend()) {
                glColor3ub(147, 154, 152);
                drawQUAD(x, y,0, cell_width, cell_height);
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

void GameMap::updateWay(){
    map_way = core::PathFinder::astar_flow(m_gamemap,
            m_logigal_height,
            m_logigal_width,
            startPoint,
            endPoint);
}

bool GameMap::checkNewPath(){
    auto newway = core::PathFinder::astar_flow(m_gamemap,
            m_logigal_height,
            m_logigal_width,
            startPoint,
            endPoint);
    if (newway.size() == 0) {
        return false;
    }else{
        return true;
    }
}
