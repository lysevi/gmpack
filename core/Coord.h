/* 
 * File:   Coord.h
 * Author: lsv
 *
 * Created on 8 Июль 2013 г., 21:56
 */

#ifndef COORD_H
#define	COORD_H

namespace core {

    class Coord {
    public:
        Coord(int x, int y);
        Coord();
        Coord(const Coord& orig);
        virtual ~Coord();

        int getX()const;
        int setX(int x);

        int getY()const;
        int setY(int y);
    private:
        int m_x, m_y;
    };
}
#endif	/* COORD_H */

