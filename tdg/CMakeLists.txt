file(GLOB SRC "*.h" "*.cpp")

include_directories(../core)
add_executable(tdg ${SRC})
TARGET_LINK_LIBRARIES(tdg core ${SDL_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})