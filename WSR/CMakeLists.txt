include(FetchContent)
cmake_minimum_required(VERSION 3.17)

project(WSR)

set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
    wsr
    SOURCE_DIR ../
)
FetchContent_MakeAvailable(wsr)

add_executable (WSR "WSR.cpp" "WSR.hpp" "src/Renderer.cpp" "src/Window.cpp")

target_compile_options(WSR PUBLIC "")

target_link_libraries(
    WSR
    glad
    glfw
	glm
)
# TODO: Add tests and install targets if needed.
