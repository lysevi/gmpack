include_directories(../core)
add_executable(pathfinders_test pathfinders_test.cpp)
TARGET_LINK_LIBRARIES(pathfinders_test core ${SDL_LIBRARY})