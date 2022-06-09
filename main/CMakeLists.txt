cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

# set the project name
set(encoder_files encoder.cpp functions.cpp)

#add_subdirectory(${PROJECT_SOURCE_DIR}/adapter)

# add the executable
add_executable(encoder ${encoder_files})

target_link_libraries(encoder PUBLIC image_adapter coder Filter bitBuffers)
target_include_directories(encoder PUBLIC ${PROJECT_SOURCE_DIR}/adapter ${PROJECT_SOURCE_DIR}/coder ${PROJECT_SOURCE_DIR}/filter ${PROJECT_SOURCE_DIR}/BitBuffers)
target_compile_options(encoder PUBLIC -Wall -pedantic)

add_executable(decoder decoder.cpp functions.cpp)
target_link_libraries(decoder PUBLIC image_adapter Filter coder bitBuffers)
target_include_directories(decoder PUBLIC ${PROJECT_SOURCE_DIR}/adapter ${PROJECT_SOURCE_DIR}/coder ${PROJECT_SOURCE_DIR}/filter ${PROJECT_SOURCE_DIR}/BitBuffers)
target_compile_options(decoder PUBLIC -Wall -pedantic)

add_executable(test test.cpp functions.cpp)
target_link_libraries(test PUBLIC image_adapter coder bitBuffers)
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/adapter ${PROJECT_SOURCE_DIR}/coder ${PROJECT_SOURCE_DIR}/filter ${PROJECT_SOURCE_DIR}/BitBuffers)
target_compile_options(test PUBLIC -Wall -pedantic)

add_executable(diff diff.cpp functions.cpp)
target_link_libraries(diff PUBLIC image_adapter coder bitBuffers)
target_include_directories(diff PUBLIC ${PROJECT_SOURCE_DIR}/adapter ${PROJECT_SOURCE_DIR}/coder ${PROJECT_SOURCE_DIR}/filter ${PROJECT_SOURCE_DIR}/BitBuffers)
target_compile_options(diff PUBLIC -Wall -pedantic)