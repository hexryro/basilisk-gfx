cmake_minimum_required(VERSION 3.23.2)
project(basilisk-test-runner)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES "src/*.c")

file(GLOB_RECURSE HEADER_FILES "include/*.h")
file(GLOB PROJECT_FILES "./*" LIST_DIRECTORIES false)

add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
    ${HEADER_FILES}

    ${VS_SHADER_FILES}
    ${FS_SHADER_FILES}
)

set_property(TARGET ${PROJECT_NAME}
    PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
    "${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME}/$<CONFIG>"
)

source_group("Source Files" FILES ${SOURCE_FILES})
source_group("Headers" FILES ${HEADER_FILES})
source_group("Project Files" FILES ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/basilisk-core/include
   # ${CMAKE_SOURCE_DIR}/basilisk-steam/include
    ${CMAKE_SOURCE_DIR}/basilisk-gfx/include
    ${CMAKE_SOURCE_DIR}/basilisk-gfx/src
    ${CMAKE_SOURCE_DIR}/basilisk-mod/include
    ${CMAKE_SOURCE_DIR}/basilisk-mod/src
    ${CMAKE_SOURCE_DIR}/basilisk-test/include
    ${CMAKE_SOURCE_DIR}/external
    include/
    src/
    ${CMAKE_SOURCE_DIR}/include/objects/
    levels/
)

add_dependencies(${PROJECT_NAME}
    basilisk-core
   # basilisk-steam
    basilisk-gfx
    basilisk-mod
    basilisk-test
)

target_link_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/external/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    basilisk-core
   # basilisk-steam
    basilisk-gfx
    vulkan-1 
   # steam_api64 
    dwmapi
)

