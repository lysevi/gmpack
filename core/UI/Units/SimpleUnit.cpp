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

    glPushMatrix();

    glTranslatef(position.x,position.y,ZCoord);
    //glRotatef(-angle_on_damage,0,0,1);
    
    
    glBegin(GL_TRIANGLES);
    glColor3ub(255, 10, 255);
    glVertex3i(0, 0, 0);
    glColor3ub(255, 10, 15);
    glVertex3i(core::GameMap::instance.cell_width, 0, 0);
    glColor3ub(15, 10, 255);
    glVertex3i(core::GameMap::instance.cell_width / 2, core::GameMap::instance.cell_height, 0);
    glEnd();
    glPopMatrix();
    drawHealt();
}