
#pragma once

#include "BaseBullet.h"
#include <list>

namespace core {
    typedef std::list<core::PtrBullet> BulletList;

    class BulletManager {
    public:
        static BulletManager* get();
        static void start();
        static void stop();
        virtual ~BulletManager();
        void append(core::PtrBullet punit);
        void onLoop();
        void draw();
        BulletList bullets;
    private:
        BulletManager();
        BulletManager(const BulletManager& orig) = delete;
    };

}