SET(CONTENT_COPY_RELEASE_DEBUG ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/../content" "${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo/content")
SET(CONTENT_COPY_RELEASE ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/../content" "${CMAKE_CURRENT_BINARY_DIR}/Release/content")
SET(CONTENT_LINK cmd.exe /c mklink /j "\"${CMAKE_CURRENT_BINARY_DIR}/Debug/content\"" "\"${PROJECT_SOURCE_DIR}/../content\"")

SET(COPY_BASILISK_CORE_DLL_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-core/Debug/basilisk-core.dll" "${CMAKE_CURRENT_BINARY_DIR}/Debug")
SET(COPY_BASILISK_CORE_DLL_RELEASE ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-core/Release/basilisk-core.dll" "${CMAKE_CURRENT_BINARY_DIR}/Release")
SET(COPY_BASILISK_CORE_DLL_RELEASE_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-core/RelWithDebInfo/basilisk-core.dll" "${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo")

SET(COPY_BASILISK_GFX_DLL_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-gfx/Debug/basilisk-gfx.dll" "${CMAKE_CURRENT_BINARY_DIR}/Debug")
SET(COPY_BASILISK_GFX_DLL_RELEASE ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-gfx/Release/basilisk-gfx.dll" "${CMAKE_CURRENT_BINARY_DIR}/Release")
SET(COPY_BASILISK_GFX_DLL_RELEASE_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-gfx/RelWithDebInfo/basilisk-gfx.dll" "${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo")

SET(COPY_BASILISK_MOD_DLL_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-mod/Debug/basilisk-mod.dll" "${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME}/Debug/")
SET(COPY_BASILISK_MOD_DLL_RELEASE ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-mod/Release/basilisk-mod.dll" "${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME}/Release")
SET(COPY_BASILISK_MOD_DLL_RELEASE_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-mod/RelWithDebInfo/basilisk-mod.dll" "${CMAKE_SOURCE_DIR}/build/${PROJECT_NAME}/RelWithDebInfo")

SET(COPY_BASILISK_TEST_DLL_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-test/Debug/basilisk-test.dll" "${CMAKE_CURRENT_BINARY_DIR}/Debug")
SET(COPY_BASILISK_TEST_DLL_RELEASE ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-test/Release/basilisk-test.dll" "${CMAKE_CURRENT_BINARY_DIR}/Release")
SET(COPY_BASILISK_TEST_DLL_RELEASE_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-test/RelWithDebInfo/basilisk-test.dll" "${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo")

SET(CLEAN_BUILD_DEBUG ${CMAKE_COMMAND} -E rm -r ${CMAKE_CURRENT_BINARY_DIR}/Debug)
SET(CLEAN_BUILD_RELEASE ${CMAKE_COMMAND} -E rm -r ${CMAKE_CURRENT_BINARY_DIR}/Release)
SET(CLEAN_BUILD_RELEASE_DEBUG ${CMAKE_COMMAND} -E rm -r ${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo)

#SET(COPY_GFSDK_DLL_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${BS_APP_NAME}/copy/GFSDK_Aftermath_Lib.x64.dll" "${CMAKE_CURRENT_BINARY_DIR}/Debug")
#SET(COPY_GFSDK_DLL_RELEASE ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${BS_APP_NAME}/copy/GFSDK_Aftermath_Lib.x64.dll" "${CMAKE_CURRENT_BINARY_DIR}/Release")
#SET(COPY_GFSDK_DLL_RELEASE_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${BS_APP_NAME}/copy/GFSDK_Aftermath_Lib.x64.dll" "${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo")

#SET(COPY_STEAM_DLL_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${BS_APP_NAME}/copy/steam_api64.dll" "${CMAKE_CURRENT_BINARY_DIR}/Debug")
#SET(COPY_STEAM_DLL_RELEASE ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${BS_APP_NAME}/copy/steam_api64.dll" "${CMAKE_CURRENT_BINARY_DIR}/Release")
#SET(COPY_STEAM_DLL_RELEASE_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/${BS_APP_NAME}/copy/steam_api64.dll" "${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo")

add_custom_command(
    TARGET ${PROJECT_NAME} 
    PRE_BUILD

    COMMAND "$<$<CONFIG:Debug>:${CLEAN_BUILD_DEBUG}>" COMMENT "PRE_BUILD: Cleaning Debug/"

	COMMAND_EXPAND_LISTS
	CONFIGURATIONS Debug
)

add_custom_command(
    TARGET ${PROJECT_NAME} 
    PRE_BUILD

    COMMAND "$<$<CONFIG:Release>:${CLEAN_BUILD_RELEASE}>" COMMENT "PRE_BUILD: Cleaning Release/"

	COMMAND_EXPAND_LISTS
	CONFIGURATIONS Release
)

add_custom_command(
    TARGET ${PROJECT_NAME} 
    PRE_BUILD

    COMMAND "$<$<CONFIG:RelWithDebInfo>:${CLEAN_BUILD_RELEASE_DEBUG}>" COMMENT "PRE_BUILD: Cleaning RelWithDebInfo/"

	COMMAND_EXPAND_LISTS
	CONFIGURATIONS RelWithDebInfo
)


SET(PROJECT_LINK_DEBUG cmd.exe /c mklink /j "\"${CMAKE_CURRENT_BINARY_DIR}/Debug/project\"" "\"${PROJECT_SOURCE_DIR}/..\"")
SET(PROJECT_LINK_RELEASE cmd.exe /c mklink /j "\"${CMAKE_CURRENT_BINARY_DIR}/Release/project\"" "\"${PROJECT_SOURCE_DIR}/..\"")
SET(PROJECT_LINK_RELEASE_DEBUG cmd.exe /c mklink /j "\"${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo/project\"" "\"${PROJECT_SOURCE_DIR}/..\"")

add_custom_command(
    TARGET ${PROJECT_NAME} 
    POST_BUILD
    #COMMAND "$<$<CONFIG:Debug>:${COPY_GFSDK_DLL_DEBUG}>" COMMENT "POST_BUILD: Copying GFSDK_Aftermath_Lib.x64.dll/"
   # COMMAND "$<$<CONFIG:Debug>:${COPY_STEAM_DLL_DEBUG}>" COMMENT "POST_BUILD: Copying steam_api64.dll/"
    COMMAND "$<$<CONFIG:Debug>:${COPY_BASILISK_CORE_DLL_DEBUG}>" COMMENT "POST_BUILD: Copying basilisk.dll/"
    COMMAND "$<$<CONFIG:Debug>:${COPY_BASILISK_GFX_DLL_DEBUG}>" COMMENT "POST_BUILD: Copying basilisk-gfx.dll/"
    COMMAND "$<$<CONFIG:Debug>:${COPY_BASILISK_MOD_DLL_DEBUG}>" COMMENT "POST_BUILD: Copying basilisk-mod.dll/"
    COMMAND "$<$<CONFIG:Debug>:${COPY_BASILISK_TEST_DLL_DEBUG}>" COMMENT "POST_BUILD: Copying basilisk-test.dll/"
    COMMAND "$<$<CONFIG:Debug>:${CONTENT_LINK}>" COMMENT "POST_BUILD: Creating junction to content/"
    COMMAND "$<$<CONFIG:Debug>:${PROJECT_LINK_DEBUG}>" COMMENT "POST_BUILD: Creating project junction"
    COMMAND_EXPAND_LISTS
	CONFIGURATIONS Debug
)

add_custom_command(
    TARGET ${PROJECT_NAME} 
    POST_BUILD
    #COMMAND "$<$<CONFIG:Release>:${COPY_GFSDK_DLL_RELEASE}>" COMMENT "POST_BUILD: Copying GFSDK_Aftermath_Lib.x64.dll/"
   # COMMAND "$<$<CONFIG:Release>:${COPY_STEAM_DLL_RELEASE}>" COMMENT "POST_BUILD: Copying steam_api64.dll/"
    COMMAND "$<$<CONFIG:Release>:${COPY_BASILISK_CORE_DLL_RELEASE}>" COMMENT "POST_BUILD: Copying basilisk.dll/"
    COMMAND "$<$<CONFIG:Release>:${COPY_BASILISK_GFX_DLL_RELEASE}>" COMMENT "POST_BUILD: Copying basilisk-gfx.dll/"
    COMMAND "$<$<CONFIG:Release>:${COPY_BASILISK_MOD_DLL_RELEASE}>" COMMENT "POST_BUILD: Copying basilisk-mod.dll/"
    COMMAND "$<$<CONFIG:Release>:${COPY_BASILISK_TEST_DLL_RELEASE}>" COMMENT "POST_BUILD: Copying basilisk-test.dll/"
    COMMAND "$<$<CONFIG:Release>:${CONTENT_COPY_RELEASE}>" COMMENT "POST_BUILD: Copying content to Release/"
    COMMAND "$<$<CONFIG:Release>:${PROJECT_LINK_RELEASE}>" COMMENT "POST_BUILD: Creating project junction"
    COMMAND_EXPAND_LISTS
	CONFIGURATIONS Release
)

add_custom_command(
    TARGET ${PROJECT_NAME} 
    POST_BUILD
    #COMMAND "$<$<CONFIG:RelWithDebInfo>:${COPY_GFSDK_DLL_RELEASE_DEBUG}>" COMMENT "POST_BUILD: Copying GFSDK_Aftermath_Lib.x64.dll/"
   # COMMAND "$<$<CONFIG:RelWithDebInfo>:${COPY_STEAM_DLL_RELEASE_DEBUG}>" COMMENT "POST_BUILD: Copying steam_api64.dll/"
    COMMAND "$<$<CONFIG:RelWithDebInfo>:${COPY_BASILISK_CORE_DLL_RELEASE_DEBUG}>" COMMENT "POST_BUILD: Copying basilisk.dll/"
    COMMAND "$<$<CONFIG:RelWithDebInfo>:${COPY_BASILISK_GFX_DLL_RELEASE_DEBUG}>" COMMENT "POST_BUILD: Copying basilisk-gfx.dll/"
    COMMAND "$<$<CONFIG:RelWithDebInfo>:${COPY_BASILISK_MOD_DLL_RELEASE_DEBUG}>" COMMENT "POST_BUILD: Copying basilisk-mod.dll/"
    COMMAND "$<$<CONFIG:RelWithDebInfo>:${COPY_BASILISK_TEST_DLL_RELEASE_DEBUG}>" COMMENT "POST_BUILD: Copying basilisk-test.dll/"
    COMMAND "$<$<CONFIG:RelWithDebInfo>:${CONTENT_COPY_RELEASE_DEBUG}>" COMMENT "POST_BUILD: Copying content to RelWithDebInfo/"
    COMMAND "$<$<CONFIG:RelWithDebInfo>:${PROJECT_LINK_RELEASE_DEBUG}>" COMMENT "POST_BUILD: Creating project junction"
    COMMAND_EXPAND_LISTS
	CONFIGURATIONS RelWithDebInfo
)
