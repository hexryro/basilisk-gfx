
 /**
  MIT License
  
  Copyright (c) 2026 switch360hardflip <switch360hardflip@gmail.com>
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
  */ 

 /**
  This file was generated from basilisk-gfx.com

  It is not recommended to make changes to this file as it will be lost if
  the code is regenerated.
  */
        
#include <basilisk-gfx.h>
#include <bsgfx_internal.gen.h>
#include <bsgfx_prevalidation.gen.h>
#include <bsgfx_validation.gen.h>
#include <math.h>
#include <stdio.h>

static bsgfx_FunctionTable next = { 0 };

const bsgfx_FunctionTable* _bsgfx_setFunctions(const bsgfx_FunctionTable* a, bsgfx_FunctionTable* b) {
    memcpy(&next, a, sizeof(next));

	if (!b) return &next;

    for (size_t offset = 0; offset < sizeof(bsgfx_FunctionTable); offset += sizeof(void*)) {
        bs_Callback* f_a = ((unsigned char*)&next) + offset;
        bs_Callback* f_b = ((unsigned char*)b) + offset;
        if (!*f_a) 
            *f_a = *f_b;
    }

    return &next;
}

void bsgfx_enableValidation()
{
    bsgfx_FunctionTable* definitions = _bsgfx_getFunctions();
    bsgfx_FunctionTable* preval_definitions = _preval_bsgfx_getFunctions();
    bsgfx_FunctionTable* val_definitions = _val_bsgfx_getFunctions();
    val_definitions = _preval_bsgfx_setFunctions(val_definitions, definitions);
    preval_definitions = _bsgfx_setFunctions(preval_definitions, val_definitions);
}

void bsgfx_disableValidation()
{
    bsgfx_FunctionTable* definitions = _bsgfx_getFunctions();
    _bsgfx_setFunctions(definitions, NULL);
}

void bsgfx_test()
{
    next.bsgfx_test();
}

bsgfx_InstanceSubtype** bsgfx_subtypes()
{
    return next.bsgfx_subtypes();
}

bsgfx_InstanceType** bsgfx_instanceTypes()
{
    return next.bsgfx_instanceTypes();
}

void bsgfx_textDimensions(
    bsgfx_Font* font, 
    bs_vec2* out, 
    char* name, 
    int length)
{
    next.bsgfx_textDimensions(font, out, name, length);
}

bs_PipelineHash bsgfx_defaultPipelineHash()
{
    return next.bsgfx_defaultPipelineHash();
}

void bsgfx_renderTileIcons(
    bs_RendererScope* scope, 
    bs_Queue* queue)
{
    next.bsgfx_renderTileIcons(scope, queue);
}

void bsgfx_renderAtlasIcons(
    bs_RendererScope* scope, 
    bs_Queue* queue)
{
    next.bsgfx_renderAtlasIcons(scope, queue);
}

void bsgfx_renderLineModel(
    bs_RendererScope* scope, 
    bs_Queue* queue, 
    const bs_mat4* camera, 
    bsgfx_InstanceSubtype* subtype, 
    bool skip_depth_test)
{
    next.bsgfx_renderLineModel(scope, queue, camera, subtype, skip_depth_test);
}

void bsgfx_renderLines(
    bs_RendererScope* scope, 
    bs_Queue* queue, 
    const bs_mat4* camera, 
    bsgfx_InstanceSubtype* subtype, 
    bool skip_depth_test)
{
    next.bsgfx_renderLines(scope, queue, camera, subtype, skip_depth_test);
}

void bsgfx_renderPoints(
    bs_RendererScope* scope, 
    bs_Queue* queue)
{
    next.bsgfx_renderPoints(scope, queue);
}

void bsgfx_renderAtlas(
    bs_RendererScope* scope, 
    bs_Queue* queue)
{
    next.bsgfx_renderAtlas(scope, queue);
}

void bsgfx_renderPrimitiveTiles(
    bs_RendererScope* scope, 
    bs_Queue* queue)
{
    next.bsgfx_renderPrimitiveTiles(scope, queue);
}

