/* 
 * File:   ILogWriter.h
 * Author: lsv
 *
 * Created on 17 ноября 2014 г., 21:30
 */

#pragma once

#include <ostream>

namespace utils {

    class ILogWriter {
    public:
        virtual std::ostream& GetStream() = 0;
    };
}