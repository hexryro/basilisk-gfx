cmake_minimum_required(VERSION 3.23.2)
project(basilisk)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BS_APP_NAME ${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME})

add_subdirectory(basilisk-core/)
add_subdirectory(basilisk-gfx/)
add_subdirectory(basilisk-mod/)
add_subdirectory(basilisk-test/)
add_subdirectory(basilisk-test-runner/)
add_subdirectory(basilisk/)
