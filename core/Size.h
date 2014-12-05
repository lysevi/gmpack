/* 
 * File:   Coord.h
 * Author: lsv
 *
 * Created on 8 Июль 2013 г., 21:56
 */

#ifndef Size_H
#define	Size_H

namespace core {

    class Size {
    public:
        Size(int width, int height);
        Size();
        Size(const Size& orig);
        virtual ~Size();

        int getWidth()const;
        int setWidth(int width);

        int getHeight()const;
        int setHeight(int height);
    private:
        int m_width, m_height;
    };
}
#endif	/* COORD_H */

