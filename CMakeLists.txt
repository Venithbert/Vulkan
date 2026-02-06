cmake_minimum_required(VERSION 3.21)

project(Vulkan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

add_executable(Vulkan
    src/main.cpp
)


target_include_directories(Vulkan PRIVATE
    "C:/Include"
)


target_link_libraries(Vulkan
    Vulkan::Vulkan
    "C:/Libs/glfw3.lib"
)