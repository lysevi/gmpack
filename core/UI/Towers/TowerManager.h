
#pragma once

#include "BaseTower.h"
#include <list>

namespace core {
    typedef std::list<core::PtrTower> TowerList;

    class TowerManager {
    public:
        static TowerManager* get();
        static void start();
        static void stop();
        virtual ~TowerManager();
        core::PtrTower getTowerById(int id);
        void append(core::PtrTower punit);
        void calcNewTargets();
        void calcTowersAngles();
        void onLoop();
        void draw();
        TowerList towers;
    private:
        TowerManager();
        TowerManager(const TowerManager& orig) = delete;
    };

}