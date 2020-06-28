add_definitions (-DGL_GLEXT_PROTOTYPES)
include_directories (
  ${SDL2_INCLUDE_DIR}/..
  ${OPENGL_INCLUDE_DIR}/..
  ${GLM_INCLUDE_DIR}
  )

add_executable (voxcube
  Window.cpp
  Shader.cpp
  Model.cpp
  Person.cpp
  Application.cpp
  main.cpp
)

target_link_libraries (voxcube
  OpenGL::GL
  ${SDL2_LIBRARY}
  ${GLM_LIBRARY}
  )
