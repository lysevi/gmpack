/* 
 * File:   BaseUnit.h
 * Author: lsv
 *
 * Created on 13 декабря 2014 г., 9:17
 */

#pragma once

#include "../Object3d.h"
#include "../GameMap.h"
#include <memory>

namespace core {
    class BaseUnit;
    typedef std::shared_ptr<BaseUnit> PtrUnit;

    class BaseUnit : public Object3d {
    public:
        BaseUnit();
        BaseUnit(const BaseUnit& orig);
        bool tryFillPath();
        virtual ~BaseUnit();
        void draw()const;
    public:
        core::PointList path;
    };

}