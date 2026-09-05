cmake_minimum_required(VERSION 3.23.2)
project(basilisk-gfx)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE GENERATED_FILES "generated/*.*")
file(GLOB SOURCE_FILES "src/*.c")
file(GLOB TYPE_FILES "src/types/*.*")

file(GLOB_RECURSE GLSL_FILES "shaders/*.glsl")
file(GLOB_RECURSE FRAG_FILES "shaders/*.frag")
file(GLOB_RECURSE VERT_FILES "shaders/*.vert")
file(GLOB_RECURSE COMP_FILES "shaders/*.comp")
file(GLOB_RECURSE RGEN_FILES "shaders/*.rgen")
file(GLOB_RECURSE RMISS_FILES "shaders/*.rmiss")

file(GLOB_RECURSE HEADER_FILES "include/*.h")
file(GLOB PROJECT_FILES "./*" LIST_DIRECTORIES false)

add_library(${PROJECT_NAME} SHARED
    bsgfx_contracts.h

    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${GENERATED_FILES}

    ${GLSL_FILES}
    ${FRAG_FILES}
    ${VERT_FILES}
    ${COMP_FILES}
    ${RGEN_FILES}
    ${RMISS_FILES}

    ${TYPE_FILES}
)

source_group("Source Files" FILES ${SOURCE_FILES})
source_group("Generated Files" FILES ${GENERATED_FILES})

source_group("Shaders" FILES ${GLSL_FILES})
source_group("Shaders/vert" FILES ${VERT_FILES})
source_group("Shaders/frag" FILES ${FRAG_FILES})
source_group("Shaders/comp" FILES ${COMP_FILES})
source_group("Shaders/rgen" FILES ${RGEN_FILES})
source_group("Shaders/rmiss" FILES ${RMISS_FILES})

source_group("Source Files/Types" FILES ${TYPE_FILES})

source_group("Headers" FILES ${HEADER_FILES})
source_group("Project Files" FILES ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/basilisk-core/generated
    ${CMAKE_SOURCE_DIR}/basilisk-core/include
    #${CMAKE_SOURCE_DIR}/basilisk-steam/include
    ${CMAKE_SOURCE_DIR}/external
    #${CMAKE_SOURCE_DIR}/external/GFSDK_Aftermath_Lib
    ${CMAKE_SOURCE_DIR}/external/vulkan
    generated/
    include/
    src/
    ${CMAKE_SOURCE_DIR}/include/objects/
    levels/
    ${CMAKE_SOURCE_DIR}/external/freetype/include
)

target_link_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/external/
    ${CMAKE_SOURCE_DIR}/external/freetype/objs
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    basilisk-core
    #basilisk-steam
    vulkan-1
    dwmapi
    #GFSDK_Aftermath_Lib.x64
    freetype
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /wd6255 /wd4047 /wd4090 /wd4024 /wd4133)
endif()

SET(COPY_BASILISK_GFX_DLL_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-gfx/Debug/basilisk-gfx.dll" "${CMAKE_SOURCE_DIR}/build/${BS_APP_NAME}/Debug/")
SET(COPY_BASILISK_GFX_DLL_RELEASE ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-gfx/Release/basilisk-gfx.dll" "${CMAKE_SOURCE_DIR}/build/${BS_APP_NAME}/Release")
SET(COPY_BASILISK_GFX_DLL_RELEASE_DEBUG ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-gfx/RelWithDebInfo/basilisk-gfx.dll" "${CMAKE_SOURCE_DIR}/build/${BS_APP_NAME}/RelWithDebInfo")

SET(COPY_BASILISK_GFX_DLL_DEBUG_TO_TEST ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-gfx/Debug/basilisk-gfx.dll" "${CMAKE_SOURCE_DIR}/build/basilisk-test-runner/Debug/")
SET(COPY_BASILISK_GFX_DLL_RELEASE_TO_TEST ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-gfx/Release/basilisk-gfx.dll" "${CMAKE_SOURCE_DIR}/build/basilisk-test-runner/Release")
SET(COPY_BASILISK_GFX_DLL_RELEASE_DEBUG_TO_TEST ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/build/basilisk-gfx/RelWithDebInfo/basilisk-gfx.dll" "${CMAKE_SOURCE_DIR}/build/basilisk-test-runner/RelWithDebInfo")

#add_custom_command(
#    TARGET ${PROJECT_NAME} 
#    POST_BUILD
#    COMMAND "$<$<CONFIG:Debug>:${COPY_BASILISK_GFX_DLL_DEBUG}>" COMMENT "POST_BUILD: Copying basilisk-gfx.dll/"
#    COMMAND "$<$<CONFIG:Debug>:${COPY_BASILISK_GFX_DLL_DEBUG_TO_TEST}>" COMMENT "POST_BUILD: Copying basilisk-gfx.dll/ to test"
#	COMMAND_EXPAND_LISTS
#    CONFIGURATIONS Debug
#)
#
#add_custom_command(
#    TARGET ${PROJECT_NAME} 
#    POST_BUILD
#    COMMAND "$<$<CONFIG:Release>:${COPY_BASILISK_GFX_DLL_RELEASE}>" COMMENT "POST_BUILD: Copying basilisk-gfx.dll/"
#    COMMAND "$<$<CONFIG:Release>:${COPY_BASILISK_GFX_DLL_RELEASE_TO_TEST}>" COMMENT "POST_BUILD: Copying basilisk-gfx.dll/ to test"
#	COMMAND_EXPAND_LISTS
#    CONFIGURATIONS Release
#)
#
#add_custom_command(
#    TARGET ${PROJECT_NAME} 
#    POST_BUILD
#    COMMAND "$<$<CONFIG:RelWithDebInfo>:${COPY_BASILISK_GFX_DLL_RELEASE_DEBUG}>" COMMENT "POST_BUILD: Copying basilisk-gfx.dll/"
#    COMMAND "$<$<CONFIG:RelWithDebInfo>:${COPY_BASILISK_GFX_DLL_RELEASE_DEBUG_TO_TEST}>" COMMENT "POST_BUILD: Copying basilisk-gfx.dll/ to test"
#	COMMAND_EXPAND_LISTS
#    CONFIGURATIONS RelWithDebInfo
#)