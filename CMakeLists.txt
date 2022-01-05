cmake_minimum_required(VERSION 3.20)
project(pilot)

set(CMAKE_CXX_STANDARD 20)

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
        src/PilotEngine.cpp
        src/Logger/Logger.h
        src/Util/StringUtil.h
        ${IMGUI_SOURCE})

find_package(Vulkan)
if (NOT Vulkan_FOUND)
    message( FATAL_ERROR "Vulkan not found" )
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

add_subdirectory("external/glfw")
find_package(glfw3 REQUIRED)

include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)

target_include_directories(${PROJECT_NAME} PUBLIC "external/glm")
target_include_directories(${PROJECT_NAME} PUBLIC "external/tinygltf")

target_link_libraries(${PROJECT_NAME} glfw Vulkan::Vulkan)
