file(GLOB SRC "*.h" "*.cpp")

include_directories(../core)
add_executable(tic_tac ${SRC})
TARGET_LINK_LIBRARIES(tic_tac core ${SDL_LIBRARY})