void bsgfx_swapBufferBindings()
{
    next.bsgfx_swapBufferBindings();
}

void bsgfx_requiredForShadowVolumes(
    bs_PipelineHash* inout)
{
    next.bsgfx_requiredForShadowVolumes(inout);
}

void bsgfx_requiredForStencilShadows(
    bs_PipelineHash* inout)
{
    next.bsgfx_requiredForStencilShadows(inout);
}

void bsgfx_requiredForTransparency(
    bs_PipelineHash* inout)
{
    next.bsgfx_requiredForTransparency(inout);
}

bsgfx_Scene* bsgfx_currentScene()
{
    return next.bsgfx_currentScene();
}

void bsgfx_loadScene(
    const char* name)
{
    next.bsgfx_loadScene(name);
}

bool bsgfx_validateSubtype(
    const char* library_name, 
    bsgfx_InstanceSubtype* subtype)
{
    return next.bsgfx_validateSubtype(library_name, subtype);
}

bool bsgfx_validateInstanceType(
    const char* library_name, 
    bsgfx_InstanceType* instance_type)
{
    return next.bsgfx_validateInstanceType(library_name, instance_type);
}

void bsgfx_worldToScreen(
    const bs_vec3* position, 
    const bs_mat4* camera, 
    const bs_vec2* resolution, 
    bs_vec2* out)
{
    next.bsgfx_worldToScreen(position, camera, resolution, out);
}

const char* bsgfx_materialCategoryName(
    bsgfx_MaterialCategory category)
{
    return next.bsgfx_materialCategoryName(category);
}

bs_List* bsgfx_materials()
{
    return next.bsgfx_materials();
}

bsgfx_Material* bsgfx_queryMaterialHash(
    bs_U64 hash)
{
    return next.bsgfx_queryMaterialHash(hash);
}

bsgfx_Material* bsgfx_fetchMaterial(
    int id)
{
    return next.bsgfx_fetchMaterial(id);
}

bsgfx_Material* bsgfx_queryMaterial(
    const char* name)
{
    return next.bsgfx_queryMaterial(name);
}

void bsgfx_loadMaterials()
{
    next.bsgfx_loadMaterials();
}

bsgfx_Material* bsgfx_material(
    char* name)
{
    return next.bsgfx_material(name);
}

bsgfx_Material* bsgfx_materialN(
    char* name, 
    int name_length)
{
    return next.bsgfx_materialN(name, name_length);
}

bsgfx_Material* bsgfx_materialV(
    char* format, 
    va_list args)
{
    return next.bsgfx_materialV(format, args);
}

bsgfx_Material* bsgfx_materialF(
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    bsgfx_Material* _return = next.bsgfx_materialV(format, args);
    va_end(args);
    return _return;
}

void bsgfx_highlightMaterial(
    int material_id, 
    bool auto_unhighlight)
{
    next.bsgfx_highlightMaterial(material_id, auto_unhighlight);
}

void bsgfx_unhighlightMaterial(
    int material_id)
{
    next.bsgfx_unhighlightMaterial(material_id);
}

void bsgfx_tickMaterials()
{
    next.bsgfx_tickMaterials();
}

void bsgfx_sweepCollisions(
    float sweep_radius, 
    const bs_vec3* position)
{
    next.bsgfx_sweepCollisions(sweep_radius, position);
}

bsgfx_Collider bsgfx_collider(
    bs_Aabb aabb, 
    bs_vec3 scale, 
    bs_ivec3 resolution, 
    float sweep_radius)
{
    return next.bsgfx_collider(aabb, scale, resolution, sweep_radius);
}

void bsgfx_applyCollisions(
    bsgfx_Collider* collider, 
    const bs_vec3* position, 
    bs_vec3* velocity)
{
    next.bsgfx_applyCollisions(collider, position, velocity);
}

void bsgfx_printCollisions(
    bsgfx_Collider* collider)
{
    next.bsgfx_printCollisions(collider);
}

void bsgfx_instanceSweepCollisions()
{
    next.bsgfx_instanceSweepCollisions();
}

