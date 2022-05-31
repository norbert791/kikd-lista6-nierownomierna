cmake_minimum_required(VERSION 3.10)

set(ADAPTER_SOURCES image.cpp TgaAdapter.cpp)
set(ADAPTER_HEADERS image_adapter.hpp)

add_subdirectory(libtga-master)

add_library(image_adapter STATIC ${ADAPTER_SOURCES})

install(TARGETS image_adapter DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${ADAPTER_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

target_link_libraries(image_adapter PUBLIC libtga)
target_include_directories(image_adapter PUBLIC libtga-master)