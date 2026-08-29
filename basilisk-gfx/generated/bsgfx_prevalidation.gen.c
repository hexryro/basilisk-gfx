
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
        
#include <bsgfx_internal.h>

static bsgfx_FunctionTable next = { 0 };

const bsgfx_FunctionTable* _preval_bsgfx_setFunctions(const bsgfx_FunctionTable* a, bsgfx_FunctionTable* b) {
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

BSGFXAPI void _preval_bsgfx_test() {
    next.bsgfx_test();
}

BSGFXAPI bsgfx_InstanceSubtype** _preval_bsgfx_subtypes() {
    return next.bsgfx_subtypes();
}

BSGFXAPI bsgfx_InstanceType** _preval_bsgfx_instanceTypes() {
    return next.bsgfx_instanceTypes();
}

BSGFXAPI void _preval_bsgfx_computeContextCamera() {
    next.bsgfx_computeContextCamera();
}

BSGFXAPI void _preval_bsgfx_tickInstanceTypes() {
    next.bsgfx_tickInstanceTypes();
}

BSGFXAPI void _preval_bsgfx_resetInstanceTypes() {
    next.bsgfx_resetInstanceTypes();
}

BSGFXAPI void _preval_bsgfx_textDimensions(bsgfx_Font* font, bs_vec2* out, char* name, int length) {
    BSGFX_VALIDATE(font != NULL, ,);
    BSGFX_VALIDATE(out != NULL, ,);
    BSGFX_VALIDATE(name != NULL, ,);
    next.bsgfx_textDimensions(font, out, name, length);
}

BSGFXAPI bs_PipelineHash _preval_bsgfx_defaultPipelineHash() {
    return next.bsgfx_defaultPipelineHash();
}

BSGFXAPI void _preval_bsgfx_renderTileIcons(bs_RendererScope* scope, bs_Queue* queue) {
    BSGFX_VALIDATE(scope != NULL, ,);
    BSGFX_VALIDATE(queue != NULL, ,);
    next.bsgfx_renderTileIcons(scope, queue);
}

BSGFXAPI void _preval_bsgfx_renderAtlasIcons(bs_RendererScope* scope, bs_Queue* queue) {
    BSGFX_VALIDATE(scope != NULL, ,);
    BSGFX_VALIDATE(queue != NULL, ,);
    next.bsgfx_renderAtlasIcons(scope, queue);
}

BSGFXAPI void _preval_bsgfx_renderLineModel(bs_RendererScope* scope, bs_Queue* queue, const bs_mat4* camera, bsgfx_InstanceSubtype* subtype, bool skip_depth_test) {
    BSGFX_VALIDATE(scope != NULL, ,);
    BSGFX_VALIDATE(queue != NULL, ,);
    BSGFX_VALIDATE(camera != NULL, ,);
    BSGFX_VALIDATE(subtype != NULL, ,);
    next.bsgfx_renderLineModel(scope, queue, camera, subtype, skip_depth_test);
}

BSGFXAPI void _preval_bsgfx_renderLines(bs_RendererScope* scope, bs_Queue* queue, const bs_mat4* camera, bsgfx_InstanceSubtype* subtype, bool skip_depth_test) {
    BSGFX_VALIDATE(scope != NULL, ,);
    BSGFX_VALIDATE(queue != NULL, ,);
    BSGFX_VALIDATE(camera != NULL, ,);
    BSGFX_VALIDATE(subtype != NULL, ,);
    next.bsgfx_renderLines(scope, queue, camera, subtype, skip_depth_test);
}

BSGFXAPI void _preval_bsgfx_renderPoints(bs_RendererScope* scope, bs_Queue* queue) {
    BSGFX_VALIDATE(scope != NULL, ,);
    BSGFX_VALIDATE(queue != NULL, ,);
    next.bsgfx_renderPoints(scope, queue);
}

BSGFXAPI void _preval_bsgfx_renderAtlas(bs_RendererScope* scope, bs_Queue* queue) {
    BSGFX_VALIDATE(scope != NULL, ,);
    BSGFX_VALIDATE(queue != NULL, ,);
    next.bsgfx_renderAtlas(scope, queue);
}

BSGFXAPI void _preval_bsgfx_renderPrimitiveTiles(bs_RendererScope* scope, bs_Queue* queue) {
    BSGFX_VALIDATE(scope != NULL, ,);
    BSGFX_VALIDATE(queue != NULL, ,);
    next.bsgfx_renderPrimitiveTiles(scope, queue);
}

BSGFXAPI void _preval_bsgfx_swapBufferBindings() {
    next.bsgfx_swapBufferBindings();
}

BSGFXAPI void _preval_bsgfx_requiredForShadowVolumes(bs_PipelineHash* inout) {
    BSGFX_VALIDATE(inout != NULL, ,);
    next.bsgfx_requiredForShadowVolumes(inout);
}

BSGFXAPI void _preval_bsgfx_requiredForStencilShadows(bs_PipelineHash* inout) {
    BSGFX_VALIDATE(inout != NULL, ,);
    next.bsgfx_requiredForStencilShadows(inout);
}

BSGFXAPI void _preval_bsgfx_requiredForTransparency(bs_PipelineHash* inout) {
    BSGFX_VALIDATE(inout != NULL, ,);
    next.bsgfx_requiredForTransparency(inout);
}

BSGFXAPI bsgfx_Scene* _preval_bsgfx_currentScene() {
    return next.bsgfx_currentScene();
}

BSGFXAPI void _preval_bsgfx_loadScene(const char* name) {
    BSGFX_VALIDATE(name != NULL, ,);
    next.bsgfx_loadScene(name);
}

BSGFXAPI bool _preval_bsgfx_validateSubtype(const char* library_name, bsgfx_InstanceSubtype* subtype) {
    BSGFX_VALIDATE(library_name != NULL, false,);
    BSGFX_VALIDATE(subtype != NULL, false,);
    return next.bsgfx_validateSubtype(library_name, subtype);
}

BSGFXAPI bool _preval_bsgfx_validateInstanceType(const char* library_name, bsgfx_InstanceType* instance_type) {
    BSGFX_VALIDATE(library_name != NULL, false,);
    BSGFX_VALIDATE(instance_type != NULL, false,);
    return next.bsgfx_validateInstanceType(library_name, instance_type);
}

BSGFXAPI void _preval_bsgfx_worldToScreen(const bs_vec3* position, const bs_mat4* camera, const bs_vec2* resolution, bs_vec2* out) {
    BSGFX_VALIDATE(position != NULL, ,);
    BSGFX_VALIDATE(camera != NULL, ,);
    BSGFX_VALIDATE(resolution != NULL, ,);
    BSGFX_VALIDATE(out != NULL, ,);
    next.bsgfx_worldToScreen(position, camera, resolution, out);
}

BSGFXAPI const char* _preval_bsgfx_materialCategoryName(bsgfx_MaterialCategory category) {
    return next.bsgfx_materialCategoryName(category);
}

BSGFXAPI bs_List* _preval_bsgfx_materials() {
    return next.bsgfx_materials();
}

BSGFXAPI bsgfx_Material* _preval_bsgfx_queryMaterialHash(bs_U64 hash) {
    return next.bsgfx_queryMaterialHash(hash);
}

BSGFXAPI bsgfx_Material* _preval_bsgfx_fetchMaterial(int id) {
    return next.bsgfx_fetchMaterial(id);
}

BSGFXAPI bsgfx_Material* _preval_bsgfx_queryMaterial(const char* name) {
    BSGFX_VALIDATE(name != NULL, NULL,);
    return next.bsgfx_queryMaterial(name);
}

BSGFXAPI void _preval_bsgfx_loadMaterials() {
    next.bsgfx_loadMaterials();
}

BSGFXAPI bsgfx_Material* _preval_bsgfx_material(char* name) {
    BSGFX_VALIDATE(name != NULL, NULL,);
    return next.bsgfx_material(name);
}

BSGFXAPI bsgfx_Material* _preval_bsgfx_materialN(char* name, int name_length) {
    BSGFX_VALIDATE(name != NULL, NULL,);
    return next.bsgfx_materialN(name, name_length);
}

BSGFXAPI bsgfx_Material* _preval_bsgfx_materialV(char* format, va_list args) {
    BSGFX_VALIDATE(format != NULL, NULL,);
    return next.bsgfx_materialV(format, args);
}

BSGFXAPI void _preval_bsgfx_highlightMaterial(int material_id, bool auto_unhighlight) {
    next.bsgfx_highlightMaterial(material_id, auto_unhighlight);
}

BSGFXAPI void _preval_bsgfx_unhighlightMaterial(int material_id) {
    next.bsgfx_unhighlightMaterial(material_id);
}

BSGFXAPI void _preval_bsgfx_tickMaterials() {
    next.bsgfx_tickMaterials();
}

BSGFXAPI void _preval_bsgfx_sweepCollisions(float sweep_radius, const bs_vec3* position) {
    BSGFX_VALIDATE(position != NULL, ,);
    next.bsgfx_sweepCollisions(sweep_radius, position);
}

BSGFXAPI bsgfx_Collider _preval_bsgfx_collider(bs_Aabb aabb, bs_vec3 scale, bs_ivec3 resolution, float sweep_radius) {
    return next.bsgfx_collider(aabb, scale, resolution, sweep_radius);
}

BSGFXAPI void _preval_bsgfx_applyCollisions(bsgfx_Collider* collider, const bs_vec3* position, bs_vec3* velocity) {
    BSGFX_VALIDATE(collider != NULL, ,);
    BSGFX_VALIDATE(position != NULL, ,);
    BSGFX_VALIDATE(velocity != NULL, ,);
    next.bsgfx_applyCollisions(collider, position, velocity);
}

BSGFXAPI void _preval_bsgfx_printCollisions(bsgfx_Collider* collider) {
    BSGFX_VALIDATE(collider != NULL, ,);
    next.bsgfx_printCollisions(collider);
}

BSGFXAPI void _preval_bsgfx_instanceSweepCollisions() {
    next.bsgfx_instanceSweepCollisions();
}

BSGFXAPI void _preval_bsgfx_instanceCollider(bsgfx_Collider* collider, const bs_vec3* position, bs_vec3* velocity) {
    BSGFX_VALIDATE(collider != NULL, ,);
    BSGFX_VALIDATE(position != NULL, ,);
    BSGFX_VALIDATE(velocity != NULL, ,);
    next.bsgfx_instanceCollider(collider, position, velocity);
}

BSGFXAPI int _preval_bsgfx_skeleton(bs_Armature* armature) {
    BSGFX_VALIDATE(armature != NULL, 0,);
    return next.bsgfx_skeleton(armature);
}

BSGFXAPI int _preval_bsgfx_animationFrame(bs_Animation* animation, float time, int num_frames) {
    BSGFX_VALIDATE(animation != NULL, 0,);
    return next.bsgfx_animationFrame(animation, time, num_frames);
}

BSGFXAPI int _preval_bsgfx_animationFrameCount(bs_Animation* animation, float time_scale) {
    BSGFX_VALIDATE(animation != NULL, 0,);
    return next.bsgfx_animationFrameCount(animation, time_scale);
}

BSGFXAPI void _preval_bsgfx_applyAnimationVelocity(bsgfx_Animator* animator, bs_vec3* velocity, bs_vec2 input) {
    BSGFX_VALIDATE(animator != NULL, ,);
    BSGFX_VALIDATE(velocity != NULL, ,);
    next.bsgfx_applyAnimationVelocity(animator, velocity, input);
}

BSGFXAPI void _preval_bsgfx_queueAnimation(bsgfx_Animator* animator, int animation_id) {
    BSGFX_VALIDATE(animator != NULL, ,);
    next.bsgfx_queueAnimation(animator, animation_id);
}

BSGFXAPI void _preval_bsgfx_runAnimator(bsgfx_Animator* animator, bsgfx_AnimatorCallbacks callbacks) {
    BSGFX_VALIDATE(animator != NULL, ,);
    next.bsgfx_runAnimator(animator, callbacks);
}

BSGFXAPI bsgfx_Animator _preval_bsgfx_animator(bs_Armature* armature, int resting_animation_id, int animations_count) {
    BSGFX_VALIDATE(armature != NULL, (bsgfx_Animator) { 0 },);
    return next.bsgfx_animator(armature, resting_animation_id, animations_count);
}

BSGFXAPI bs_Result _preval_bsgfx_ensureInstanceCount(bsgfx_InstanceType* instance_type, bs_U32 instances_count, bs_U32 overhead_count) {
    BSGFX_VALIDATE(instance_type != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bsgfx_ensureInstanceCount(instance_type, instances_count, overhead_count);
}

BSGFXAPI bs_Result _preval_bsgfx_instanceType(size_t instance_size, int bind_set, int binding, bsgfx_InstanceType** out) {
    BSGFX_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bsgfx_instanceType(instance_size, bind_set, binding, out);
}

BSGFXAPI void _preval_bsgfx_deleteSubtype(bsgfx_InstanceSubtype* instance_subtype) {
    BSGFX_VALIDATE(instance_subtype != NULL, ,);
    next.bsgfx_deleteSubtype(instance_subtype);
}

BSGFXAPI bs_Result _preval_bsgfx_subtype(bsgfx_InstanceType* instance_type, bs_Batch* batch, bs_U32 flags, bs_Range range, bsgfx_InstanceSubtype** out) {
    BSGFX_VALIDATE(instance_type != NULL, BS_RESULT_VALIDATION_ERROR,);
    BSGFX_VALIDATE(batch != NULL, BS_RESULT_VALIDATION_ERROR,);
    BSGFX_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bsgfx_subtype(instance_type, batch, flags, range, out);
}

BSGFXAPI int _preval_bsgfx_instantiate(bsgfx_InstanceSubtype* instance_subtype, const char* data, int data_size, bs_U32 flags, unsigned int bone_index, int id, int material) {
    BSGFX_VALIDATE(instance_subtype != NULL, 0,);
    BSGFX_VALIDATE(data != NULL, 0,);
    return next.bsgfx_instantiate(instance_subtype, data, data_size, flags, bone_index, id, material);
}

BSGFXAPI void _preval_bsgfx_tickInstanceType(bsgfx_InstanceType* instance_type) {
    BSGFX_VALIDATE(instance_type != NULL, ,);
    next.bsgfx_tickInstanceType(instance_type);
}

BSGFXAPI void _preval_bsgfx_renderSubtype(bs_Queue* queue, bsgfx_InstanceSubtype* instance_subtype, bs_Pipeline* pipeline) {
    BSGFX_VALIDATE(queue != NULL, ,);
    BSGFX_VALIDATE(instance_subtype != NULL, ,);
    BSGFX_VALIDATE(pipeline != NULL, ,);
    next.bsgfx_renderSubtype(queue, instance_subtype, pipeline);
}

BSGFXAPI void _preval_bsgfx_resetInstanceType(bsgfx_InstanceType* instance_type) {
    BSGFX_VALIDATE(instance_type != NULL, ,);
    next.bsgfx_resetInstanceType(instance_type);
}

BSGFXAPI void _preval_bsgfx_instanceHiResMesh(bs_Mesh* mesh, const bs_vec3* position, const bs_vec4* rotation, float scale, int subtype_offset, bool origin_at_center) {
    BSGFX_VALIDATE(mesh != NULL, ,);
    BSGFX_VALIDATE(position != NULL, ,);
    BSGFX_VALIDATE(rotation != NULL, ,);
    next.bsgfx_instanceHiResMesh(mesh, position, rotation, scale, subtype_offset, origin_at_center);
}

BSGFXAPI int _preval_bsgfx_instanceMesh(bsgfx_InstanceSubtype* subtype, const bsgfx_MeshInstance* data, bs_U32 flags, int id, int material) {
    BSGFX_VALIDATE(subtype != NULL, 0,);
    BSGFX_VALIDATE(data != NULL, 0,);
    return next.bsgfx_instanceMesh(subtype, data, flags, id, material);
}

BSGFXAPI int _preval_bsgfx_instanceBoneMesh(bsgfx_InstanceSubtype* subtype, const bsgfx_BoneInstance* data, bs_U32 flags, int id, int material) {
    BSGFX_VALIDATE(subtype != NULL, 0,);
    BSGFX_VALIDATE(data != NULL, 0,);
    return next.bsgfx_instanceBoneMesh(subtype, data, flags, id, material);
}

BSGFXAPI int _preval_bsgfx_instanceDepthlessLine(bs_vec3 start, bs_vec3 end, bs_RGBA color) {
    return next.bsgfx_instanceDepthlessLine(start, end, color);
}

BSGFXAPI int _preval_bsgfx_instanceLine(bs_vec3 start, bs_vec3 end, bs_RGBA color) {
    return next.bsgfx_instanceLine(start, end, color);
}

BSGFXAPI int _preval_bsgfx_instanceRay(const bs_Ray* ray, bs_RGBA color) {
    BSGFX_VALIDATE(ray != NULL, 0,);
    return next.bsgfx_instanceRay(ray, color);
}

BSGFXAPI void _preval_bsgfx_instanceAabb(const bs_Aabb* aabb, bs_RGBA color, bs_Range* out) {
    BSGFX_VALIDATE(aabb != NULL, ,);
    BSGFX_VALIDATE(out != NULL, ,);
    next.bsgfx_instanceAabb(aabb, color, out);
}

BSGFXAPI int _preval_bsgfx_instanceSphere(bs_vec3 position, float radius) {
    return next.bsgfx_instanceSphere(position, radius);
}

BSGFXAPI int _preval_bsgfx_instanceCone(bs_mat4 transform, float radius, bs_U32 flags, int id, int material) {
    return next.bsgfx_instanceCone(transform, radius, flags, id, material);
}

BSGFXAPI int _preval_bsgfx_instancePoint(bs_vec3 position, bs_RGBA color, float size) {
    return next.bsgfx_instancePoint(position, color, size);
}

BSGFXAPI int _preval_bsgfx_instantiateQuad(bsgfx_InstanceSubtype* subtype, bs_mat4x3 transform, bs_vec4 coords, bs_U32 flags, int id, int material) {
    BSGFX_VALIDATE(subtype != NULL, 0,);
    return next.bsgfx_instantiateQuad(subtype, transform, coords, flags, id, material);
}

BSGFXAPI void _preval_bsgfx_instanceDepthlessCircle(const bs_mat4* transform, int segments, float radius, bs_RGBA color, bs_Range* out) {
    BSGFX_VALIDATE(transform != NULL, ,);
    BSGFX_VALIDATE(out != NULL, ,);
    next.bsgfx_instanceDepthlessCircle(transform, segments, radius, color, out);
}

BSGFXAPI int _preval_bsgfx_instanceAtlas(bsgfx_InstanceSubtype* subtype, bs_mat4x3 transform, int texture, bs_U32 flags, int id, int material) {
    BSGFX_VALIDATE(subtype != NULL, 0,);
    return next.bsgfx_instanceAtlas(subtype, transform, texture, flags, id, material);
}

BSGFXAPI int _preval_bsgfx_instanceAtlasFlipped(bsgfx_InstanceSubtype* subtype, bs_mat4x3 transform, int texture, bs_U32 flags, int id, int material) {
    BSGFX_VALIDATE(subtype != NULL, 0,);
    return next.bsgfx_instanceAtlasFlipped(subtype, transform, texture, flags, id, material);
}

BSGFXAPI float _preval_bsgfx_fontHeight(bsgfx_Font* font, int px_size) {
    BSGFX_VALIDATE(font != NULL, 0,);
    return next.bsgfx_fontHeight(font, px_size);
}

BSGFXAPI float _preval_bsgfx_instanceASCIIText(bsgfx_InstanceSubtype* subtype, bsgfx_Font* font, bs_vec3 position, int pt_size, int material_id, char* text) {
    BSGFX_VALIDATE(subtype != NULL, 0,);
    BSGFX_VALIDATE(font != NULL, 0,);
    BSGFX_VALIDATE(text != NULL, 0,);
    return next.bsgfx_instanceASCIIText(subtype, font, position, pt_size, material_id, text);
}

BSGFXAPI float _preval_bsgfx_instanceASCIITextN(bsgfx_InstanceSubtype* subtype, bsgfx_Font* font, bs_vec3 position, int pt_size, int material_id, char* text, int text_length) {
    BSGFX_VALIDATE(subtype != NULL, 0,);
    BSGFX_VALIDATE(font != NULL, 0,);
    BSGFX_VALIDATE(text != NULL, 0,);
    return next.bsgfx_instanceASCIITextN(subtype, font, position, pt_size, material_id, text, text_length);
}

BSGFXAPI float _preval_bsgfx_instanceASCIITextV(bsgfx_InstanceSubtype* subtype, bsgfx_Font* font, bs_vec3 position, int pt_size, int material_id, char* format, va_list args) {
    BSGFX_VALIDATE(subtype != NULL, 0,);
    BSGFX_VALIDATE(font != NULL, 0,);
    BSGFX_VALIDATE(format != NULL, 0,);
    return next.bsgfx_instanceASCIITextV(subtype, font, position, pt_size, material_id, format, args);
}

BSGFXAPI bs_mat4x3 _preval_bsgfx_matrix(bs_vec3 position, bs_vec3 scale) {
    return next.bsgfx_matrix(position, scale);
}

BSGFXAPI void _preval_bsgfx_renderFineShadowVolumes() {
    next.bsgfx_renderFineShadowVolumes();
}

BSGFXAPI void _preval_bsgfx_renderShadowVolumes() {
    next.bsgfx_renderShadowVolumes();
}

BSGFXAPI void _preval_bsgfx_computeShadowVolumes() {
    next.bsgfx_computeShadowVolumes();
}

BSGFXAPI bs_Model* _preval_bsgfx_prefabModel() {
    return next.bsgfx_prefabModel();
}

BSGFXAPI int _preval_bsgfx_package() {
    return next.bsgfx_package();
}

BSGFXAPI void _preval_bsgfx_ini(const char* name, bs_U32 width, bs_U32 height, bs_U32 window_flags, int argc, char* argv[]) {
    BSGFX_VALIDATE(name != NULL, ,);
    BSGFX_VALIDATE(argv != NULL, ,);
    next.bsgfx_ini(name, width, height, window_flags, argc, argv);
}

BSGFXAPI void _preval_bsgfx_tick() {
    next.bsgfx_tick();
}

BSGFXAPI bsgfx_Application* _preval_bsgfx_app() {
    return next.bsgfx_app();
}

BSGFXAPI bsgfx_Callbacks* _preval_bsgfx_callbacks() {
    return next.bsgfx_callbacks();
}

BSGFXAPI bsgfx_Settings* _preval_bsgfx_settings() {
    return next.bsgfx_settings();
}

BSGFXAPI void _preval_bsgfx_setCamera(const bs_mat4* proj, const bs_mat4* view) {
    BSGFX_VALIDATE(proj != NULL, ,);
    BSGFX_VALIDATE(view != NULL, ,);
    next.bsgfx_setCamera(proj, view);
}

BSGFXAPI void _preval_bsgfx_type(bsgfx_TypeId id, int package_id, int version, const char* plural, const char* singular, size_t unmapped_size, size_t mapped_size, PFN_bsgfx_TypeMapper mapper, size_t unmapped_flexible_offset, size_t mapped_flexible_offset, size_t unmapped_flexible_size, size_t mapped_flexible_size) {
    BSGFX_VALIDATE(plural != NULL, ,);
    BSGFX_VALIDATE(singular != NULL, ,);
    next.bsgfx_type(id, package_id, version, plural, singular, unmapped_size, mapped_size, mapper, unmapped_flexible_offset, mapped_flexible_offset, unmapped_flexible_size, mapped_flexible_size);
}

BSGFXAPI void _preval_bsgfx_map(bsgfx_TypeId type, int id) {
    next.bsgfx_map(type, id);
}

BSGFXAPI void _preval_bsgfx_remap(bsgfx_TypeId type_id) {
    next.bsgfx_remap(type_id);
}

BSGFXAPI int _preval_bsgfx_count(bsgfx_TypeId type_id) {
    return next.bsgfx_count(type_id);
}

BSGFXAPI void* _preval_bsgfx_get(bsgfx_TypeId type_id, bs_U32 id) {
    return next.bsgfx_get(type_id, id);
}

BSGFXAPI bsgfx_Type* _preval_bsgfx_getType(bsgfx_TypeId type_id) {
    return next.bsgfx_getType(type_id);
}

BSGFXAPI int _preval_bsgfx_id(bsgfx_TypeId type_id, unsigned char* p) {
    BSGFX_VALIDATE(p != NULL, 0,);
    return next.bsgfx_id(type_id, p);
}

BSGFXAPI int _preval_bsgfx_rawId(bsgfx_TypeId type_id, unsigned char* p) {
    BSGFX_VALIDATE(p != NULL, 0,);
    return next.bsgfx_rawId(type_id, p);
}

BSGFXAPI void* _preval_bsgfx_getRaw(bsgfx_TypeId type_id, int id) {
    return next.bsgfx_getRaw(type_id, id);
}

BSGFXAPI int _preval_bsgfx_flexibleCount(bsgfx_TypeId type_id, int id) {
    return next.bsgfx_flexibleCount(type_id, id);
}

BSGFXAPI void _preval_bsgfx_loadLights(int package_id) {
    next.bsgfx_loadLights(package_id);
}

BSGFXAPI void _preval_bsgfx_computePrefabShadows(bs_Queue* queue) {
    BSGFX_VALIDATE(queue != NULL, ,);
    next.bsgfx_computePrefabShadows(queue);
}

BSGFXAPI void _preval_bsgfx_renderPrefabShadowVolumes(bs_RendererScope* scope, bs_Queue* queue) {
    BSGFX_VALIDATE(scope != NULL, ,);
    BSGFX_VALIDATE(queue != NULL, ,);
    next.bsgfx_renderPrefabShadowVolumes(scope, queue);
}

BSGFXAPI bsgfx_PrefabMetadata* _preval_bsgfx_prefabMetadata(int mesh_id) {
    return next.bsgfx_prefabMetadata(mesh_id);
}

BSGFXAPI void _preval_bsgfx_loadPrefabs(int package_id, bs_Model* model) {
    BSGFX_VALIDATE(model != NULL, ,);
    next.bsgfx_loadPrefabs(package_id, model);
}

BSGFXAPI void _preval_bsgfx_prefabTransform(bsgfx_Prefab* prefab, bs_mat4* out) {
    BSGFX_VALIDATE(prefab != NULL, ,);
    BSGFX_VALIDATE(out != NULL, ,);
    next.bsgfx_prefabTransform(prefab, out);
}

BSGFXAPI int _preval_bsgfx_instancePrefabModel(int mesh_id, bs_mat4 transform, bsgfx_PrefabSubtype prefab_subtype, int material_id) {
    return next.bsgfx_instancePrefabModel(mesh_id, transform, prefab_subtype, material_id);
}

BSGFXAPI int _preval_bsgfx_instancePrefab(int id, bsgfx_PrefabSubtype prefab_subtype) {
    return next.bsgfx_instancePrefab(id, prefab_subtype);
}

BSGFXAPI void _preval_bsgfx_instancePrefabs() {
    next.bsgfx_instancePrefabs();
}

BSGFXAPI void _preval_bsgfx_renderPrefabs(bs_Queue* queue, bs_Pipeline* pipeline, int key_start) {
    BSGFX_VALIDATE(queue != NULL, ,);
    BSGFX_VALIDATE(pipeline != NULL, ,);
    next.bsgfx_renderPrefabs(queue, pipeline, key_start);
}

BSGFXAPI void _preval_bsgfx_renderPrefabPrimitives(bs_Queue* queue, bs_Pipeline* pipeline, int key_start) {
    BSGFX_VALIDATE(queue != NULL, ,);
    BSGFX_VALIDATE(pipeline != NULL, ,);
    next.bsgfx_renderPrefabPrimitives(queue, pipeline, key_start);
}

BSGFXAPI int _preval_bsgfx_queryPrefabId(const bs_GUID* guid) {
    BSGFX_VALIDATE(guid != NULL, 0,);
    return next.bsgfx_queryPrefabId(guid);
}

BSGFXAPI int _preval_bsgfx_closestPrefab(bs_U64 mesh_name_hash, bs_vec3 position, float radius) {
    return next.bsgfx_closestPrefab(mesh_name_hash, position, radius);
}

BSGFXAPI void _preval_bsgfx_primitivePosition(const bsgfx_RawPrimitive* primitive, bs_vec3* out) {
    BSGFX_VALIDATE(primitive != NULL, ,);
    BSGFX_VALIDATE(out != NULL, ,);
    next.bsgfx_primitivePosition(primitive, out);
}

BSGFXAPI void _preval_bsgfx_loadPrimitives(int package_id) {
    next.bsgfx_loadPrimitives(package_id);
}

BSGFXAPI bsgfx_InstanceSubtype* _preval_bsgfx_primitiveSubtype(bsgfx_PrimitiveType type) {
    return next.bsgfx_primitiveSubtype(type);
}

BSGFXAPI int _preval_bsgfx_instancePrimitive(bsgfx_InstanceSubtype* subtype, bs_mat4 transform, bs_U32 flags, int id, int material) {
    BSGFX_VALIDATE(subtype != NULL, 0,);
    return next.bsgfx_instancePrimitive(subtype, transform, flags, id, material);
}

BSGFXAPI int _preval_bsgfx_queryTilePrimitive(int tile_id) {
    return next.bsgfx_queryTilePrimitive(tile_id);
}

BSGFXAPI void _preval_bsgfx_instancePrimitives() {
    next.bsgfx_instancePrimitives();
}

BSGFXAPI void _preval_bsgfx_renderPrimitives(bs_RendererScope* scope, bs_Queue* queue, bs_mat4 camera) {
    BSGFX_VALIDATE(scope != NULL, ,);
    BSGFX_VALIDATE(queue != NULL, ,);
    next.bsgfx_renderPrimitives(scope, queue, camera);
}

BSGFXAPI int _preval_bsgfx_queryPrimitive(bs_GUID* guid) {
    BSGFX_VALIDATE(guid != NULL, 0,);
    return next.bsgfx_queryPrimitive(guid);
}

BSGFXAPI void _preval_bsgfx_loadSpawners(int package_id) {
    next.bsgfx_loadSpawners(package_id);
}

BSGFXAPI void _preval_bsgfx_spawn(bsgfx_Spawner* spawner) {
    BSGFX_VALIDATE(spawner != NULL, ,);
    next.bsgfx_spawn(spawner);
}

BSGFXAPI void _preval_bsgfx_loadTiles(int package_id, bool force_destroy) {
    next.bsgfx_loadTiles(package_id, force_destroy);
}

BSGFXAPI void _preval_bsgfx_instanceTiles() {
    next.bsgfx_instanceTiles();
}

BSGFXAPI void _preval_bsgfx_pushTile(const bs_Batch* batch, const bs_Quad* quad, bs_vec3 normal, bs_U32 index, int image_index, bs_Range* out_range) {
    BSGFX_VALIDATE(batch != NULL, ,);
    BSGFX_VALIDATE(quad != NULL, ,);
    BSGFX_VALIDATE(out_range != NULL, ,);
    next.bsgfx_pushTile(batch, quad, normal, index, image_index, out_range);
}

BSGFXAPI void _preval_bsgfx_batchTile(const bs_Batch* batch, const bs_U32* offset, const bs_Quad* quad, bs_vec3 normal, bs_U32 index, int image_index) {
    BSGFX_VALIDATE(batch != NULL, ,);
    BSGFX_VALIDATE(offset != NULL, ,);
    BSGFX_VALIDATE(quad != NULL, ,);
    next.bsgfx_batchTile(batch, offset, quad, normal, index, image_index);
}

BSGFXAPI const bsgfx_TileAxis* _preval_bsgfx_tileAxes() {
    return next.bsgfx_tileAxes();
}

BSGFXAPI void _preval_bsgfx_tilePosition(const bsgfx_Primitive* primitive, int axis, int x, int y, bs_vec3* out) {
    BSGFX_VALIDATE(primitive != NULL, ,);
    BSGFX_VALIDATE(out != NULL, ,);
    next.bsgfx_tilePosition(primitive, axis, x, y, out);
}

BSGFXAPI void _preval_bsgfx_tileRotation(int axis, bs_vec4* out) {
    BSGFX_VALIDATE(out != NULL, ,);
    next.bsgfx_tileRotation(axis, out);
}

BSGFXAPI void _preval_bsgfx_tileEulerRotation(int axis, bs_vec3* out) {
    BSGFX_VALIDATE(out != NULL, ,);
    next.bsgfx_tileEulerRotation(axis, out);
}

BSGFXAPI void _preval_bsgfx_pushTileAt(const bs_Batch* batch, const bsgfx_Primitive* primitive, int axis, int x, int y, bs_U32 index, int image_index, bs_U32* out) {
    BSGFX_VALIDATE(batch != NULL, ,);
    BSGFX_VALIDATE(primitive != NULL, ,);
    BSGFX_VALIDATE(out != NULL, ,);
    next.bsgfx_pushTileAt(batch, primitive, axis, x, y, index, image_index, out);
}

BSGFXAPI void _preval_bsgfx_tileCoordinate(const bsgfx_Primitive* primitive, int axis, int index, bs_ivec2* out) {
    BSGFX_VALIDATE(primitive != NULL, ,);
    BSGFX_VALIDATE(out != NULL, ,);
    next.bsgfx_tileCoordinate(primitive, axis, index, out);
}

BSGFXAPI void _preval_bsgfx_tileAxis(const bsgfx_Primitive* primitive, int index, int* out) {
    BSGFX_VALIDATE(primitive != NULL, ,);
    BSGFX_VALIDATE(out != NULL, ,);
    next.bsgfx_tileAxis(primitive, index, out);
}

BSGFXAPI void _preval_bsgfx_tileIndex(const bsgfx_Primitive* primitive, int axis, int x, int y, bs_U32* out) {
    BSGFX_VALIDATE(primitive != NULL, ,);
    BSGFX_VALIDATE(out != NULL, ,);
    next.bsgfx_tileIndex(primitive, axis, x, y, out);
}

BSGFXAPI bool _preval_bsgfx_instanceWidgets(bsgfx_Menu menu, bsgfx_TitleBar* title_bar, bsgfx_MenuTabBar* tab_bar) {
    return next.bsgfx_instanceWidgets(menu, title_bar, tab_bar);
}

BSGFXAPI void _preval_bsgfx_instantiateTextUI(bsgfx_UIText text, bsgfx_UIElement* element) {
    BSGFX_VALIDATE(element != NULL, ,);
    next.bsgfx_instantiateTextUI(text, element);
}

BSGFXAPI void _preval_bsgfx_instantiateSolidUI(bsgfx_UISolid solid, bsgfx_UIElement* element) {
    BSGFX_VALIDATE(element != NULL, ,);
    next.bsgfx_instantiateSolidUI(solid, element);
}

BSGFXAPI void _preval_bsgfx_instantiateSolidUIElement(bsgfx_UISolid solid, const bsgfx_UIElement* element) {
    BSGFX_VALIDATE(element != NULL, ,);
    next.bsgfx_instantiateSolidUIElement(solid, element);
}

BSGFXAPI void _preval_bsgfx_solidUIElement(bsgfx_UISolid solid, bsgfx_UIElement* element) {
    BSGFX_VALIDATE(element != NULL, ,);
    next.bsgfx_solidUIElement(solid, element);
}

BSGFXAPI void _preval_bsgfx_instantiateAtlasIconUI(bsgfx_UIIcon icon, bsgfx_UIElement* element) {
    BSGFX_VALIDATE(element != NULL, ,);
    next.bsgfx_instantiateAtlasIconUI(icon, element);
}

BSGFXAPI void _preval_bsgfx_instantiateAtlasIconUIElement(bsgfx_UIIcon icon, const bsgfx_UIElement* element) {
    BSGFX_VALIDATE(element != NULL, ,);
    next.bsgfx_instantiateAtlasIconUIElement(icon, element);
}

BSGFXAPI void _preval_bsgfx_atlasIconUIElement(bsgfx_UIIcon icon, bsgfx_UIElement* element) {
    BSGFX_VALIDATE(element != NULL, ,);
    next.bsgfx_atlasIconUIElement(icon, element);
}

BSGFXAPI bool _preval_bsgfx_hoveringUIElement(const bsgfx_UIElement* element) {
    BSGFX_VALIDATE(element != NULL, false,);
    return next.bsgfx_hoveringUIElement(element);
}

BSGFXAPI void _preval_bsgfx_renderColorPickers(bs_RendererScope* scope, bs_Queue* queue) {
    BSGFX_VALIDATE(scope != NULL, ,);
    BSGFX_VALIDATE(queue != NULL, ,);
    next.bsgfx_renderColorPickers(scope, queue);
}

bsgfx_FunctionTable* _preval_bsgfx_getFunctionTable() {
    static bsgfx_FunctionTable functions = { 0 };

    functions.bsgfx_test = _preval_bsgfx_test;
    functions.bsgfx_subtypes = _preval_bsgfx_subtypes;
    functions.bsgfx_instanceTypes = _preval_bsgfx_instanceTypes;
    functions.bsgfx_computeContextCamera = _preval_bsgfx_computeContextCamera;
    functions.bsgfx_tickInstanceTypes = _preval_bsgfx_tickInstanceTypes;
    functions.bsgfx_resetInstanceTypes = _preval_bsgfx_resetInstanceTypes;
    functions.bsgfx_textDimensions = _preval_bsgfx_textDimensions;
    functions.bsgfx_defaultPipelineHash = _preval_bsgfx_defaultPipelineHash;
    functions.bsgfx_renderTileIcons = _preval_bsgfx_renderTileIcons;
    functions.bsgfx_renderAtlasIcons = _preval_bsgfx_renderAtlasIcons;
    functions.bsgfx_renderLineModel = _preval_bsgfx_renderLineModel;
    functions.bsgfx_renderLines = _preval_bsgfx_renderLines;
    functions.bsgfx_renderPoints = _preval_bsgfx_renderPoints;
    functions.bsgfx_renderAtlas = _preval_bsgfx_renderAtlas;
    functions.bsgfx_renderPrimitiveTiles = _preval_bsgfx_renderPrimitiveTiles;
    functions.bsgfx_swapBufferBindings = _preval_bsgfx_swapBufferBindings;
    functions.bsgfx_requiredForShadowVolumes = _preval_bsgfx_requiredForShadowVolumes;
    functions.bsgfx_requiredForStencilShadows = _preval_bsgfx_requiredForStencilShadows;
    functions.bsgfx_requiredForTransparency = _preval_bsgfx_requiredForTransparency;
    functions.bsgfx_currentScene = _preval_bsgfx_currentScene;
    functions.bsgfx_loadScene = _preval_bsgfx_loadScene;
    functions.bsgfx_validateSubtype = _preval_bsgfx_validateSubtype;
    functions.bsgfx_validateInstanceType = _preval_bsgfx_validateInstanceType;
    functions.bsgfx_worldToScreen = _preval_bsgfx_worldToScreen;
    functions.bsgfx_materialCategoryName = _preval_bsgfx_materialCategoryName;
    functions.bsgfx_materials = _preval_bsgfx_materials;
    functions.bsgfx_queryMaterialHash = _preval_bsgfx_queryMaterialHash;
    functions.bsgfx_fetchMaterial = _preval_bsgfx_fetchMaterial;
    functions.bsgfx_queryMaterial = _preval_bsgfx_queryMaterial;
    functions.bsgfx_loadMaterials = _preval_bsgfx_loadMaterials;
    functions.bsgfx_material = _preval_bsgfx_material;
    functions.bsgfx_materialN = _preval_bsgfx_materialN;
    functions.bsgfx_materialV = _preval_bsgfx_materialV;
    functions.bsgfx_highlightMaterial = _preval_bsgfx_highlightMaterial;
    functions.bsgfx_unhighlightMaterial = _preval_bsgfx_unhighlightMaterial;
    functions.bsgfx_tickMaterials = _preval_bsgfx_tickMaterials;
    functions.bsgfx_sweepCollisions = _preval_bsgfx_sweepCollisions;
    functions.bsgfx_collider = _preval_bsgfx_collider;
    functions.bsgfx_applyCollisions = _preval_bsgfx_applyCollisions;
    functions.bsgfx_printCollisions = _preval_bsgfx_printCollisions;
    functions.bsgfx_instanceSweepCollisions = _preval_bsgfx_instanceSweepCollisions;
    functions.bsgfx_instanceCollider = _preval_bsgfx_instanceCollider;
    functions.bsgfx_skeleton = _preval_bsgfx_skeleton;
    functions.bsgfx_animationFrame = _preval_bsgfx_animationFrame;
    functions.bsgfx_animationFrameCount = _preval_bsgfx_animationFrameCount;
    functions.bsgfx_applyAnimationVelocity = _preval_bsgfx_applyAnimationVelocity;
    functions.bsgfx_queueAnimation = _preval_bsgfx_queueAnimation;
    functions.bsgfx_runAnimator = _preval_bsgfx_runAnimator;
    functions.bsgfx_animator = _preval_bsgfx_animator;
    functions.bsgfx_ensureInstanceCount = _preval_bsgfx_ensureInstanceCount;
    functions.bsgfx_instanceType = _preval_bsgfx_instanceType;
    functions.bsgfx_deleteSubtype = _preval_bsgfx_deleteSubtype;
    functions.bsgfx_subtype = _preval_bsgfx_subtype;
    functions.bsgfx_instantiate = _preval_bsgfx_instantiate;
    functions.bsgfx_tickInstanceType = _preval_bsgfx_tickInstanceType;
    functions.bsgfx_renderSubtype = _preval_bsgfx_renderSubtype;
    functions.bsgfx_resetInstanceType = _preval_bsgfx_resetInstanceType;
    functions.bsgfx_instanceHiResMesh = _preval_bsgfx_instanceHiResMesh;
    functions.bsgfx_instanceMesh = _preval_bsgfx_instanceMesh;
    functions.bsgfx_instanceBoneMesh = _preval_bsgfx_instanceBoneMesh;
    functions.bsgfx_instanceDepthlessLine = _preval_bsgfx_instanceDepthlessLine;
    functions.bsgfx_instanceLine = _preval_bsgfx_instanceLine;
    functions.bsgfx_instanceRay = _preval_bsgfx_instanceRay;
    functions.bsgfx_instanceAabb = _preval_bsgfx_instanceAabb;
    functions.bsgfx_instanceSphere = _preval_bsgfx_instanceSphere;
    functions.bsgfx_instanceCone = _preval_bsgfx_instanceCone;
    functions.bsgfx_instancePoint = _preval_bsgfx_instancePoint;
    functions.bsgfx_instantiateQuad = _preval_bsgfx_instantiateQuad;
    functions.bsgfx_instanceDepthlessCircle = _preval_bsgfx_instanceDepthlessCircle;
    functions.bsgfx_instanceAtlas = _preval_bsgfx_instanceAtlas;
    functions.bsgfx_instanceAtlasFlipped = _preval_bsgfx_instanceAtlasFlipped;
    functions.bsgfx_fontHeight = _preval_bsgfx_fontHeight;
    functions.bsgfx_instanceASCIIText = _preval_bsgfx_instanceASCIIText;
    functions.bsgfx_instanceASCIITextN = _preval_bsgfx_instanceASCIITextN;
    functions.bsgfx_instanceASCIITextV = _preval_bsgfx_instanceASCIITextV;
    functions.bsgfx_matrix = _preval_bsgfx_matrix;
    functions.bsgfx_renderFineShadowVolumes = _preval_bsgfx_renderFineShadowVolumes;
    functions.bsgfx_renderShadowVolumes = _preval_bsgfx_renderShadowVolumes;
    functions.bsgfx_computeShadowVolumes = _preval_bsgfx_computeShadowVolumes;
    functions.bsgfx_prefabModel = _preval_bsgfx_prefabModel;
    functions.bsgfx_package = _preval_bsgfx_package;
    functions.bsgfx_ini = _preval_bsgfx_ini;
    functions.bsgfx_tick = _preval_bsgfx_tick;
    functions.bsgfx_app = _preval_bsgfx_app;
    functions.bsgfx_callbacks = _preval_bsgfx_callbacks;
    functions.bsgfx_settings = _preval_bsgfx_settings;
    functions.bsgfx_setCamera = _preval_bsgfx_setCamera;
    functions.bsgfx_type = _preval_bsgfx_type;
    functions.bsgfx_map = _preval_bsgfx_map;
    functions.bsgfx_remap = _preval_bsgfx_remap;
    functions.bsgfx_count = _preval_bsgfx_count;
    functions.bsgfx_get = _preval_bsgfx_get;
    functions.bsgfx_getType = _preval_bsgfx_getType;
    functions.bsgfx_id = _preval_bsgfx_id;
    functions.bsgfx_rawId = _preval_bsgfx_rawId;
    functions.bsgfx_getRaw = _preval_bsgfx_getRaw;
    functions.bsgfx_flexibleCount = _preval_bsgfx_flexibleCount;
    functions.bsgfx_loadLights = _preval_bsgfx_loadLights;
    functions.bsgfx_computePrefabShadows = _preval_bsgfx_computePrefabShadows;
    functions.bsgfx_renderPrefabShadowVolumes = _preval_bsgfx_renderPrefabShadowVolumes;
    functions.bsgfx_prefabMetadata = _preval_bsgfx_prefabMetadata;
    functions.bsgfx_loadPrefabs = _preval_bsgfx_loadPrefabs;
    functions.bsgfx_prefabTransform = _preval_bsgfx_prefabTransform;
    functions.bsgfx_instancePrefabModel = _preval_bsgfx_instancePrefabModel;
    functions.bsgfx_instancePrefab = _preval_bsgfx_instancePrefab;
    functions.bsgfx_instancePrefabs = _preval_bsgfx_instancePrefabs;
    functions.bsgfx_renderPrefabs = _preval_bsgfx_renderPrefabs;
    functions.bsgfx_renderPrefabPrimitives = _preval_bsgfx_renderPrefabPrimitives;
    functions.bsgfx_queryPrefabId = _preval_bsgfx_queryPrefabId;
    functions.bsgfx_closestPrefab = _preval_bsgfx_closestPrefab;
    functions.bsgfx_primitivePosition = _preval_bsgfx_primitivePosition;
    functions.bsgfx_loadPrimitives = _preval_bsgfx_loadPrimitives;
    functions.bsgfx_primitiveSubtype = _preval_bsgfx_primitiveSubtype;
    functions.bsgfx_instancePrimitive = _preval_bsgfx_instancePrimitive;
    functions.bsgfx_queryTilePrimitive = _preval_bsgfx_queryTilePrimitive;
    functions.bsgfx_instancePrimitives = _preval_bsgfx_instancePrimitives;
    functions.bsgfx_renderPrimitives = _preval_bsgfx_renderPrimitives;
    functions.bsgfx_queryPrimitive = _preval_bsgfx_queryPrimitive;
    functions.bsgfx_loadSpawners = _preval_bsgfx_loadSpawners;
    functions.bsgfx_spawn = _preval_bsgfx_spawn;
    functions.bsgfx_loadTiles = _preval_bsgfx_loadTiles;
    functions.bsgfx_instanceTiles = _preval_bsgfx_instanceTiles;
    functions.bsgfx_pushTile = _preval_bsgfx_pushTile;
    functions.bsgfx_batchTile = _preval_bsgfx_batchTile;
    functions.bsgfx_tileAxes = _preval_bsgfx_tileAxes;
    functions.bsgfx_tilePosition = _preval_bsgfx_tilePosition;
    functions.bsgfx_tileRotation = _preval_bsgfx_tileRotation;
    functions.bsgfx_tileEulerRotation = _preval_bsgfx_tileEulerRotation;
    functions.bsgfx_pushTileAt = _preval_bsgfx_pushTileAt;
    functions.bsgfx_tileCoordinate = _preval_bsgfx_tileCoordinate;
    functions.bsgfx_tileAxis = _preval_bsgfx_tileAxis;
    functions.bsgfx_tileIndex = _preval_bsgfx_tileIndex;
    functions.bsgfx_instanceWidgets = _preval_bsgfx_instanceWidgets;
    functions.bsgfx_instantiateTextUI = _preval_bsgfx_instantiateTextUI;
    functions.bsgfx_instantiateSolidUI = _preval_bsgfx_instantiateSolidUI;
    functions.bsgfx_instantiateSolidUIElement = _preval_bsgfx_instantiateSolidUIElement;
    functions.bsgfx_solidUIElement = _preval_bsgfx_solidUIElement;
    functions.bsgfx_instantiateAtlasIconUI = _preval_bsgfx_instantiateAtlasIconUI;
    functions.bsgfx_instantiateAtlasIconUIElement = _preval_bsgfx_instantiateAtlasIconUIElement;
    functions.bsgfx_atlasIconUIElement = _preval_bsgfx_atlasIconUIElement;
    functions.bsgfx_hoveringUIElement = _preval_bsgfx_hoveringUIElement;
    functions.bsgfx_renderColorPickers = _preval_bsgfx_renderColorPickers;

    return &functions;
}

