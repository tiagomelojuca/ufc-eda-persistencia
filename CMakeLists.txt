cmake_minimum_required(VERSION 3.24)
project(ufc_eda_persistencia)

option(BUILD_UNIT_TESTS "Build unit tests using gtest framework, requires C++17" ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/exeobj_cmake")
set(FW_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (BUILD_UNIT_TESTS)
    add_subdirectory(src/testes)
endif()

add_executable(
    cli
    "${FW_SOURCE_DIR}/main.cpp"
)

target_include_directories(
    cli 
    PRIVATE
    "${FW_SOURCE_DIR}"
)

install(
    TARGETS cli
    RUNTIME DESTINATION bin
)
