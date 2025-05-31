cmake_minimum_required(VERSION 3.24)
project(unit_test)

# TODO: Investigar por que gera o gtest static por default, levando ao erro abaixo:
#       gtest.lib(gtest-all.obj) : error LNK2038: mismatch detected for 'RuntimeLibrary':
#       value 'MT_StaticRelease' doesn't match value 'MD_DynamicRelease' in dummy.obj
#       Reparar que o default do VC eh gerar dinamico. Aparentemente, desde o VC2005:
#       "If you use Visual Studio 2005 or above, we recommend the -md version as /MD
#       is the default for new projects in these versions of Visual Studio"
#       A flag abaixo forca a geracao dinamica do gtest resolvendo de forma bruta,
#       mas nao eh a solucao mais adequada
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(
    ${CMAKE_SOURCE_DIR}/3rd_party/gtest
    ${CMAKE_CURRENT_BINARY_DIR}/gtest
)

add_executable(
    unit_test
    "abb_test.cpp"
    "arg_parser_test.cpp"
    "executor_test.cpp"
    "file_parser_test.cpp"
    "file_writer_test.cpp"
)

target_link_libraries(unit_test gtest_main)
target_include_directories(unit_test PRIVATE ${FW_SOURCE_DIR})

install(
    TARGETS unit_test
    RUNTIME DESTINATION bin
)
