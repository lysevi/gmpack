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
    auto res = std::find_if(punit->path.cbegin(),
            punit->path.cend(),
            [punit](const core::Point & p) {
                return p.line == punit->point.line && p.column == punit->point.column;
            });
    ++res;
    if (res != punit->path.cend()) {
        punit->dest_point.line = res->line;
        punit->dest_point.column = res->column;
        punit->dest_position = core::GameMap::instance.Point2Position(punit->dest_point);
    }
    units.push_back(punit);
}

void UnitManager::removeDeads(){
    auto predicat=[](PtrUnit pu){
            return pu->isDead;
    };
    units.remove_if(predicat);
}

void UnitManager::nextStep() {
    core::UnitList removedUnits;
    for (auto&punit:units) {

        auto cur_dist = core::distance(punit->position, punit->dest_position);
        if (cur_dist >= 2) {
            calcNewPosition(punit);
        } else { // обновляем точки размещения на карте.
            // ищем точку в списке-маршруте
            auto res = std::find_if(punit->path.cbegin(),
                    punit->path.cend(),
                    [punit](const core::Point & p) {
                        return p.line == punit->point.line && p.column == punit->point.column;
                    });
            ++res;
            if (res != punit->path.cend()) { // если до конца карты не дошли
                punit->point.line = res->line;
                punit->point.column = res->column;
                punit->position = core::GameMap::instance.Point2Position(punit->point);
                ++res;
                if (res != punit->path.cend()) {
                    punit->dest_point.line = res->line;
                    punit->dest_point.column = res->column;
                    punit->dest_position = core::GameMap::instance.Point2Position(punit->dest_point);
                }
                calcNewPosition(punit);

            } else {
                removedUnits.push_back(punit);
            }

            for (auto p:removedUnits) { // удаляем те юниты, что дошли до конца
                units.remove(p);
            }
            // обновился список. если не удалить, то будет эксепшен
            if (removedUnits.size() != 0)
                break;
        }
    }
}

bool UnitManager::tryMakeNewWays() {
    for (auto pu:units) {
        if (!pu->tryFillPath())
            return false;
    }
    return true;
}

void UnitManager::calcNewPosition(PtrUnit punit)const {
    core::Vector3d speed = punit->move_speed;
    core::Vector3d tmp = (punit->dest_position - punit->position);
    tmp.norm();
    auto delta_v = tmp* speed;

    punit->position = punit->position + delta_v;
}

void UnitManager::draw() {
    for (auto punit:units) {
        punit->draw();
    }
}

void UnitManager::onLoop(){
    for (auto punit:units) {
        punit->onLoop();
    }
}