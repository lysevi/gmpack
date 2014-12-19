
#pragma once

#include "../Object3d.h"
#include <memory>
namespace core {
    class BaseTower;
    typedef std::shared_ptr<BaseTower> PtrTower;
    
    class BaseTower : public Object3d {
    public:
        BaseTower();
        BaseTower(const BaseTower& orig);
        virtual ~BaseTower();
        void draw()const;
        int getRadius()const;
        void setRadius(int newRadius);
        void updatePosition();
    public:
        float angle;
        int   id_of_target; //id юнита, в который стреляем. -1 если такого нет.
        Vector3d gun_vector; // куда повернут ствол по умолчанию
    private:
        int m_radius;

    };
}