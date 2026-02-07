cmake_minimum_required(VERSION 3.21)

project(Vulkan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Vulkan
find_package(Vulkan REQUIRED)

add_executable(Vulkan
    src/main.cpp
)

# Include directories - C:/Include should contain vulkan/ and GLFW/ subdirectories
target_include_directories(Vulkan PRIVATE
    "C:/Include"
)

# Link libraries
target_link_libraries(Vulkan PRIVATE
    Vulkan::Vulkan
    "C:/Libs/glfw3.lib"
)