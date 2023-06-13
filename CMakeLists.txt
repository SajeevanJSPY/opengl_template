cmake_minimum_required(VERSION 3.22)

project(opengl_template)

add_executable(${PROJECT_NAME} glad.c main.c)

target_link_libraries(${PROJECT_NAME} GL dl glfw)

