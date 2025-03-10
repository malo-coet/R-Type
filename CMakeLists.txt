cmake_minimum_required(VERSION 3.17)

# Setup vcpkg script with CMake (note: should be placed before project() call)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(
    RType
    VERSION 1.0
    DESCRIPTION "RType game"
    LANGUAGES CXX
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "CMake generator" FORCE)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CLIENT_DIR "${CMAKE_SOURCE_DIR}/RType/Client")
set(GAMEENGINE_DIR "${CMAKE_SOURCE_DIR}/RType/GameEngine")
set(SERVER_DIR "${CMAKE_SOURCE_DIR}/RType/Server")
set(COMMONLIB_DIR "${CMAKE_SOURCE_DIR}/RType/CommonLib")
set(TESTS_DIR "${CMAKE_SOURCE_DIR}/tests")

option(BUILD_DOC "Build documentation" OFF)
option(BUILD_TESTS "Build with '--coverage'" OFF)

if (BUILD_DOC)
    add_subdirectory(doc)
    return()
endif (BUILD_DOC)

if (BUILD_TESTS)
    find_package(Catch2 CONFIG REQUIRED)
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(--coverage)
        add_link_options(--coverage)
        add_subdirectory(${TESTS_DIR})
    endif ()
endif ()

if (WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/build/debug-windows/vcpkg_installed/x64-windows/lib)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_library(ENET_LIBRARY enet REQUIRED)
find_package(MPG123 REQUIRED)

if (WIN32)
    set(SYSTEM_LIBS ws2_32 winmm)
endif()

add_subdirectory(${CLIENT_DIR})
add_subdirectory(${GAMEENGINE_DIR})
add_subdirectory(${SERVER_DIR})
add_subdirectory(${COMMONLIB_DIR})

if (WIN32)
    target_link_libraries(r-type_game_engine PRIVATE ${SYSTEM_LIBS})
    target_link_libraries(r-type_server PRIVATE ${SYSTEM_LIBS})
    target_link_libraries(r-type_client PRIVATE ${SYSTEM_LIBS})
endif()