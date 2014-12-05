/* 
 * File:   Coord.cpp
 * Author: lsv
 * 
 * Created on 8 Июль 2013 г., 21:56
 */

#include "Coord.h"

namespace core {

    Coord::Coord(int x, int y) {
        m_x = x;
        m_y = y;
    }

    Coord::Coord() {
        m_x = 0;
        m_y = 0;
    }

    Coord::Coord(const Coord& orig) {
        m_x = orig.m_x;
        m_y = orig.m_y;
    }

    Coord::~Coord() {
    }

    int Coord::getX()const {
        return m_x;
    }

    int Coord::setX(int x) {
        m_x = x;
    }

    int Coord::getY()const {
        return m_y;
    }

    int Coord::setY(int y) {
        m_y = y;
    }
}