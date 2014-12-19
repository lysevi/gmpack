/* 
 * File:   GameMap.h
 * Author: lsv
 *
 * Created on 9 декабря 2014 г., 20:28
 */

#pragma once
#include <list>

#include "../Math/Vector3d.h"

namespace core {

    class Coord;

    enum CellType {
        GROUND = 0,
        ROCK
    };

    typedef CellType map_cell;

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
        core::Vector3d Point2Position(const core::Point&point)const;
        Point Position2Point(const core::Vector3d&c)const;
        CellType operator()(int line, int column) const;
        void setValue(int line, int column, CellType v);
        core::PointList getWay(core::Point startPoint);
        void changeCell(int line, int column, CellType ctype);
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
    };
}