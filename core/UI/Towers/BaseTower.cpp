#include <GL/gl.h>
#include <GL/glu.h>
#include "BaseTower.h"
#include "../Helpers.h"

using namespace core;

BaseTower::BaseTower() {
    this->size.height=GameMap::instance.cell_height;
    this->size.width=GameMap::instance.cell_width;
    this->m_radius=GameMap::instance.cell_width*3;
    angle=0;

    gun_vector.x=this->size.width*4;
    gun_vector.y=0;
    gun_vector.z=ZCoord+1;
}

BaseTower::BaseTower(const BaseTower& orig) {
}

BaseTower::~BaseTower() {
}

int BaseTower::getRadius()const{
    return m_radius;
}

void BaseTower::setRadius(int newRadius){
    m_radius=newRadius;
}

void BaseTower::updatePosition(){
    position=GameMap::instance.Point2Position(point);
}

void BaseTower::draw()const{
    
    if(isSelected){
        glColor3ub(255,100,255);

        core::drawCircle(position.x+this->size.width/2,
                position.y+this->size.height/2,
                ZCoord,
                m_radius,
                50);
    }
    
    glLoadName(id);
    glBegin(GL_POLYGON);
    glColor3ub(255,100,4);
    glVertex3d(position.x,
            position.y,
            ZCoord);
    glVertex3d(position.x,
            position.y+this->size.height,
            ZCoord);
    glVertex3d(position.x+this->size.width,position.y+this->size.height, ZCoord);
    glVertex3d(position.x+this->size.width,position.y, ZCoord);
    glEnd();

    glPushMatrix();
    auto tw=getVector();
        glTranslated(tw.x+size.width/2, tw.y+size.height/2, tw.z);
        glRotated(angle, 0, 0, 1);
    glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex3d(0, 0, gun_vector.z);
        glVertex3d(gun_vector.x/8, gun_vector.y, gun_vector.z);
    glEnd();
    glPopMatrix();
    glLoadIdentity();
}