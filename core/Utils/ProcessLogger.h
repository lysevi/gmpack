/* 
 * File:   ProcessLogger.h
 * Author: lsv
 *
 * Created on 13 Ноябрь 2014 г., 22:42
 */

#pragma once

#include <string>
#include "ILogWriter.h"

#define logger          core::ProcessLogger::get()->GetStream()

using std::endl;
namespace core {

    class ProcessLogger : public ILogWriter {
    public:
        static ProcessLogger* get();
        static void start();
        static void stop();
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