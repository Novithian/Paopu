cmake_minimum_required(VERSION 3.12.4)
project (paopu_sandbox VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

################ Sandbox ####################
set( SRCS
    src/PaopuApplication.cpp
)
add_executable(${PROJECT_NAME} ${SRCS})

#find_package(paopu REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC paopu -std=c++17)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        "${PAOPU_INCLUDE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/../Paopu"
)
#target_precompile_headers(paopu PUBLIC "${CMAKE_CURRENT_SOUCE_DIR}/src/pch.h")

#message(STATUS :"blah blah Included!")