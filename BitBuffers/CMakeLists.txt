cmake_minimum_required(VERSION 3.10)

set(BIT_BUFFERS_SOURCES BitReader.cpp BitWriter.cpp bitFiles.cpp BitReader.cpp)
set(BIT_BUFFERS_HEADERS BitReader.hpp bitWriter.hpp bitFiles.hpp BitReader.hpp)

add_library(bitBuffers STATIC ${BIT_BUFFERS_SOURCES})

install(TARGETS bitBuffers DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${BIT_BUFFERS_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

target_link_libraries(bitBuffers PUBLIC image_adapter)
target_include_directories(bitBuffers PUBLIC ${PROJECT_SOURCE_DIR}/adapter)