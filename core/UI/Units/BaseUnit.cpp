/* 
 * File:   BaseUnit.cpp
 * Author: lsv
 * 
 * Created on 13 декабря 2014 г., 9:17
 */

#include "BaseUnit.h"
using namespace core;

BaseUnit::BaseUnit() {
    size.height = core::GameMap::instance.cell_height;
    size.width = core::GameMap::instance.cell_width;
    move_speed.x = move_speed.y = 3;
    isDead=false;
}

BaseUnit::~BaseUnit() {
}

void BaseUnit::draw()const {
}

bool BaseUnit::tryFillPath() {
    auto tmplist = core::GameMap::instance.getWay(point);
    if (tmplist.size() == 0) {
        return false;
    } else {
        path = tmplist;
        return true;
    }
}

void BaseUnit::onLoop(){
    if(health.curHealth<=0){
        isDead=true;
    }else{
        isDead=false;
    }
}