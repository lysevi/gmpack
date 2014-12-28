#include <GL/gl.h>

#include "BaseBullet.h"

using namespace core;

BaseBullet::BaseBullet() {
    speed.x=speed.y=0.4;
    damage=5;
}


BaseBullet::~BaseBullet() {
}

void BaseBullet::draw()const{
    glPointSize(5);
    glBegin(GL_POINTS);
        glColor3ub(255,255,255);
        glVertex3d(position.x,position.y,position.z);
    glEnd();
}