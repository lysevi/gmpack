/* 
 * File:   Object3d.cpp
 * Author: lsv
 * 
 * Created on 13 декабря 2014 г., 9:00
 */

#include "Object3d.h"

using namespace core;
uint Object3d::nextID=0;

Object3d::Object3d() {
    isSelected=false;
    id+=nextID;
    nextID+=1;
}

Object3d::Object3d(const Object3d& orig) {
}

Object3d::~Object3d() {
}

void Object3d::OnClick(){
}

Vector3d Object3d::getVector()const{
    return Vector3d(coord.x+size.width/2,coord.y+size.height/2,ZCoord);
}