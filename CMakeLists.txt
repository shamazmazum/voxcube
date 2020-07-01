cmake_minimum_required (VERSION 2.6)
cmake_policy(SET CMP0048 NEW)

project (voxcube VERSION 0.1)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules")
set (CMAKE_C_FLAGS_RELEASE "-O3 -march=native")

find_package(PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (SDL2 REQUIRED)
pkg_check_modules(GLM REQUIRED glm)

option (SYSTEM_WIDE "System-wide install" ON)

add_subdirectory (src)
