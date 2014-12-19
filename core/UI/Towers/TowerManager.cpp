#include "TowerManager.h"
#include "../Units/UnitManager.h"
#include <algorithm>

using namespace core;

TowerManager::TowerManager() {
}

TowerManager::~TowerManager() {
}

TowerManager* TowerManager::get() {
    static TowerManager* instance;
    if (instance == nullptr) {
        instance = new TowerManager;
    }
    return instance;
}

void TowerManager::start() {
    TowerManager::get();
}

void TowerManager::stop() {
    delete get();
}

core::PtrTower TowerManager::getTowerById(int id) {
    auto res = std::find_if(towers.cbegin(), towers.cend(),
            [id](const core::PtrTower pu) {
                return pu->id == id;
            });
    if (res == towers.cend())
        return nullptr;
    else
        return *res;
}

void TowerManager::append(core::PtrTower punit) {
    towers.push_back(punit);
}

void TowerManager::calcNewTargets(){
    for(auto pt:towers){
        core::UnitList closesUnit;// досягаемые враги.
        core::Vector3d towerCoord=pt->position;
        for(auto pu:core::UnitManager::get()->units){
            core::Vector3d unit_coord=core::GameMap::instance.Point2Position(pu->point);
            auto dist=(towerCoord-unit_coord).length();
            if(dist<pt->getRadius()){
                closesUnit.push_back(pu);
            }
        }
        if(closesUnit.size()==0){
            pt->id_of_target=-1;
            continue;
        }
        if(pt->id_of_target==-1){
            pt->id_of_target=closesUnit.front()->id;
        }
        // если уже целимся в кого то.
        if(pt->id_of_target!=-1){
            // проверяем, что он все еще досягаем.
            auto id_of_target=pt->id_of_target;
            auto res=core::UnitManager::get()->getUnitById(id_of_target);
            // если все еще досягаем
            if(res!=nullptr){
                continue;
            }else{
                pt->id_of_target=closesUnit.front()->id;
            }
        }
    }
}

void TowerManager::calcTowersAngles(){
    for(auto &pt:towers){
        if(pt->id_of_target==-1){
            continue;
        }

        auto pu=core::UnitManager::get()->getUnitById(pt->id_of_target);

        core::Vector3d gunface_orig=pt->gun_vector;
	core::Vector3d gunface=gunface_orig;
	auto gun_pos = pt->getLogicalCenter();
        auto hero_pos = pu->getLogicalCenter();
	gunface.norm();
	auto guard_to_her = hero_pos - gun_pos;
	guard_to_her.norm();
	float angle = acosf(dot(gunface, guard_to_her))*(180/3.14159265358979323846264338327);

        if ((pt->getVector().y>pu->getVector().y))
            angle = -angle;

        pt->angle=angle;
    }
}