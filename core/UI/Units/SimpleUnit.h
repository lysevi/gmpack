
#pragma once
#include "BaseUnit.h"

namespace core {

    class SimpleUnit : public BaseUnit {
    public:
        SimpleUnit();
        SimpleUnit(const SimpleUnit& orig)=default;
        virtual ~SimpleUnit();
        void draw()const;
    private:

    };

}