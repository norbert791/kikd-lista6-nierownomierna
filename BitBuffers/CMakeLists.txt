cmake_minimum_required(VERSION 3.10)

set(FILTER_SOURCES LowerFilter.cpp UpperFilter.cpp)
set(FILTER_HEADERS LowerFilter.h UpperFilter.h Filter.hpp)

add_library(Filter STATIC ${FILTER_SOURCES})

install(TARGETS Filter DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${FILTER_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

target_link_libraries(Filter PUBLIC image_adapter)
target_include_directories(Filter PUBLIC ${PROJECT_SOURCE_DIR}/adapter)