if (SYSTEM_WIDE)
  set (RESOURCE_DIR ${CMAKE_INSTALL_PREFIX}/share/voxcube)
else (SYSTEM_WIDE)
  set (RESOURCE_DIR ".")
endif (SYSTEM_WIDE)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources.h.in ${CMAKE_CURRENT_BINARY_DIR}/Resources.h)

add_definitions (-DGL_GLEXT_PROTOTYPES -std=c++17)
include_directories (
  ${SDL2_INCLUDE_DIR}/..
  ${OPENGL_INCLUDE_DIR}
  ${GLM_INCLUDE_DIRS}
  ${JSONCPP_INCLUDE_DIR}/..
  ${CMAKE_CURRENT_BINARY_DIR}
  )

add_executable (voxcube
  Window.cpp
  Shader.cpp
  ConfigFile.cpp
  Model.cpp
  Person.cpp
  Renderer.cpp
  Application.cpp
  main.cpp
)

target_link_libraries (voxcube
  OpenGL::GL
  ${SDL2_LIBRARY}
  ${JSONCPP_LIBRARY}
  )

install (TARGETS voxcube RUNTIME DESTINATION bin)
