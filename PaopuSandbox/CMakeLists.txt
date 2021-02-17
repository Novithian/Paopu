########## -Sandbox- ###########
cmake_minimum_required(VERSION 3.12.4)
project(paopu_sandbox LANGUAGES CXX C)

set(cmake_cxx_standard 17)

set( SRCS
    src/PaopuSandbox.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin")

#set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
#list(APPEND CMAKE_MODULE_PATH "../cmake")
#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../Paopu/vendor/spdlog")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../Paopu" paopu)
add_executable(${PROJECT_NAME} ${SRCS})

find_library(Vulkan_LIBS NAMES vulkan-1 vulkan PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../Paopu/vendor/vulkan/libs)
target_link_libraries(${PROJECT_NAME} PUBLIC paopu spdlog::spdlog ${Vulkan_LIBS} glfw ${GLFW_LIBRARIES} -std=c++17)
target_include_directories(${PROJECT_NAME}
    PUBLIC 
        "${CMAKE_CURRENT_SOURCE_DIR}/../Paopu/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/../Paopu/vendor/spdlog/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/../Paopu/vendor/glfw/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/../Paopu/vendor/vulkan/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/../Paopu/vendor/glm"

)
