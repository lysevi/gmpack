/* 
 * File:   Health.cpp
 * Author: lsv
 * 
 * Created on 8 Июль 2013 г., 21:34
 */

#include "Health.h"

namespace core {

    Health::Health() {
        curHealth = maxHealth = 0;
    }

    Health::Health(int _maxHealth, int _curHealth) {
        maxHealth = _maxHealth;
        curHealth = _curHealth;
    }

    Health::Health(const Health& orig) {
        maxHealth = orig.maxHealth;
        curHealth = orig.curHealth;
    }
}