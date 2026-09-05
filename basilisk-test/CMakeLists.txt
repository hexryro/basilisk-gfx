cmake_minimum_required(VERSION 3.23.2)
project(basilisk-test)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES "src/*.c")

file(GLOB_RECURSE HEADER_FILES "include/*.h")
file(GLOB PROJECT_FILES "./*" LIST_DIRECTORIES false)

file(GLOB VS_SHADER_FILES "shaders/vert/*.*")
file(GLOB FS_SHADER_FILES "shaders/frag/*.*")

add_library(${PROJECT_NAME} SHARED
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${VS_SHADER_FILES}
    ${FS_SHADER_FILES}
)

source_group("Source Files" FILES ${SOURCE_FILES})
source_group("Headers" FILES ${HEADER_FILES})
source_group("Project Files" FILES ${PROJECT_FILES})

source_group("Shaders/vert" FILES ${VS_SHADER_FILES})
source_group("Shaders/frag" FILES ${FS_SHADER_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/basilisk-core/include
   # ${CMAKE_SOURCE_DIR}/basilisk-steam/include
    ${CMAKE_SOURCE_DIR}/basilisk-gfx/include
    ${CMAKE_SOURCE_DIR}/basilisk-gfx/src
    ${CMAKE_SOURCE_DIR}/basilisk-mod/include
    ${CMAKE_SOURCE_DIR}/basilisk-mod/src
    ${CMAKE_SOURCE_DIR}/basilisk-test/tests
    ${CMAKE_SOURCE_DIR}/external
    include/
    src/
    ${CMAKE_SOURCE_DIR}/include/objects/
    levels/
)

target_link_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/external/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    basilisk-core
    basilisk-gfx
    basilisk-mod
   # basilisk-steam
    vulkan-1 
   # steam_api64 
    dwmapi
    #GFSDK_Aftermath_Lib.x64
)

SET(COPY_DLL_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-test/Debug/basilisk-test.dll" "${CMAKE_SOURCE_DIR}/build/basilisk-test-runner/Debug/")
SET(COPY_DLL_RELEASE ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-test/Release/basilisk-test.dll" "${CMAKE_SOURCE_DIR}/build/basilisk-test-runner/Release")
SET(COPY_DLL_RELEASE_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-test/RelWithDebInfo/basilisk-test.dll" "${CMAKE_SOURCE_DIR}/build/basilisk-test-runner/RelWithDebInfo")

add_custom_command(
    TARGET ${PROJECT_NAME} 
    POST_BUILD
    COMMAND "$<$<CONFIG:Debug>:${COPY_DLL_DEBUG}>" COMMENT "POST_BUILD: Copying basilisk-test.dll/"
	COMMAND_EXPAND_LISTS
    CONFIGURATIONS Debug
)

add_custom_command(
    TARGET ${PROJECT_NAME} 
    POST_BUILD
    COMMAND "$<$<CONFIG:Release>:${COPY_DLL_RELEASE}>" COMMENT "POST_BUILD: Copying basilisk-test.dll/"
	COMMAND_EXPAND_LISTS
    CONFIGURATIONS Release
)

add_custom_command(
    TARGET ${PROJECT_NAME} 
    POST_BUILD
    COMMAND "$<$<CONFIG:RelWithDebInfo>:${COPY_DLL_RELEASE_DEBUG}>" COMMENT "POST_BUILD: Copying basilisk-test.dll/"
	COMMAND_EXPAND_LISTS
    CONFIGURATIONS RelWithDebInfo
)