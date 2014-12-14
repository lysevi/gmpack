/* 
 * File:   Coord.cpp
 * Author: lsv
 * 
 * Created on 8 Июль 2013 г., 21:56
 */

#include "Coord.h"
#include <cmath>

namespace core {

    Coord::Coord(int _x, int _y) {
        x = _x;
        y = _y;
    }

    Coord::Coord() {
        x = 0;
        y = 0;
    }

    float Coord::distance(const Coord&left,const Coord&right){
        return sqrt(pow(left.x-right.x,2)+pow(left.y-right.y,2));
    }
}