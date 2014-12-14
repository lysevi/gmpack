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

void BaseTower::draw()const{
    
    if(isSelected){
        glColor3ub(255,100,255);

        core::drawCircle(coord.x+this->size.width/2,
                coord.y+this->size.height/2,
                ZCoord,
                m_radius,
                50);
    }
    coord=GameMap::instance.Point2Coord(point);
    glLoadName(id);
    glBegin(GL_POLYGON);
    glColor3ub(255,100,4);
    glVertex3d(coord.x,
            coord.y,
            ZCoord);
    glVertex3d(coord.x,
            coord.y+this->size.height,
            ZCoord);
    glVertex3d(coord.x+this->size.width,coord.y+this->size.height, ZCoord);
    glVertex3d(coord.x+this->size.width,coord.y, ZCoord);
    glEnd();

    glPushMatrix();
    glTranslated(coord.x+this->size.width/2,
            coord.y+this->size.height/2,
            ZCoord+1);
    glRotatef(angle,0,0,1);
    
    glColor3ub(255,255,255);
    core::drawQUAD(0-this->size.width/2,0,ZCoord+1,
            this->size.width/2,this->size.height/5);
    glPopMatrix();
}