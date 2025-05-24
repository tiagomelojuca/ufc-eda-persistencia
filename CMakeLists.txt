project(ufc_eda_persistencia)
cmake_minimum_required(VERSION 3.24)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/exeobj_cmake")
set(FW_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_subdirectory(src/testes)
