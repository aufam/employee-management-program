cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# project settings
project(employee-management-program
    VERSION     0.1.0
    DESCRIPTION "Employee Management Program"
)


# external libraries
include("cmake/delameta.cmake")
## advance preprocessor
delameta_github_package("preprocessor:boostorg/preprocessor#boost-1.86.0")
## string formatter
delameta_github_package("fmt:fmtlib/fmt#11.0.2" OPTIONS "FMT_INSTALL OFF")
## socket and serial framework
delameta_github_package("delameta:aufam/delameta#main" OPTIONS "DELAMETA_INSTALL OFF")
## testing framework
delameta_github_package("Catch2:catchorg/Catch2#v3.7.0")


# executable
file(GLOB_RECURSE SOURCES src/*)
add_executable(emp ${SOURCES})

target_link_libraries(emp PRIVATE
    Boost::preprocessor
    fmt-header-only
    delameta
    Catch2
)

target_compile_options(emp PRIVATE
    -Wall
    -Wextra
)

