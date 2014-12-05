/* 
 * File:   ProcessLogger.cpp
 * Author: lsv
 * 
 * Created on 13 Ноябрь 2014 г., 22:42
 */

#include "ProcessLogger.h"
#include <iostream>

using namespace utils;

ProcessLogger* ProcessLogger::m_instance;

ProcessLogger* ProcessLogger::getInstance() {
    if (ProcessLogger::m_instance == nullptr) {
        ProcessLogger::m_instance = new ProcessLogger();
        ProcessLogger::m_instance->setLevel(0);
    }
    return m_instance;
}

std::ostream& ProcessLogger::GetStream() {
    return std::cout;
}