void bsgfx_instanceCollider(
    bsgfx_Collider* collider, 
    const bs_vec3* position, 
    bs_vec3* velocity)
{
    next.bsgfx_instanceCollider(collider, position, velocity);
}

int bsgfx_skeleton(
    bs_Armature* armature)
{
    return next.bsgfx_skeleton(armature);
}

int bsgfx_animationFrame(
    bs_Animation* animation, 
    float time, 
    int num_frames)
{
    return next.bsgfx_animationFrame(animation, time, num_frames);
}

int bsgfx_animationFrameCount(
    bs_Animation* animation, 
    float time_scale)
{
    return next.bsgfx_animationFrameCount(animation, time_scale);
}

void bsgfx_applyAnimationVelocity(
    bsgfx_Animator* animator, 
    bs_vec3* velocity, 
    bs_vec2 input)
{
    next.bsgfx_applyAnimationVelocity(animator, velocity, input);
}

void bsgfx_queueAnimation(
    bsgfx_Animator* animator, 
    int animation_id)
{
    next.bsgfx_queueAnimation(animator, animation_id);
}

void bsgfx_runAnimator(
    bsgfx_Animator* animator, 
    bsgfx_AnimatorCallbacks callbacks)
{
    next.bsgfx_runAnimator(animator, callbacks);
}

bsgfx_Animator bsgfx_animator(
    bs_Armature* armature, 
    int resting_animation_id, 
    int animations_count)
{
    return next.bsgfx_animator(armature, resting_animation_id, animations_count);
}

bs_Result bsgfx_ensureInstanceCount(
    bsgfx_InstanceType* instance_type, 
    bs_U32 instances_count, 
    bs_U32 overhead_count)
{
    return next.bsgfx_ensureInstanceCount(instance_type, instances_count, overhead_count);
}

bs_Result bsgfx_instanceType(
    size_t instance_size, 
    int bind_set, 
    int binding, 
    bsgfx_InstanceType** out)
{
    return next.bsgfx_instanceType(instance_size, bind_set, binding, out);
}

void bsgfx_deleteSubtype(
    bsgfx_InstanceSubtype* instance_subtype)
{
    next.bsgfx_deleteSubtype(instance_subtype);
}

bs_Result bsgfx_subtype(
    bsgfx_InstanceType* instance_type, 
    bs_Batch* batch, 
    bs_U32 flags, 
    bs_Range range, 
    bsgfx_InstanceSubtype** out)
{
    return next.bsgfx_subtype(instance_type, batch, flags, range, out);
}

int bsgfx_instantiate(
    bsgfx_InstanceSubtype* instance_subtype, 
    const char* data, 
    int data_size, 
    bs_U32 flags, 
    unsigned int bone_index, 
    int id, 
    int material)
{
    return next.bsgfx_instantiate(instance_subtype, data, data_size, flags, bone_index, id, material);
}

void bsgfx_tickInstanceType(
    bsgfx_InstanceType* instance_type)
{
    next.bsgfx_tickInstanceType(instance_type);
}

void bsgfx_renderSubtype(
    bs_Queue* queue, 
    bsgfx_InstanceSubtype* instance_subtype, 
    bs_Pipeline* pipeline)
{
    next.bsgfx_renderSubtype(queue, instance_subtype, pipeline);
}

void bsgfx_resetInstanceType(
    bsgfx_InstanceType* instance_type)
{
    next.bsgfx_resetInstanceType(instance_type);
}

void bsgfx_instanceHiResMesh(
    bs_Mesh* mesh, 
    const bs_vec3* position, 
    const bs_vec4* rotation, 
    float scale, 
    int subtype_offset, 
    bool origin_at_center)
{
    next.bsgfx_instanceHiResMesh(mesh, position, rotation, scale, subtype_offset, origin_at_center);
}

int bsgfx_instanceMesh(
    bsgfx_InstanceSubtype* subtype, 
    const bsgfx_MeshInstance* data, 
    bs_U32 flags, 
    int id, 
    int material)
{
    return next.bsgfx_instanceMesh(subtype, data, flags, id, material);
}

