file(GLOB SRC "*.h" "*.cpp")

include_directories(../core)
add_executable(tetra ${SRC})
TARGET_LINK_LIBRARIES(tetra core ${SDL_LIBRARY})