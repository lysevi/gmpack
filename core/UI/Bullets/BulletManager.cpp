#include "BulletManager.h"
#include "../Units/UnitManager.h"
#include "../Towers/TowerManager.h"
#include <algorithm>
#include <assert.h>
using namespace core;

BulletManager::BulletManager() {
}

BulletManager::~BulletManager() {
}

BulletManager* BulletManager::get() {
    static BulletManager* instance;
    if (instance == nullptr) {
        instance = new BulletManager;
    }
    return instance;
}

void BulletManager::start() {
    TowerManager::get();
}

void BulletManager::stop() {
    delete get();
}


void BulletManager::append(core::PtrBullet punit) {
    bullets.push_back(punit);
}

void BulletManager::onLoop(){
    BulletList toRemove;
    for(auto pb:bullets){
        logger<<"id_of_target="<<pb->id_of_target<<std::endl;
        auto target=core::UnitManager::get()->getUnitById(pb->id_of_target);
        if(distance(target->position,pb->position)<core::GameMap::instance.cell_width){
            toRemove.push_back(pb);
            continue;
        }
        assert(target!=nullptr);

        auto dv=(target->position - pb->position);
        pb->position=pb->position+dv*pb->speed;
    }

    for(auto pb:toRemove){
        bullets.remove(pb);
    }
}

void BulletManager::draw(){
    for(auto pb:bullets){
        pb->draw();
    }
}