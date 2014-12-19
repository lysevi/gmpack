/* 
 * File:   Object3d.h
 * Author: lsv
 *
 * Created on 13 декабря 2014 г., 9:00
 */

#pragma once

#include <memory>

#include "../Utils/Size.h"
#include "../Utils/PathFinder.h"
#include "../Math/Vector3d.h"
#include "../Utils/ProcessLogger.h"

namespace core {
    const int ZCoord = 5;
    class Object3d;
    typedef std::shared_ptr<Object3d> PtrObject3d;
    typedef unsigned int uint;
    class Object3d {
        static uint nextID;
    protected:
    public:
        Object3d();
        Object3d(const Object3d& orig);
        virtual ~Object3d();

        virtual void draw()const = 0;
        virtual void OnClick();
        virtual Vector3d getLogicalCenter()const;
        Vector3d getVector()const;
    public:
        int id;
        bool isSelected;
        Point point;
        Vector3d position;
        Vector3d orientation; // куда повернуто "лицо" объекта
        Size size;
    };

}
