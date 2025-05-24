project(TesteUnitario)
cmake_minimum_required(VERSION 3.24)

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
    TesteUnitario
    "abb_test.cpp"
)

target_link_libraries(TesteUnitario gtest_main)

install(
    TARGETS TesteUnitario
    RUNTIME DESTINATION bin
)
