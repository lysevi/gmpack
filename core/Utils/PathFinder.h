/* 
 * File:   PathFinder.h
 * Author: lsv
 *
 * Created on 9 декабря 2014 г., 20:22
 */

#pragma once

#include <list>
#include "GameMap.h"

namespace core {

    class PathFinder {
    public:
        static PointList astar_flow(map_cell**map, const int map_height, const int map_width, Point start, Point goal);
    private:
        static PointList getNeighbors(Point from, map_cell** map, int map_height, int map_width);
        static float heuristic_cost_estimate(Point start, Point goal);
    };

}