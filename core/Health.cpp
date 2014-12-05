/* 
 * File:   Health.cpp
 * Author: lsv
 * 
 * Created on 8 Июль 2013 г., 21:34
 */

#include "Health.h"

namespace core {

    Health::Health() {
        m_curHealth = m_maxHealth = 0;
    }

    Health::Health(int maxHealth, int curHealth) {
        m_maxHealth = maxHealth;
        m_curHealth = curHealth;
    }

    Health::Health(const Health& orig) {
        m_maxHealth = orig.m_maxHealth;
        m_curHealth = orig.m_curHealth;
    }

    Health::~Health() {
    }

    int Health::getMaxHealth()const {
        return m_maxHealth;
    }

    void Health::setMaxHealth(const int value) {
        m_maxHealth = value;
    }

    int Health::getHealth()const {
        return m_curHealth;
    }

    void Health::setHealth(const int value) {
        m_curHealth = value;
    }
}