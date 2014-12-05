/* 
 * File:   Utils.h
 * Author: lsv
 *
 * Created on 13 Ноябрь 2014 г., 22:43
 */

#pragma once

#include <string>
#include <list>

namespace utils {

    typedef std::list<std::string> StringList;

    // класс для удаления и освобождения shared_memory

    class NonCopy {
    private:
        NonCopy(const NonCopy&) = delete;
        NonCopy& operator=(const NonCopy&) = delete;
    protected:
        NonCopy() = default;
    };

}