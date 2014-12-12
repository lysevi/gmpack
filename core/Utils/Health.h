/* 
 * File:   Health.h
 * Author: lsv
 *
 * Created on 8 Июль 2013 г., 21:34
 */

#pragma once

namespace core {

    struct Health {
        Health();
        Health(int maxHealth, int curHealth);

        int maxHealth;
        int curHealth;
    };
}
