#include <Utils/PathFinder.h>
#include <iostream>
#include <cstdlib>

const int map_width = 35;
const int map_height = 20;

core::map_cell** map;

void init_map() {
    map = new core::map_cell*[map_height];

    for (int i = 0; i < map_height; ++i) {
        map[i] = new core::map_cell[map_width];
        if ((i == (int) (map_height / 2)) || (i == ((int) (map_height / 2) - 1))) {
            continue;
        }
        map[i][map_width / 2] = core::CellType::ROCK;
    }

    for (int i = map_height / 2; i < map_height - 3; ++i) {
        for (int j = map_width / 2 + map_width / 4; j < map_width - 3; ++j)
            map[i][j] = core::CellType::ROCK;
    }
}

void show_map() {
    for (int i = 0; i < map_height; ++i) {
        for (int j = 0; j < map_width; ++j) {
            std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    init_map();

    show_map();
    auto from = core::Point{0, 0};
    auto goal = core::Point{map_height - 1, map_width - 1};
    auto path = core::PathFinder::astar_flow(map, map_height, map_width, from, goal);

    for (auto it = path.begin(); it != path.end(); ++it) {
        map[it->line][it->column] = 9;
    }
    std::cout << "***\n";
    show_map();
    
    return 0;
}
