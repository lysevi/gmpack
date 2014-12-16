include_directories(../core)
find_package(Boost 1.57.0
    COMPONENTS
    unit_test_framework
    REQUIRED
)


add_executable(pathfinders_test pathfinders_test.cpp)
add_executable(unit_test unit_test.cpp)

TARGET_LINK_LIBRARIES(pathfinders_test core ${ALL_LIBRARIES})
TARGET_LINK_LIBRARIES(unit_test core ${ALL_LIBRARIES} ${Boost_LIBRARIES})

add_test(tdg_testes pathfinders_test)
add_test(unit_testes unit_test)