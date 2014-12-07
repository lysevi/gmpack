/* 
 * File:   Health.cpp
 * Author: lsv
 * 
 * Created on 8 Июль 2013 г., 21:34
 */

#include "Health.h"

namespace core {

    Health::Health() {
        curHealth = maxHealth = -1;
    }

    Health::Health(int _maxHealth, int _curHealth) {
        maxHealth = _maxHealth;
        curHealth = _curHealth;
    }
}