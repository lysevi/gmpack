/* 
 * File:   Coord.h
 * Author: lsv
 *
 * Created on 8 Июль 2013 г., 21:56
 */

#ifndef COORD_H
#define	COORD_H

namespace core {

    struct Coord {
        Coord(int x, int y);
        Coord();
        Coord(const Coord& orig);

        int x;
        int y;
    };
}
#endif	/* COORD_H */

