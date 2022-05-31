cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

# set the project name
project(lista6)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(CMAKE_INSTALL_INCLUDEDIR ${PROJECT_SOURCE_DIR}/include)
set(CMAKE_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_INSTALL_LIBDIR ${PROJECT_SOURCE_DIR}/lib)

include_directories(${CMAKE_INSTALL_INCLUDEDIR})
include_directories(${CMAKE_INSTALL_LIBDIR})

add_subdirectory(adapter)
add_subdirectory(coder)
add_subdirectory(filter)
add_subdirectory(main)