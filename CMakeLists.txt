cmake_minimum_required (VERSION 3.0)
cmake_policy(SET CMP0048 NEW)

project (voxcube VERSION 0.1)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules")

set (OpenGL_GL_PREFERENCE GLVND)
find_package (OpenGL REQUIRED)
find_package (SDL2 REQUIRED)
find_package (SDL2_ttf REQUIRED)
find_package (JsonCpp REQUIRED)
find_package (GLM REQUIRED)

option (SYSTEM_WIDE "System-wide install" ON)

add_subdirectory (src)

install (DIRECTORY examples/ DESTINATION share/examples/voxcube
  FILES_MATCHING PATTERN "*.json" PATTERN "*.dat")
install (DIRECTORY shaders/ DESTINATION share/voxcube/shaders)
install (DIRECTORY fonts/ DESTINATION share/voxcube/fonts)
