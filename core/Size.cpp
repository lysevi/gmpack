/* 
 * File:   Size.cpp
 * Author: lsv
 * 
 * Created on 8 Июль 2013 г., 21:56
 */

#include "Size.h"

namespace core {

    Size::Size(int x, int y) {
        m_width = x;
        m_height = y;
    }

    Size::Size() {
        m_width = 0;
        m_height = 0;
    }

    Size::Size(const Size& orig) {
        m_width = orig.m_width;
        m_height = orig.m_height;
    }

    Size::~Size() {
    }

    int Size::getWidth()const {
        return m_width;
    }

    int Size::setWidth(int width) {
        m_width = width;
    }

    int Size::getHeight()const {
        return m_height;
    }

    int Size::setHeight(int height) {
        m_height = height;
    }
}