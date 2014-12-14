#include <GL/gl.h>

#include "SimpleUnit.h"

using namespace core;

SimpleUnit::SimpleUnit() {
    size.height=core::GameMap::instance.cell_height;
    size.width=core::GameMap::instance.cell_width;
}

SimpleUnit::SimpleUnit(const SimpleUnit& orig) {
}

SimpleUnit::~SimpleUnit() {
}

void SimpleUnit::draw()const{
    if(isSelected)
        logger<<"isSelected\n";
    coord=core::GameMap::instance.Point2Coord(point);
    glBegin(GL_TRIANGLES);
    glColor3ub(255,10,255);
    glVertex3i(coord.x,coord.y,ZCoord);
    glVertex3i(coord.x+core::GameMap::instance.cell_width,coord.y,ZCoord);
    glVertex3i(coord.x+core::GameMap::instance.cell_width/2,
            coord.y+core::GameMap::instance.cell_height,ZCoord);
    glEnd();
}