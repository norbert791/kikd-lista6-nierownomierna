cmake_minimum_required(VERSION 3.10)

set(CODER_SOURCES DifferentialCoder.cpp NonUniformQuantizer.cpp)
set(CODER_HEADERS DifferentialCoder.hpp NonUniformQuantizer.hpp Quantizer.hpp Coder.hpp)

add_library(coder STATIC ${CODER_SOURCES})

install(TARGETS coder DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${CODER_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

target_link_libraries(coder PUBLIC image_adapter)
target_include_directories(coder PUBLIC ${PROJECT_SOURCE_DIR}/adapter)