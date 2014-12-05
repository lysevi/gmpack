cmake_minimum_required(VERSION 2.8)
PROJECT(tdg)

INCLUDE(FindSDL)

IF(SDL_FOUND) 
        INCLUDE_DIRECTORIES(SDL_INCLUDE_DIR) 
ELSE(SDL_FOUND) 
        MESSAGE("SDL not found") 
ENDIF(SDL_FOUND) 

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -Wwrite-strings -g -ftest-coverage -fprofile-arcs")

add_subdirectory(core)
add_subdirectory(tic_tac)
#file(GLOB src_cpp "*.cpp" "core/*.cpp" "units/*.cpp")
#add_executable(tdg ${src_cpp})
#TARGET_LINK_LIBRARIES(tdg ${SDL_LIBRARY})
