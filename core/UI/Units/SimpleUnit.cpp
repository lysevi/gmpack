#include <GL/gl.h>

#include "SimpleUnit.h"

using namespace core;

SimpleUnit::SimpleUnit() {
    health.curHealth=health.maxHealth=100;
}

SimpleUnit::~SimpleUnit() {
}

void SimpleUnit::draw()const {
    if (isSelected)
        logger << "un" << id << " isSelected\n";
    
    glBegin(GL_TRIANGLES);
    glColor3ub(255, 10, 255);
    glVertex3i(position.x, position.y, ZCoord);
    glColor3ub(255, 10, 15);
    glVertex3i(position.x + core::GameMap::instance.cell_width, position.y, ZCoord);
    glColor3ub(15, 10, 255);
    glVertex3i(position.x + core::GameMap::instance.cell_width / 2,
            position.y + core::GameMap::instance.cell_height, ZCoord);
    glEnd();

    drawHealt();
}