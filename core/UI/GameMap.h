/* 
 * File:   GameMap.h
 * Author: lsv
 *
 * Created on 9 декабря 2014 г., 20:28
 */

#pragma once
#include <list>

namespace core {

    class Coord;
    
    enum CellType {
        GROUND = 0,
        ROCK
    };

    typedef int map_cell;

    struct Point {
        int line;
        int column;

        Point() = default;

        Point(int _line, int _column) : line(_line), column(_column) {
        }

        
        bool operator==(const Point& other)const {
            return other.line == line && other.column == column;
        }

        bool operator<(const Point& other)const {
            if (line != other.line) {
                return (line < other.line);
            }
            if (column != other.column) {
                return (column < other.column);
            }
            return false;
        }
    };

    typedef std::list<Point> PointList;

    class GameMap {
    public:
        static GameMap instance;

        void setLogicalSize(int width, int height);
        void setUiSize(int width, int height);
        void generateMap();
        void draw()const;
        core::Coord Point2Coord(const core::Point&point);
    private:
        GameMap() = default;
        ~GameMap() = default;
    protected:
        int m_logigal_width;
        int m_logigal_height;

        int m_ui_width;
        int m_ui_height;

        map_cell** m_gamemap;
    public:
        int cell_height;
        int cell_width;
        Point startPoint;
        Point endPoint;
        PointList map_way;
    };
}