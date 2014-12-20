FILE(GLOB SRC "App/*.cpp"
              "Math/*.cpp"
              "UI/*.cpp"
              "UI/Units/*.cpp"
              "UI/Towers/*.cpp"
              "UI/Bullets/*.cpp"
              "Utils/*.cpp")

add_library(core STATIC ${SRC})


