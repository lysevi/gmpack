FILE(GLOB SRC "App/*.cpp"
              "UI/*.cpp"
              "UI/Units/*.cpp"
              "UI/Towers/*.cpp"
              "Utils/*.cpp")

add_library(core STATIC ${SRC})


