
#pragma once
#include "../Object3d.h"

namespace core {
    class BaseBullet;
    typedef std::shared_ptr<BaseBullet> PtrBullet;
    
    class BaseBullet : public Object3d {
    public:
        BaseBullet();
        BaseBullet(const BaseBullet& orig);
        virtual ~BaseBullet();
        void draw()const;
    public:
        int id_of_target;
        int damage;
        Vector3d speed;
    };

}