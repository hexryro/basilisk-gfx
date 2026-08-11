cmake_minimum_required(VERSION 3.23.2)
project(basilisk-mod)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES "src/*.c")

file(GLOB TYPE_FILES "src/types/*.*")

file(GLOB UI_FILES "src/ui/*.*")

file(GLOB VS_SHADER_FILES "resources/shaders/vert/*.*")
file(GLOB FS_SHADER_FILES "resources/shaders/frag/*.*")

file(GLOB_RECURSE GENERATE_FILES "generated/*.*")
file(GLOB_RECURSE HEADER_FILES "include/*.h")
file(GLOB PROJECT_FILES "./*" LIST_DIRECTORIES false)

add_library(${PROJECT_NAME} SHARED
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${GENERATE_FILES}

    ${UI_FILES}

    ${VS_SHADER_FILES}
    ${FS_SHADER_FILES}

    ${TYPE_FILES}
)

source_group("Views" FILES ${VIEWS})
source_group("Source Files" FILES ${SOURCE_FILES})

source_group("Shaders/vert" FILES ${VS_SHADER_FILES})
source_group("Shaders/frag" FILES ${FS_SHADER_FILES})

source_group("Source Files/UI" FILES ${UI_FILES})
source_group("Source Files/UI/Prefab" FILES ${UI_PREFAB_FILES})
source_group("Source Files/UI/Primitive" FILES ${UI_PRIMITIVE_FILES})
source_group("Source Files/UI/Instance" FILES ${UI_INSTANCE_FILESs})
source_group("Source Files/UI/Light" FILES ${UI_LIGHT_FILES})
source_group("Source Files/UI/Tile" FILES ${UI_TILE_FILES})
source_group("Source Files/UI/Type" FILES ${UI_TYPE_FILES})
source_group("Source Files/UI/Material" FILES ${UI_MATERIAL_FILES})
source_group("Source Files/UI/Context" FILES ${UI_CONTEXT_FILES})
source_group("Source Files/UI/Grid" FILES ${UI_GRID_FILES})
source_group("Source Files/UI/Side" FILES ${UI_SIDE_FILES})

source_group("Source Files/Types" FILES ${TYPE_FILES})
source_group("Project Files" FILES ${PROJECT_FILES})
source_group("Headers" FILES ${HEADER_FILES})
source_group("Generated Files" FILES ${GENERATE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/basilisk-core/include
    ${CMAKE_SOURCE_DIR}/basilisk-core/generated
    #${CMAKE_SOURCE_DIR}/basilisk-steam/include
    ${CMAKE_SOURCE_DIR}/basilisk-gfx/include
    ${CMAKE_SOURCE_DIR}/basilisk-gfx/generated
    ${CMAKE_SOURCE_DIR}/basilisk-gfx/src
    ${CMAKE_SOURCE_DIR}/basilisk-mod/include
    ${CMAKE_SOURCE_DIR}/external
    #${CMAKE_SOURCE_DIR}/external/GFSDK_Aftermath_Lib
    ${CMAKE_SOURCE_DIR}/external/glslang
    ${CMAKE_SOURCE_DIR}/external/SPIRV-Cross
    external/
    include/
    generated/
    src/
    ${CMAKE_SOURCE_DIR}/include/objects/
    ${CMAKE_SOURCE_DIR}/external/freetype/include
)

target_link_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/external/
    ${CMAKE_SOURCE_DIR}/external/glslang/build/glslang/Debug
    ${CMAKE_SOURCE_DIR}/external/glslang/build/SPIRV/Debug
    ${CMAKE_SOURCE_DIR}/external/SPIRV-Cross/build/Debug
    ${CMAKE_SOURCE_DIR}/external/freetype/objs
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /wd6255 /wd4047 /wd4090 /wd4024 /wd4133)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    basilisk-core
    basilisk-gfx
    #basilisk-steam
    vulkan-1 
    #steam_api64 
    dwmapi
    #GFSDK_Aftermath_Lib.x64
    GenericCodeGend
    glslangd optimized glslangd
    glslang-default-resource-limitsd optimized glslang-default-resource-limitsd
    MachineIndependentd optimized MachineIndependentd
    SPIRVd optimized SPIRVd
    spirv-cross-cd optimized spirv-cross-cd
    spirv-cross-cored optimized spirv-cross-cored
    spirv-cross-glsld optimized spirv-cross-glsld
    freetype
)
