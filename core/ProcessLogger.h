/* 
 * File:   ProcessLogger.h
 * Author: lsv
 *
 * Created on 13 Ноябрь 2014 г., 22:42
 */

#pragma once

#include <string>
#include "ILogWriter.h"

#define logger          utils::ProcessLogger::getInstance()->GetStream()

using std::endl;
namespace utils {

    class ProcessLogger : public ILogWriter {
    public:
        static ProcessLogger* getInstance();

        virtual std::ostream& GetStream();

        void setLevel(uint16_t level) {
            m_level = level;
        }

        virtual ~ProcessLogger() {
        };
    private:
        uint16_t m_level;
        static ProcessLogger *m_instance;

        ProcessLogger() {
        };
    };
}