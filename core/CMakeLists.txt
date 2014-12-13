FILE(GLOB SRC "App/*.cpp"
              "UI/*.cpp"
              "UI/Units/*.cpp"
              "Utils/*.cpp")

add_library(core STATIC ${SRC})


