
#pragma once

#include "BaseUnit.h"
#include <list>

namespace core {
    typedef std::list<core::PtrUnit> UnitList;
    
    class UnitManager {        
    public:
        static UnitManager* get();
        static void start();
        static void stop();
        virtual ~UnitManager();
        core::PtrUnit getUnitById(int id);
        void append(core::PtrUnit punit);

        UnitList units;
    private:
        UnitManager();
        UnitManager(const UnitManager& orig) = delete;
    };

}