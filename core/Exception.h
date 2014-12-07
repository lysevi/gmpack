/* 
 * File:   Exception.h
 * Author: lsv
 *
 * Created on 17 ноября 2014 г., 19:55
 */

#pragma once
#include <string>
#include "ProcessLogger.h"
#include <stdexcept>
namespace core {

    struct CodePosition {

        CodePosition(const char* file, int line, const char* function)
        : File(file), Line(line), Function(function) {
        }
        const char* File;
        const int Line;
        const char* Function;

        std::string toString()const;
    };

#define POSITION (CodePosition(__FILE__, __LINE__, __FUNCTION__))

    class Exception : public std::exception {
    public:

        inline static Exception CreateAndLog(const CodePosition& pos) {
            logger << "FATAL ERROR. The Exception will be thrown! "
                    << pos.toString()
                    << endl;
            return Exception();
        }

        inline static Exception CreateAndLog(const CodePosition& pos, const std::string& message) {
            logger << "FATAL ERROR. The Exception will be thrown! "
                    << pos.toString()
                    << " Message: "
                    << message
                    << endl;
            return Exception(message);
        }

    public:

        virtual const char* what() const throw () {
            return _message.c_str();
        }

        const std::string& GetErrorMessage() const {
            return _message;
        }

        ~Exception() throw () {
        };

    protected:

        Exception() {
        }

        Exception(const char*& message) : _message(std::string(message)) {
        }

        Exception(const std::string& message) : _message(message) {
        }

    private:
        std::string _message;
    };
}