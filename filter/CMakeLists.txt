cmake_minimum_required(VERSION 3.10)

set(FILTER_SOURCES UpperFilterProcess.cpp LowerFilterProcess.cpp UniformFilterQuantizer.cpp IdQuantizer.cpp)
set(FILTER_HEADERS Filter.hpp UpperFilterProcess.hpp LowerFilterProcess.hpp UniformFilterQuantizer.hpp IdQuantizer.hpp)

add_library(Filter STATIC ${FILTER_SOURCES})

install(TARGETS Filter DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${FILTER_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

target_link_libraries(Filter PUBLIC image_adapter)
target_include_directories(Filter PUBLIC ${PROJECT_SOURCE_DIR}/adapter)