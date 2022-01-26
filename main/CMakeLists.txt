cmake_minimum_required(VERSION 2.6)

project(main)

find_package(Boost COMPONENTS filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(main main.cpp)
target_link_libraries(main ${Boost_FILESYSTEM_LIBRARY})