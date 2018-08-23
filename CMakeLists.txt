cmake_minimum_required(VERSION 3.12)
project(MorderOpenGLUdemyTutorial)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        Window.cpp Window.h
        Shader.cpp Shader.h
        Mesh.cpp Mesh.h
        Transform.h
        obj_loader.h obj_loader.cpp
        Camera.cpp Camera.h
        stb_image.h stb_image.c
        Texture.cpp Texture.h
        Object.h) # which files should be compiled

add_executable(MorderOpenGLUdemyTutorial ${SOURCE_FILES}) # which files should produce executables

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
link_directories(${GLEW_LIBRARY_DIRS})
if(NOT GLEW_FOUND)
    message(ERROR "GLEW not found!")
endif(NOT GLEW_FOUND)

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIBRARY_DIRS})
if(NOT SDL2_FOUND)
    message(ERROR "SDL2 not found!")
endif(NOT SDL2_FOUND)

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIR})
link_directories(${GLFW_LIBRARY_DIRS})
if(NOT GLFW_FOUND)
    message(ERROR "GLFW not found!")
endif(NOT GLFW_FOUND)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR "OPENGL not found!")
endif(NOT OPENGL_FOUND)

target_link_libraries(MorderOpenGLUdemyTutorial ${GLFW_LIBRARIES} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})