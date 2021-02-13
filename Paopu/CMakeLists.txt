cmake_minimum_required(VERSION 3.12.4)
project(paopu VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

################ PAOPU #####################
add_library( ${PROJECT_NAME} STATIC
   src/Application.cpp
    #
)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
#add_subdirectory(vendor/glfw)
add_compile_definitions(-DPAO_PLATFORM_WINDOWS)
target_include_directories( ${PROJECT_NAME}
    PRIVATE
        Paopu
    #"${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include"
)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME} EXPORT paopu_lib 
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDRI}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(EXPORT paopu_lib DESTINATION share/Paopu/cmake)

