/* 
 * File:   Exception.cpp
 * Author: lsv
 * 
 * Created on 17 ноября 2014 г., 19:55
 */

#include "Exception.h"

#include <sstream>
using namespace core;
std::string CodePosition::toString()const {
    std::stringstream ss;
    ss << File << " line" << Line << " function: " << Function << std::endl;
    return ss.str();
}