cmake_minimum_required(VERSION 3.20)
project(pilot)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

set(IMGUI_DIR "external/imgui")

set(IMGUI_SOURCE
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp)

add_executable(${PROJECT_NAME}
        ${IMGUI_SOURCE}
        src/PilotEngine.cpp
        src/Common.h
        src/Logger/Logger.h
        src/Util/StringUtil.h
        src/Util/FileUtil.h
        src/Shaders/Compile/ShaderCompiler.h
        src/Shaders/Compile/ShaderCompiler.cpp
        )

find_package(Vulkan)
if (NOT Vulkan_FOUND)
    message( FATAL_ERROR "Vulkan not found" )
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/shaders/out)

add_subdirectory("external/glfw")
find_package(glfw3 REQUIRED)

add_subdirectory("external/shaderc")

include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)

target_include_directories(${PROJECT_NAME} PUBLIC "external/glm")
target_include_directories(${PROJECT_NAME} PUBLIC "external/tinygltf")
target_include_directories(${PROJECT_NAME} PUBLIC "src")

target_link_libraries(${PROJECT_NAME} glfw Vulkan::Vulkan shaderc)
