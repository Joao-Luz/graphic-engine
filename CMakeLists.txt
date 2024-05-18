cmake_minimum_required(VERSION 3.10)
project(MyOpenGLLibrary)

set(CMAKE_CXX_STANDARD 17)

# Add include directories
include_directories(src)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the library
add_library(MyOpenGLLibrary ${SOURCES})


# Link third-party libraries (e.g., GLFW, GLAD, etc.)
find_package(glfw3 REQUIRED)
find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(MyOpenGLLibrary glfw GLM::glm ${OPENGL_LIBRARIES})

# Create an executable for each example
file(GLOB EXAMPLES "examples/*.cpp")
foreach(EXAMPLE ${EXAMPLES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE})
    target_link_libraries(${EXAMPLE_NAME} MyOpenGLLibrary)
endforeach()
