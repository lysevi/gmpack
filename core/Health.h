/* 
 * File:   Health.h
 * Author: lsv
 *
 * Created on 8 Июль 2013 г., 21:34
 */

#ifndef HEALTH_H
#define	HEALTH_H

namespace core {

    struct Health {
        Health();
        Health(int maxHealth, int curHealth);
        Health(const Health& orig);

        int maxHealth;
        int curHealth;
    };
}
#endif	/* HEALTH_H */