int bsgfx_instanceBoneMesh(
    bsgfx_InstanceSubtype* subtype, 
    const bsgfx_BoneInstance* data, 
    bs_U32 flags, 
    int id, 
    int material)
{
    return next.bsgfx_instanceBoneMesh(subtype, data, flags, id, material);
}

int bsgfx_instanceDepthlessLine(
    bs_vec3 start, 
    bs_vec3 end, 
    bs_RGBA color)
{
    return next.bsgfx_instanceDepthlessLine(start, end, color);
}

int bsgfx_instanceLine(
    bs_vec3 start, 
    bs_vec3 end, 
    bs_RGBA color)
{
    return next.bsgfx_instanceLine(start, end, color);
}

int bsgfx_instanceRay(
    const bs_Ray* ray, 
    bs_RGBA color)
{
    return next.bsgfx_instanceRay(ray, color);
}

void bsgfx_instanceAabb(
    const bs_Aabb* aabb, 
    bs_RGBA color, 
    bs_Range* out)
{
    next.bsgfx_instanceAabb(aabb, color, out);
}

int bsgfx_instanceSphere(
    bs_vec3 position, 
    float radius)
{
    return next.bsgfx_instanceSphere(position, radius);
}

int bsgfx_instanceCone(
    bs_mat4 transform, 
    float radius, 
    bs_U32 flags, 
    int id, 
    int material)
{
    return next.bsgfx_instanceCone(transform, radius, flags, id, material);
}

int bsgfx_instancePoint(
    bs_vec3 position, 
    bs_RGBA color, 
    float size)
{
    return next.bsgfx_instancePoint(position, color, size);
}

int bsgfx_instanceQuad(
    bsgfx_InstanceSubtype* subtype, 
    bs_mat4x3 transform, 
    bs_vec4 coords, 
    bs_U32 flags, 
    int id, 
    int material)
{
    return next.bsgfx_instanceQuad(subtype, transform, coords, flags, id, material);
}

void bsgfx_instanceDepthlessCircle(
    const bs_mat4* transform, 
    int segments, 
    float radius, 
    bs_RGBA color, 
    bs_Range* out)
{
    next.bsgfx_instanceDepthlessCircle(transform, segments, radius, color, out);
}

int bsgfx_instanceAtlas(
    bsgfx_InstanceSubtype* subtype, 
    bs_mat4x3 transform, 
    int texture, 
    bs_U32 flags, 
    int id, 
    int material)
{
    return next.bsgfx_instanceAtlas(subtype, transform, texture, flags, id, material);
}

int bsgfx_instanceAtlasFlipped(
    bsgfx_InstanceSubtype* subtype, 
    bs_mat4x3 transform, 
    int texture, 
    bs_U32 flags, 
    int id, 
    int material)
{
    return next.bsgfx_instanceAtlasFlipped(subtype, transform, texture, flags, id, material);
}

float bsgfx_fontHeight(
    bsgfx_Font* font, 
    int px_size)
{
    return next.bsgfx_fontHeight(font, px_size);
}

float bsgfx_instanceASCIIText(
    bsgfx_InstanceSubtype* subtype, 
    bsgfx_Font* font, 
    bs_vec3 position, 
    int pt_size, 
    char* text)
{
    return next.bsgfx_instanceASCIIText(subtype, font, position, pt_size, text);
}

float bsgfx_instanceASCIITextN(
    bsgfx_InstanceSubtype* subtype, 
    bsgfx_Font* font, 
    bs_vec3 position, 
    int pt_size, 
    char* text, 
    int text_length)
{
    return next.bsgfx_instanceASCIITextN(subtype, font, position, pt_size, text, text_length);
}

float bsgfx_instanceASCIITextV(
    bsgfx_InstanceSubtype* subtype, 
    bsgfx_Font* font, 
    bs_vec3 position, 
    int pt_size, 
    char* format, 
    va_list args)
{
    return next.bsgfx_instanceASCIITextV(subtype, font, position, pt_size, format, args);
}

