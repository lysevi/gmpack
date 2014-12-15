/* 
 * File:   BaseUnit.cpp
 * Author: lsv
 * 
 * Created on 13 декабря 2014 г., 9:17
 */

#include "BaseUnit.h"
using namespace core;

BaseUnit::BaseUnit() {
    size.height=core::GameMap::instance.cell_height;
    size.width=core::GameMap::instance.cell_width;
}

BaseUnit::BaseUnit(const BaseUnit& orig) {
}

BaseUnit::~BaseUnit() {
}

void BaseUnit::draw()const{
}
