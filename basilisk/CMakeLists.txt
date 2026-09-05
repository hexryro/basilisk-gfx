cmake_minimum_required(VERSION 3.23.2)
project(basilisk)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES "src/*.c")
file(GLOB UI_FILES "src/ui/*.c")

file(GLOB_RECURSE HEADER_FILES "include/*.h")
file(GLOB PROJECT_FILES "./*" LIST_DIRECTORIES false)

file(GLOB XML_FILES "../xml/*.*")

add_executable(${PROJECT_NAME}
    ${XML_FILES}
    ${UI_FILES}
    ${SOURCE_FILES}
    ${HEADER_FILES}

    ${VS_SHADER_FILES}
    ${FS_SHADER_FILES}
)

set_property(TARGET ${PROJECT_NAME}
    PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
    "${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME}/$<CONFIG>"
)

source_group("UI" FILES ${UI_FILES})
source_group("Source Files" FILES ${SOURCE_FILES})
source_group("Headers" FILES ${HEADER_FILES})
source_group("Project Files" FILES ${PROJECT_FILES})
source_group("XML Files" FILES ${XML_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/basilisk-core/include
    ${CMAKE_SOURCE_DIR}/basilisk-gfx/include
    ${CMAKE_SOURCE_DIR}/basilisk-mod/include

    ${CMAKE_SOURCE_DIR}/basilisk-core/generated
    ${CMAKE_SOURCE_DIR}/basilisk-gfx/generated
    ${CMAKE_SOURCE_DIR}/basilisk-mod/generated

    ${CMAKE_SOURCE_DIR}/external
    include/
    src/
)

add_dependencies(${PROJECT_NAME}
    basilisk-core
    basilisk-gfx
    basilisk-mod
)

target_link_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/external/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    basilisk-core
    basilisk-gfx
    basilisk-mod
    vulkan-1
    dwmapi
)

set(PROJECT_LINK
    cmd.exe /c
    "mklink /J \"${CMAKE_CURRENT_BINARY_DIR}/Debug/project\" \"${PROJECT_SOURCE_DIR}/..\" || exit /b 0"
)

set(CONTENT_LINK
    cmd.exe /c
    "mklink /J \"${CMAKE_CURRENT_BINARY_DIR}/Debug/content\" \"${PROJECT_SOURCE_DIR}/../content\" || exit /b 0"
)

set(CONTENT_COPY_RELEASE
    ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/../content"
    "${CMAKE_CURRENT_BINARY_DIR}/Release/content"
)

set(CONTENT_COPY_RELEASE_DEBUG
    ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/../content"
    "${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo/content"
)

set(RESOURCE_CREATE_CONTENT_DIRECTORY_RELEASE_DEBUG
    ${CMAKE_COMMAND} -E make_directory
    "${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo/content"
)

set(RESOURCE_CREATE_CONTENT_DIRECTORY_RELEASE
    ${CMAKE_COMMAND} -E make_directory
    "${CMAKE_CURRENT_BINARY_DIR}/Release/content"
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "$<$<CONFIG:Debug>:${PROJECT_LINK}>" COMMENT "POST_BUILD: Creating junction to /"
    COMMAND "$<$<CONFIG:Debug>:${CONTENT_LINK}>" COMMENT "POST_BUILD: Creating junction to content/"
    COMMAND_EXPAND_LISTS
    CONFIGURATIONS Debug
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "$<$<CONFIG:Release>:${RESOURCE_CREATE_CONTENT_DIRECTORY_RELEASE}>" COMMENT "POST_BUILD: Creating content/ directory in Release/"
    COMMAND "$<$<CONFIG:Release>:${CONTENT_COPY_RELEASE}>" COMMENT "POST_BUILD: Copying content to Release/"
    COMMAND_EXPAND_LISTS
    CONFIGURATIONS Release
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "$<$<CONFIG:RelWithDebInfo>:${RESOURCE_CREATE_CONTENT_DIRECTORY_RELEASE_DEBUG}>" COMMENT "POST_BUILD: Creating content/ directory in RelWithDebInfo/"
    COMMAND "$<$<CONFIG:RelWithDebInfo>:${CONTENT_COPY_RELEASE_DEBUG}>" COMMENT "POST_BUILD: Copying content to RelWithDebInfo/"
    COMMAND_EXPAND_LISTS
    CONFIGURATIONS RelWithDebInfo
)
