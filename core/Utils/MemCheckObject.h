/* 
 * File:   BaseObject.h
 * Author: lsv
 *
 * Created on 11 декабря 2014 г., 22:28
 */
#pragma once

#include <mutex>
#include <exception>
#include "ProcessLogger.h"
#include "Exception.h"
namespace core {

    class MemCheckObject {
        static std::mutex memory_mutex;
        static long long memory_op;
    public:

        MemCheckObject();
        static void* operator new(std::size_t sz);
        static void* operator new[](std::size_t sz);
        static void checkMemoryStatus();
    };

}