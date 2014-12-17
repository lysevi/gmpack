#include "TowerManager.h"
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