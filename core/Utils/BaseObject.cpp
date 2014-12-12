/* 
 * File:   BaseObject.cpp
 * Author: lsv
 * 
 * Created on 11 декабря 2014 г., 22:28
 */

#include "BaseObject.h"
using namespace core;

long long BaseObject::memory_op = 0L;
std::mutex BaseObject::memory_mutex{};

BaseObject::BaseObject() {
};

void* BaseObject::operator new(std::size_t sz) {
    std::lock_guard<std::mutex> lock(memory_mutex);
    ++memory_op;
    return ::operator new(sz);
}
void* BaseObject::operator new[](std::size_t sz) {
    std::lock_guard<std::mutex> lock(memory_mutex);
    --memory_op;
    return ::operator new(sz);
}

void BaseObject::checkMemoryStatus() {
    if (memory_op % 2 != 0)
        throw Exception::CreateAndLog(POSITION, "bad memory");
    logger << "memory ok." << std::endl;
}
