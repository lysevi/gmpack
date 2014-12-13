
#pragma once

#include "../Object3d.h"
namespace core {
    class BaseTower : public Object3d {
    public:
        BaseTower();
        BaseTower(const BaseTower& orig);
        virtual ~BaseTower();
        void draw()const;
    private:

    };
}