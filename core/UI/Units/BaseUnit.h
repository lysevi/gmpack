/* 
 * File:   BaseUnit.h
 * Author: lsv
 *
 * Created on 13 декабря 2014 г., 9:17
 */

#pragma once

#include "../Object3d.h"
#include "../GameMap.h"
#include "../../Utils/Health.h"

#include <memory>

namespace core {
    class BaseUnit;
    
    typedef std::shared_ptr<BaseUnit> PtrUnit;

    
    class BaseUnit : public Object3d {
        
    public:
        BaseUnit();
        BaseUnit(const BaseUnit& orig)=default;
        bool tryFillPath();
        virtual ~BaseUnit();
        void draw()const;
        void onLoop();
    public:
        core::PointList path;
        core::Point    dest_point;
        core::Vector3d dest_position;
        core::Vector3d move_speed;
        core::Health   health;
        bool isDead;
    };

}