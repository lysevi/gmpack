
#pragma once

#include "../Object3d.h"
namespace core {
    class BaseTower : public Object3d {
    public:
        BaseTower();
        BaseTower(const BaseTower& orig);
        virtual ~BaseTower();
        void draw()const;
        int getRadius()const;
        void setRadius(int newRadius);
    public:
        float angle;
        int   id_of_target; //id юнита, в который стреляем. -1 если такого нет.
    private:
        int m_radius;

    };
}