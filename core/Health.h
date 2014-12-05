/* 
 * File:   Health.h
 * Author: lsv
 *
 * Created on 8 Июль 2013 г., 21:34
 */

#ifndef HEALTH_H
#define	HEALTH_H

namespace core {

    class Health {
    public:
        Health();
        Health(int maxHealt, int curHealth);
        Health(const Health& orig);
        virtual ~Health();

        int getMaxHealth()const;
        void setMaxHealth(const int);

        int getHealth()const;
        void setHealth(const int);
    protected:
        int m_maxHealth;
        int m_curHealth;
    };
}
#endif	/* HEALTH_H */

