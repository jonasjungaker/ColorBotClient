cmake_minimum_required(VERSION 3.28)
project(ColorBotClient LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(GLOB IMGUI
        "${PROJECT_SOURCE_DIR}/extern/imgui/*.cpp"
        "${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_glfw.cpp"
        "${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_opengl3.cpp"
)

add_subdirectory(extern/pybind11)
add_subdirectory(extern/glfw)
add_subdirectory(extern/SFML)

add_executable(client src/main.cpp src/Client.cpp src/Scripting/python.cpp ${IMGUI})
target_include_directories(client PRIVATE inc)
target_include_directories(client PRIVATE extern/imgui)
target_include_directories(client PRIVATE extern/imgui/backends)
target_include_directories(client PRIVATE extern/pybind11/include)
target_include_directories(client PRIVATE extern/glfw/include)
target_include_directories(client PRIVATE extern/SFML/include)

target_link_libraries(client PRIVATE pybind11::embed)
target_link_libraries(client PRIVATE glfw)
target_link_libraries(client PRIVATE sfml-network)

find_package(OpenGL REQUIRED)
target_link_libraries(client PRIVATE OpenGL::GL)

#include(FetchContent)
##FetchContent_Declare(SFML
#    GIT_REPOSITORY https://github.com/SFML/SFML.git
#    GIT_TAG 2.6.1)
#FetchContent_MakeAvailable(SFML)
#target_link_libraries(client PRIVATE sfml-network)

install(TARGETS client)