float bsgfx_instanceASCIITextF(
    bsgfx_InstanceSubtype* subtype, 
    bsgfx_Font* font, 
    bs_vec3 position, 
    int pt_size, 
    char* format, 
    ...)
{
    va_list args;
    va_start(args, format);
    float _return = next.bsgfx_instanceASCIITextV(subtype, font, position, pt_size, format, args);
    va_end(args);
    return _return;
}

bs_mat4x3 bsgfx_matrix(
    bs_vec3 position, 
    bs_vec3 scale)
{
    return next.bsgfx_matrix(position, scale);
}

void bsgfx_renderFineShadowVolumes()
{
    next.bsgfx_renderFineShadowVolumes();
}

void bsgfx_renderShadowVolumes()
{
    next.bsgfx_renderShadowVolumes();
}

void bsgfx_computeShadowVolumes()
{
    next.bsgfx_computeShadowVolumes();
}

bs_Model* bsgfx_prefabModel()
{
    return next.bsgfx_prefabModel();
}

int bsgfx_package()
{
    return next.bsgfx_package();
}

void bsgfx_ini(
    const char* name, 
    bs_U32 width, 
    bs_U32 height, 
    int argc, 
    char* argv[])
{
    next.bsgfx_ini(name, width, height, argc, argv);
}

void bsgfx_tick()
{
    next.bsgfx_tick();
}

bsgfx_Application* bsgfx_app()
{
    return next.bsgfx_app();
}

bsgfx_Callbacks* bsgfx_callbacks()
{
    return next.bsgfx_callbacks();
}

bsgfx_Settings* bsgfx_settings()
{
    return next.bsgfx_settings();
}

void bsgfx_setCamera(
    const bs_mat4* proj, 
    const bs_mat4* view)
{
    next.bsgfx_setCamera(proj, view);
}

void bsgfx_type(
    bsgfx_TypeId id, 
    int package_id, 
    int version, 
    const char* plural, 
    const char* singular, 
    size_t unmapped_size, 
    size_t mapped_size, 
    PFN_bsgfx_TypeMapper mapper, 
    size_t unmapped_flexible_offset, 
    size_t mapped_flexible_offset, 
    size_t unmapped_flexible_size, 
    size_t mapped_flexible_size)
{
    next.bsgfx_type(id, package_id, version, plural, singular, unmapped_size, mapped_size, mapper, unmapped_flexible_offset, mapped_flexible_offset, unmapped_flexible_size, mapped_flexible_size);
}

void bsgfx_map(
    bsgfx_TypeId type, 
    int id)
{
    next.bsgfx_map(type, id);
}

void bsgfx_remap(
    bsgfx_TypeId type_id)
{
    next.bsgfx_remap(type_id);
}

int bsgfx_count(
    bsgfx_TypeId type_id)
{
    return next.bsgfx_count(type_id);
}

void* bsgfx_get(
    bsgfx_TypeId type_id, 
    bs_U32 id)
{
    return next.bsgfx_get(type_id, id);
}

bsgfx_Type* bsgfx_getType(
    bsgfx_TypeId type_id)
{
    return next.bsgfx_getType(type_id);
}

int bsgfx_id(
    bsgfx_TypeId type_id, 
    unsigned char* p)
{
    return next.bsgfx_id(type_id, p);
}

int bsgfx_rawId(
    bsgfx_TypeId type_id, 
    unsigned char* p)
{
    return next.bsgfx_rawId(type_id, p);
}

void* bsgfx_getRaw(
    bsgfx_TypeId type_id, 
    int id)
{
    return next.bsgfx_getRaw(type_id, id);
}

int bsgfx_flexibleCount(
    bsgfx_TypeId type_id, 
    int id)
{
    return next.bsgfx_flexibleCount(type_id, id);
}

void bsgfx_loadLights(
    int package_id)
{
    next.bsgfx_loadLights(package_id);
}

void bsgfx_computePrefabShadows(
    bs_Queue* queue)
{
    next.bsgfx_computePrefabShadows(queue);
}

void bsgfx_renderPrefabShadowVolumes(
    bs_RendererScope* scope, 
    bs_Queue* queue)
{
    next.bsgfx_renderPrefabShadowVolumes(scope, queue);
}

