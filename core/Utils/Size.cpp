/* 
 * File:   Size.cpp
 * Author: lsv
 * 
 * Created on 8 Июль 2013 г., 21:56
 */

#include "Size.h"

namespace core {

    Size::Size(int x, int y) {
        width = x;
        height = y;
    }

    Size::Size() {
        width = -1;
        height = -1;
    }
}