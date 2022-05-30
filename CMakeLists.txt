cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_STANDARD 20)

# set the project name
project(main)

# add the MathFunctions library
add_subdirectory(libtga-master)
add_subdirectory(adapter)
add_subdirectory(coder)
add_subdirectory(filter)

# add the executable
add_executable(${PROJECT_NAME} main.cpp Quantizer.cpp TgaAdapter.cpp image.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC libtga PRIVATE m)

target_include_directories(${PROJECT_NAME} PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/libtga-master"
                          )

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -pedantic)