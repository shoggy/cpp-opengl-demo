add_executable(opengl_app main.cpp)

target_link_libraries(opengl_app
    PRIVATE
        OpenGL::GL
        FreeGLUT::freeglut
)

install(TARGETS opengl_app
    RUNTIME DESTINATION bin
    COMPONENT Runtime
)
