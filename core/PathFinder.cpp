/* 
 * File:   PathFinder.cpp
 * Author: lsv
 * 
 * Created on 9 декабря 2014 г., 20:22
 */

#include "PathFinder.h"
#include <cmath>
#include <list>
#include <set>
#include <map>
#include <algorithm>

using namespace core;

PathFinder::PointList PathFinder::getNeighbors(PathFinder::Point from, map_cell** map, int map_height, int map_width) {
    PathFinder::PointList result;
    if ((from.column - 1) >= 0) {
        result.push_back({from.line, from.column - 1});
    }

    if ((from.column + 1) != map_width) {
        result.push_back({from.line, from.column + 1});
    }

    if ((from.line - 1) >= 0) {
        result.push_back({from.line - 1, from.column});
    }

    if ((from.line + 1) != map_height) {
        result.push_back({from.line + 1, from.column});
    }

    result.remove_if([map](const Point & p) {
        return map[p.line][p.column] == ROCK;
    });

    return result;
}

float PathFinder::heuristic_cost_estimate(PathFinder::Point start, PathFinder::Point goal) {
    auto res = sqrt((float) (pow((goal.line - start.line), 2.0) + pow((goal.column - start.column), 2.0)));

    return res;
}

PathFinder::PointList PathFinder::astar_flow(map_cell**map, int map_height, int map_width, Point start, Point goal) {
    PathFinder::PointList result;

    std::set<PathFinder::Point> closedset;
    std::set<PathFinder::Point> openset;
    std::map<PathFinder::Point, Point> came_from;
    std::map<PathFinder::Point, float> g_score;
    std::map<PathFinder::Point, float> f_score;

    openset.insert(start);
    g_score[start] = 0;
    f_score[start] = g_score[start] + heuristic_cost_estimate(start, goal);

    while (!openset.empty()) {
        auto current_p = std::min_element(openset.begin(), openset.end(),
                [&f_score](const Point el1, const Point el2) {
                    return f_score[el1] < f_score[el2];
                });

        auto current = *current_p;

        if (current == goal) {

            auto curpath = goal;
            result.push_back(goal);
            while (came_from.count(current)) {
                curpath = came_from[curpath];
                if (std::find(result.begin(), result.end(), curpath) != result.end())
                    break;
                result.push_back(curpath);
            }
            return result;
        }

        openset.erase(current);
        closedset.insert(current);

        for (auto neighbor:getNeighbors(current, map, map_height, map_width)) {
            if (closedset.find(neighbor) != closedset.end()) {
                continue;
            }

            if (g_score.find(current) == g_score.end())
                g_score[current] = 0;

            auto tentative_g_score = g_score[current] + heuristic_cost_estimate(current, neighbor);

            if (g_score.find(neighbor) == g_score.end())
                g_score[neighbor] = 0;

            if ((openset.find(neighbor) == openset.end())
                    ) {
                came_from[neighbor] = current;
                g_score[neighbor] = tentative_g_score;
                f_score[neighbor] = g_score[neighbor] + heuristic_cost_estimate(neighbor, goal);

                openset.insert(neighbor);
            }
        }
    }
    return result;
}
