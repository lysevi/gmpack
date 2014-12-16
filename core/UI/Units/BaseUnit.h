/* 
 * File:   BaseUnit.h
 * Author: lsv
 *
 * Created on 13 декабря 2014 г., 9:17
 */

#pragma once

#include "../Object3d.h"
#include <memory>

namespace core{
    class BaseUnit;
    typedef std::shared_ptr<BaseUnit> PtrUnit;
class BaseUnit:public Object3d {
public:
    BaseUnit();
    BaseUnit(const BaseUnit& orig);
    virtual ~BaseUnit();
    void draw()const;
private:

};

}