bsgfx_PrefabMetadata* bsgfx_prefabMetadata(
    int mesh_id)
{
    return next.bsgfx_prefabMetadata(mesh_id);
}

void bsgfx_loadPrefabs(
    int package_id, 
    bs_Model* model)
{
    next.bsgfx_loadPrefabs(package_id, model);
}

void bsgfx_prefabTransform(
    bsgfx_Prefab* prefab, 
    bs_mat4* out)
{
    next.bsgfx_prefabTransform(prefab, out);
}

int bsgfx_instancePrefabModel(
    int mesh_id, 
    bs_mat4 transform, 
    bsgfx_PrefabSubtype prefab_subtype, 
    int material_id)
{
    return next.bsgfx_instancePrefabModel(mesh_id, transform, prefab_subtype, material_id);
}

int bsgfx_instancePrefab(
    int id, 
    bsgfx_PrefabSubtype prefab_subtype)
{
    return next.bsgfx_instancePrefab(id, prefab_subtype);
}

void bsgfx_instancePrefabs()
{
    next.bsgfx_instancePrefabs();
}

void bsgfx_renderPrefabs(
    bs_Queue* queue, 
    bs_Pipeline* pipeline, 
    int key_start)
{
    next.bsgfx_renderPrefabs(queue, pipeline, key_start);
}

void bsgfx_renderPrefabPrimitives(
    bs_Queue* queue, 
    bs_Pipeline* pipeline, 
    int key_start)
{
    next.bsgfx_renderPrefabPrimitives(queue, pipeline, key_start);
}

int bsgfx_queryPrefabId(
    const bs_GUID* guid)
{
    return next.bsgfx_queryPrefabId(guid);
}

int bsgfx_closestPrefab(
    bs_U64 mesh_name_hash, 
    bs_vec3 position, 
    float radius)
{
    return next.bsgfx_closestPrefab(mesh_name_hash, position, radius);
}

void bsgfx_primitivePosition(
    const bsgfx_RawPrimitive* primitive, 
    bs_vec3* out)
{
    next.bsgfx_primitivePosition(primitive, out);
}

void bsgfx_loadPrimitives(
    int package_id)
{
    next.bsgfx_loadPrimitives(package_id);
}

bsgfx_InstanceSubtype* bsgfx_primitiveSubtype(
    bsgfx_PrimitiveType type)
{
    return next.bsgfx_primitiveSubtype(type);
}

int bsgfx_instancePrimitive(
    bsgfx_InstanceSubtype* subtype, 
    bs_mat4 transform, 
    bs_U32 flags, 
    int id, 
    int material)
{
    return next.bsgfx_instancePrimitive(subtype, transform, flags, id, material);
}

int bsgfx_queryTilePrimitive(
    int tile_id)
{
    return next.bsgfx_queryTilePrimitive(tile_id);
}

void bsgfx_instancePrimitives()
{
    next.bsgfx_instancePrimitives();
}

void bsgfx_renderPrimitives(
    bs_RendererScope* scope, 
    bs_Queue* queue, 
    bs_mat4 camera)
{
    next.bsgfx_renderPrimitives(scope, queue, camera);
}

int bsgfx_queryPrimitive(
    bs_GUID* guid)
{
    return next.bsgfx_queryPrimitive(guid);
}

void bsgfx_loadSpawners(
    int package_id)
{
    next.bsgfx_loadSpawners(package_id);
}

void bsgfx_spawn(
    bsgfx_Spawner* spawner)
{
    next.bsgfx_spawn(spawner);
}

void bsgfx_loadTiles(
    int package_id, 
    bool force_destroy)
{
    next.bsgfx_loadTiles(package_id, force_destroy);
}

void bsgfx_instanceTiles()
{
    next.bsgfx_instanceTiles();
}

void bsgfx_pushTile(
    const bs_Batch* batch, 
    const bs_Quad* quad, 
    bs_vec3 normal, 
    bs_U32 index, 
    int image_index, 
    bs_Range* out_range)
{
    next.bsgfx_pushTile(batch, quad, normal, index, image_index, out_range);
}

