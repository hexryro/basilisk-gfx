cmake_minimum_required(VERSION 3.23.2)

project(basilisk-core)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE LODEPNG_FILES "${CMAKE_SOURCE_DIR}/external/lodepng/*.*")
file(GLOB_RECURSE YYJSON_FILES "${CMAKE_SOURCE_DIR}/external/yyjson/*.*")
file(GLOB_RECURSE SOURCE_FILES "src/*.c")
file(GLOB_RECURSE HEADER_FILES "include/*.h")
file(GLOB_RECURSE GENERATED_FILES "generated/*.*")

add_library(${PROJECT_NAME} SHARED
    ${LODEPNG_FILES}
    ${YYJSON_FILES}
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${GENERATED_FILES}
)

if (UNIX)
    add_definitions(-W)

    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wno-discarded-qualifiers
        -Wdiscarded-array-qualifiers
        -Wsign-compare
    )
endif()

source_group("External Files" FILES ${LODEPNG_FILES} ${YYJSON_FILES})
source_group("Source Files" FILES ${SOURCE_FILES})
source_group("Header Files" FILES ${HEADER_FILES})
source_group("Generated Files" FILES ${GENERATED_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    include/
    generated/
    ${CMAKE_SOURCE_DIR}/external/
    ${CMAKE_SOURCE_DIR}/external/lodepng
    ${CMAKE_SOURCE_DIR}/external/yyjson
    ${CMAKE_SOURCE_DIR}/external/cglm-0.9.6/include
    ${CMAKE_SOURCE_DIR}/external/vulkan
)

target_link_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/external/
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /wd6255 /wd4047 /wd4090 /wd4024 /wd4133)
endif()

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        vulkan-1
        dwmapi
        winhttp
        httpapi
        ws2_32
        dbghelp
    )
endif ()

if (UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        vulkan
        dl
    )
endif ()

SET(COPY_BASILISK_DLL_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-core/Debug/basilisk-core.dll" "${CMAKE_SOURCE_DIR}/build/${BS_APP_NAME}/Debug/")
SET(COPY_BASILISK_DLL_RELEASE ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-core/Release/basilisk-core.dll" "${CMAKE_SOURCE_DIR}/build/${BS_APP_NAME}/Release")
SET(COPY_BASILISK_DLL_RELEASE_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-core/RelWithDebInfo/basilisk-core.dll" "${CMAKE_SOURCE_DIR}/build/${BS_APP_NAME}/RelWithDebInfo")

SET(COPY_BASILISK_DLL_DEBUG_TO_TEST ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-core/Debug/basilisk-core.dll" "${CMAKE_SOURCE_DIR}/build/basilisk-test-runner/Debug/")
SET(COPY_BASILISK_DLL_RELEASE_TO_TEST ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-core/Release/basilisk-core.dll" "${CMAKE_SOURCE_DIR}/build/basilisk-test-runner/Release")
SET(COPY_BASILISK_DLL_RELEASE_DEBUG_TO_TEST ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-core/RelWithDebInfo/basilisk-core.dll" "${CMAKE_SOURCE_DIR}/build/basilisk-test-runner/RelWithDebInfo")

#add_custom_command(
#    TARGET ${PROJECT_NAME}
#    POST_BUILD
#    COMMAND "$<$<CONFIG:Debug>:${COPY_BASILISK_DLL_DEBUG}>" COMMENT "POST_BUILD: Copying basilisk.dll/"
#    COMMAND "$<$<CONFIG:Debug>:${COPY_BASILISK_DLL_DEBUG_TO_TEST}>" COMMENT "POST_BUILD: Copying basilisk.dll/ to test"
#	COMMAND_EXPAND_LISTS
#    CONFIGURATIONS Debug
#)

#add_custom_command(
#    TARGET ${PROJECT_NAME}
#    POST_BUILD
#    COMMAND "$<$<CONFIG:Release>:${COPY_BASILISK_DLL_RELEASE}>" COMMENT "POST_BUILD: Copying basilisk.dll/"
#    COMMAND "$<$<CONFIG:Release>:${COPY_BASILISK_DLL_RELEASE_TO_TEST}>" COMMENT "POST_BUILD: Copying basilisk.dll/ to test"
#	COMMAND_EXPAND_LISTS
#    CONFIGURATIONS Release
#)

#add_custom_command(
#    TARGET ${PROJECT_NAME}
#    POST_BUILD
#    COMMAND "$<$<CONFIG:RelWithDebInfo>:${COPY_BASILISK_DLL_RELEASE_DEBUG}>" COMMENT "POST_BUILD: Copying basilisk.dll/"
#    COMMAND "$<$<CONFIG:RelWithDebInfo>:${COPY_BASILISK_DLL_RELEASE_DEBUG_TO_TEST}>" COMMENT "POST_BUILD: Copying basilisk.dll/ to test"
#	COMMAND_EXPAND_LISTS
#    CONFIGURATIONS RelWithDebInfo
#)
