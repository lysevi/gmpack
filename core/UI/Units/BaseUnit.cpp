/* 
 * File:   BaseUnit.cpp
 * Author: lsv
 * 
 * Created on 13 декабря 2014 г., 9:17
 */

#include <GL/gl.h>

#include "BaseUnit.h"
#include "../Helpers.h"

using namespace core;

BaseUnit::BaseUnit() {
    size.height = core::GameMap::instance.cell_height;
    size.width = core::GameMap::instance.cell_width;
    move_speed.x = move_speed.y = 3;
    isDead = false;
    angle_on_damage = 0;
}

BaseUnit::~BaseUnit() {
}

void BaseUnit::drawHealt()const {
    glColor4ub(255, 255, 255, 100);
    auto healt_width = core::GameMap::instance.cell_width;
    drawQUAD(position.x, position.y, ZCoord + 1, healt_width, 4);
    healt_width = (static_cast<float> (healt_width) / health.maxHealth) * health.curHealth;
    glColor4ub(255, 0, 0, 250);
    drawQUAD(position.x + 1, position.y + 1, ZCoord + 2, healt_width, 2);
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

void BaseUnit::onLoop() {
    if (health.curHealth <= 0) {
        isDead = true;
    } else {
        isDead = false;
    }
}

void BaseUnit::onDamage() {
    angle_on_damage += 5;
}