void bsgfx_batchTile(
    const bs_Batch* batch, 
    const bs_U32* offset, 
    const bs_Quad* quad, 
    bs_vec3 normal, 
    bs_U32 index, 
    int image_index)
{
    next.bsgfx_batchTile(batch, offset, quad, normal, index, image_index);
}

const bsgfx_TileAxis* bsgfx_tileAxes()
{
    return next.bsgfx_tileAxes();
}

void bsgfx_tilePosition(
    const bsgfx_Primitive* primitive, 
    int axis, 
    int x, 
    int y, 
    bs_vec3* out)
{
    next.bsgfx_tilePosition(primitive, axis, x, y, out);
}

void bsgfx_tileRotation(
    int axis, 
    bs_vec4* out)
{
    next.bsgfx_tileRotation(axis, out);
}

void bsgfx_tileEulerRotation(
    int axis, 
    bs_vec3* out)
{
    next.bsgfx_tileEulerRotation(axis, out);
}

void bsgfx_pushTileAt(
    const bs_Batch* batch, 
    const bsgfx_Primitive* primitive, 
    int axis, 
    int x, 
    int y, 
    bs_U32 index, 
    int image_index, 
    bs_U32* out)
{
    next.bsgfx_pushTileAt(batch, primitive, axis, x, y, index, image_index, out);
}

void bsgfx_tileCoordinate(
    const bsgfx_Primitive* primitive, 
    int axis, 
    int index, 
    bs_ivec2* out)
{
    next.bsgfx_tileCoordinate(primitive, axis, index, out);
}

void bsgfx_tileAxis(
    const bsgfx_Primitive* primitive, 
    int index, 
    int* out)
{
    next.bsgfx_tileAxis(primitive, index, out);
}

void bsgfx_tileIndex(
    const bsgfx_Primitive* primitive, 
    int axis, 
    int x, 
    int y, 
    bs_U32* out)
{
    next.bsgfx_tileIndex(primitive, axis, x, y, out);
}

bool bsgfx_instanceWidgets(
    bsgfx_Menu menu, 
    bsgfx_TitleBar* title_bar, 
    bsgfx_MenuTabBar* tab_bar)
{
    return next.bsgfx_instanceWidgets(menu, title_bar, tab_bar);
}

void bsgfx_instantiateTextUI(
    bsgfx_UIText text, 
    bsgfx_UIElement* element)
{
    next.bsgfx_instantiateTextUI(text, element);
}

void bsgfx_instantiateSolidUI(
    bsgfx_UISolid solid, 
    bsgfx_UIElement* element)
{
    next.bsgfx_instantiateSolidUI(solid, element);
}

void bsgfx_instantiateSolidUIElement(
    bsgfx_UISolid solid, 
    const bsgfx_UIElement* element)
{
    next.bsgfx_instantiateSolidUIElement(solid, element);
}

void bsgfx_solidUIElement(
    bsgfx_UISolid solid, 
    bsgfx_UIElement* element)
{
    next.bsgfx_solidUIElement(solid, element);
}

void bsgfx_instantiateAtlasIconUI(
    bsgfx_UIIcon icon, 
    bsgfx_UIElement* element)
{
    next.bsgfx_instantiateAtlasIconUI(icon, element);
}

void bsgfx_instantiateAtlasIconUIElement(
    bsgfx_UIIcon icon, 
    const bsgfx_UIElement* element)
{
    next.bsgfx_instantiateAtlasIconUIElement(icon, element);
}

void bsgfx_atlasIconUIElement(
    bsgfx_UIIcon icon, 
    bsgfx_UIElement* element)
{
    next.bsgfx_atlasIconUIElement(icon, element);
}

bool bsgfx_hoveringUIElement(
    const bsgfx_UIElement* element)
{
    return next.bsgfx_hoveringUIElement(element);
}

void bsgfx_renderColorPickers(
    bs_RendererScope* scope, 
    bs_Queue* queue)
{
    next.bsgfx_renderColorPickers(scope, queue);
}

