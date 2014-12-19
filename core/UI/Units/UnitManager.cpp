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
    punit->tryFillPath();
    units.push_back(punit);
}

void UnitManager::nextStep() {
    core::UnitList removedUnits;
    for (auto&punit:units) {
        auto res = std::find_if(punit->path.cbegin(),
                punit->path.cend(),
                [punit](const core::Point & p) {
                    return p.line == punit->point.line && p.column == punit->point.column;
                });
        res++;
        if (res != punit->path.cend()) {
            punit->point.line = res->line;
            punit->point.column = res->column;
            punit->position = core::GameMap::instance.Point2Position(punit->point);

        } else {
            removedUnits.push_back(punit);
        }
    }
    for (auto p:removedUnits) {
        units.remove(p);
    }
}

bool UnitManager::tryMakeNewWays() {
    for (auto pu:units) {
        if (!pu->tryFillPath())
            return false;
    }
    return true;
}