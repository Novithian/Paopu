########## -Paopu- ###############

cmake_minimum_required(VERSION 3.12.4)
set(cmake_cxx_standard 17)
project(paopu LANGUAGES CXX C)


add_library(${PROJECT_NAME} STATIC
	src/Core/Application.cpp
	src/Core/Logger.cpp
	src/Renderer/Renderer.cpp
)

#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../Paopu/vendor/spdlog" spdlog)

#set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw" )
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm")

target_include_directories(${PROJECT_NAME}
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/vendor/vulkan/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm"
)

#set( GLFW_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/lib-mingw-w64")
find_library(Vulkan_LIBS NAMES vulkan-1 vulkan PATHS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/vulkan/libs)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog glfw glm ${Vulkan_LIBS} -std=c++17)