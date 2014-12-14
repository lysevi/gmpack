/* 
 * File:   Object3d.h
 * Author: lsv
 *
 * Created on 13 декабря 2014 г., 9:00
 */

#pragma once

#include "../Utils/MemCheckObject.h"
#include "../Utils/Coord.h"
#include "../Utils/Size.h"
#include "../Utils/PathFinder.h"

namespace core 
{
    const int ZCoord=5;
    class Object3d:public MemCheckObject {
        static uint nextID;
    protected:
    public:
        Object3d();
        Object3d(const Object3d& orig);
        virtual ~Object3d();

        virtual void draw()const=0;
        virtual void OnClick();
    public:
        uint  id;
        bool isSelected;
        Point point;
        mutable Coord coord;
        Size  size;
    };

}