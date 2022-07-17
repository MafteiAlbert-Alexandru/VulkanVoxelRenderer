cmake_minimum_required(VERSION 3.0)
project(VulkanVoxelRenderer VERSION 1.0) 
set(CXX_STANDARD 20)

set(GLFW_LIBRARY_TYPE SHARED)
set(BUILD_SHARED_LIBS 1)

add_subdirectory(lib/Vulkan-Hpp)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)
add_executable(${PROJECT_NAME} src/main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra)

target_include_directories(${PROJECT_NAME} PUBLIC lib/Vulkan-Hpp)
target_include_directories(${PROJECT_NAME} PUBLIC lib/glfw/include)
target_include_directories(${PROJECT_NAME} PUBLIC lib/glm)

target_link_libraries(${PROJECT_NAME} glfw glm vulkan)
file(GLOB_RECURSE shaders "*.vs" "*.fs" "*.vert" "*.frag" "*.compute" "*.cs")
file(COPY ${shaders} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shd)