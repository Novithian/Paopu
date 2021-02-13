################ PAOPU #####################

cmake_minimum_required(VERSION 3.12.4)
project(paopu VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

#find_package(spdlog REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/Paopu/vendor/spdlog")

add_library( ${PROJECT_NAME} STATIC
   Paopu/src/Core/Application.cpp
   Paopu/src/Core/Logger.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

add_subdirectory(Paopu/vendor/spdlog)


#add_compile_definitions(PAO_PLATFORM_WINDOWS)
target_include_directories( ${PROJECT_NAME}
    PUBLIC
        paopu
        "${CMAKE_CURRENT_SOURCE_DIR}/Paopu/vendor/spdlog/include"
    #"${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include"
)

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
#include(GNUInstallDirs)

#install(TARGETS ${PROJECT_NAME} EXPORT paopu_lib 
#   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDRI}
#   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
#install(EXPORT paopu_lib DESTINATION share/Paopu/cmake)


################ Sandbox ####################

cmake_minimum_required(VERSION 3.12.4)
project(paopu_application VERSION 0.1.0 LANGUAGES CXX C)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set( SRCS
    PaopuSandbox/src/PaopuApplication.cpp
)
add_executable(paupo_application ${SRCS})

#find_package(paopu REQUIRED)

target_link_libraries(paupo_application PUBLIC paopu spdlog::spdlog -std=c++17)
target_include_directories(paupo_application
    PUBLIC
        #"${PAOPU_INCLUDE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/Paopu"
        "${CMAKE_CURRENT_SOURCE_DIR}/Paopu/vendor/spdlog/include"
)