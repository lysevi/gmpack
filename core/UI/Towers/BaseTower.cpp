#include <GL/gl.h>

#include "BaseTower.h"

using namespace core;

BaseTower::BaseTower() {
}

BaseTower::BaseTower(const BaseTower& orig) {
}

BaseTower::~BaseTower() {
}

void BaseTower::draw()const{
    coord=GameMap::instance.Point2Coord(point);
    glBegin(GL_POLYGON);
    glColor3ub(255,100,4);
    glVertex3d(coord.x,
            coord.y,
            ZCoord);
    glVertex3d(coord.x,
            coord.y+GameMap::instance.cell_height,
            ZCoord);
    glVertex3d(coord.x+GameMap::instance.cell_width,coord.y+GameMap::instance.cell_height, ZCoord);
    glVertex3d(coord.x+GameMap::instance.cell_width,coord.y, ZCoord);
    glEnd();
}