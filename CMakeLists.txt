cmake_minimum_required(VERSION 4.3)
project(rummikub_engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(rummikub_engine main.cpp
        src/core/headers/tile.h
        src/core/headers/tileId.h
        src/core/headers/rack.h
        src/core/rack.cpp
        src/core/headers/tileSet.h
)
