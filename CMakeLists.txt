# cmake_minimum_required(VERSION 3.7)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_definitions(-std=c++17)

# set(CXX_FLAGS "-Wall")
# set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

# project(SDL2Test)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# find_package(SDL2 REQUIRED)
# include_directories(${SDL2_INCLUDE_DIRS} src)

# add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp)
# string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
# target_link_libraries(SnakeGame ${SDL2_LIBRARIES})

cmake_minimum_required(VERSION 3.7)
project(MySnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$CMAKE_SOURCE_DIR/cmake/")

find_package(SDL2 REQUIRED)

set(SDL2_TTF_INCLUDE_DIRS "/opt/homebrew/Cellar/sdl2_ttf/2.24.0/include/SDL2")
set(SDL2_TTF_LIBRARIES "/opt/homebrew/Cellar/sdl2_ttf/2.24.0/lib/libSDL2_ttf.dylib")

include_directories(${SDL2_TTF_INCLUDE_DIRS})

message(STATUS "SDL2_TTF_INCLUDE_DIRS: ${SDL2_TTF_INCLUDE_DIRS}")

include_directories(${SDL2_INCLUDE_DIRS} mysrc)

add_executable(MySnakeGame  mysrc/main.cpp
                            mysrc/game.cpp
                            mysrc/controller.cpp
                            mysrc/renderer.cpp
                            mysrc/snake.cpp
                            mysrc/colour.cpp)

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

target_link_libraries(MySnakeGame ${SDL2_LIBRARIES}
                                  ${SDL2_TTF_LIBRARIES})
