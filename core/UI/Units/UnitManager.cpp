#include "UnitManager.h"
#include <algorithm>
using namespace core;

UnitManager::UnitManager() {
}

UnitManager::~UnitManager() {
}

UnitManager* UnitManager::get() {
    static UnitManager* instance;
    if (instance == nullptr) {
        instance = new UnitManager;
    }
    return instance;
}

void UnitManager::start() {
    UnitManager::get();
}

void UnitManager::stop() {
    delete get();
}

core::PtrUnit UnitManager::getUnitById(int id) {
    auto res = std::find_if(units.cbegin(), units.cend(),
            [id](const core::PtrUnit pu) {
                return pu->id == id;
            });
    if (res == units.cend())
        return nullptr;
    else
        return *res;
}

void UnitManager::append(core::PtrUnit punit) {
    units.push_back(punit);
}