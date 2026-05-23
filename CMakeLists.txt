cmake_minimum_required(VERSION 3.20)
project(render_to_ppm CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Pangolin CONFIG REQUIRED)

add_executable(render_to_ppm src/render_to_ppm.cpp)
target_link_libraries(render_to_ppm PRIVATE ${Pangolin_LIBRARIES})
target_include_directories(render_to_ppm PRIVATE ${Pangolin_INCLUDE_DIRS})
