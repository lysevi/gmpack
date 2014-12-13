FILE(GLOB SRC "App/*.cpp"
              "UI/*.cpp"
              "Utils/*.cpp")

add_library(core STATIC ${SRC})


