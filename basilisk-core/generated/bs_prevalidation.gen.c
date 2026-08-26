
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
        
#include <basilisk-core.h>
#include <bs_internal.h>

static bs_FunctionTable next = { 0 };

const bs_FunctionTable* _preval_bs_setFunctions(const bs_FunctionTable* a, bs_FunctionTable* b) {
    memcpy(&next, a, sizeof(next));

	if (!b) return &next;

    for (size_t offset = 0; offset < sizeof(bs_FunctionTable); offset += sizeof(void*)) {
        bs_Callback* f_a = ((unsigned char*)&next) + offset;
        bs_Callback* f_b = ((unsigned char*)b) + offset;
        if (!*f_a) 
            *f_a = *f_b;
    }

    return &next;
}

BSAPI bs_Callbacks* _preval_bs_callbacks() {
    return next.bs_callbacks();
}

BSAPI bs_Scope* _preval_bs_scope() {
    return next.bs_scope();
}

BSAPI void _preval_bs_writeLogFile(char* value) {
    BS_VALIDATE(value != NULL, ,);
    next.bs_writeLogFile(value);
}

BSAPI void _preval_bs_writeLogFileN(char* value, int value_length) {
    BS_VALIDATE(value != NULL, ,);
    next.bs_writeLogFileN(value, value_length);
}

BSAPI void _preval_bs_writeLogFileV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, ,);
    next.bs_writeLogFileV(format, args);
}

BSAPI void _preval_bs_v2Mid(const bs_vec2* a, const bs_vec2* b, bs_vec2* out) {
    BS_VALIDATE(a != NULL, ,);
    BS_VALIDATE(b != NULL, ,);
    BS_VALIDATE(out != NULL, ,);
    next.bs_v2Mid(a, b, out);
}

BSAPI void _preval_bs_v3Mid(const bs_vec3* a, const bs_vec3* b, bs_vec3* out) {
    BS_VALIDATE(a != NULL, ,);
    BS_VALIDATE(b != NULL, ,);
    BS_VALIDATE(out != NULL, ,);
    next.bs_v3Mid(a, b, out);
}

BSAPI bs_mat4x3 _preval_bs_m4x3(const bs_mat4* m) {
    BS_VALIDATE(m != NULL, (bs_mat4x3) { 0 },);
    return next.bs_m4x3(m);
}

BSAPI void _preval_bs_eulToQ(const bs_vec3* eul, bs_vec4* out) {
    BS_VALIDATE(eul != NULL, ,);
    BS_VALIDATE(out != NULL, ,);
    next.bs_eulToQ(eul, out);
}

BSAPI void _preval_bs_qToEul(const bs_vec4* q, bs_vec3* out) {
    BS_VALIDATE(q != NULL, ,);
    BS_VALIDATE(out != NULL, ,);
    next.bs_qToEul(q, out);
}

BSAPI void _preval_bs_v2CubicBezier(const bs_vec2* p0, const bs_vec2* p1, const bs_vec2* p2, const bs_vec2* p3, bs_vec2* out, int out_length) {
    BS_VALIDATE(p0 != NULL, ,);
    BS_VALIDATE(p1 != NULL, ,);
    BS_VALIDATE(p2 != NULL, ,);
    BS_VALIDATE(p3 != NULL, ,);
    BS_VALIDATE(out != NULL, ,);
    next.bs_v2CubicBezier(p0, p1, p2, p3, out, out_length);
}

BSAPI void _preval_bs_v2QuadBezier(const bs_vec2* p0, const bs_vec2* p1, const bs_vec2* p2, bs_vec2* out, int out_length) {
    BS_VALIDATE(p0 != NULL, ,);
    BS_VALIDATE(p1 != NULL, ,);
    BS_VALIDATE(p2 != NULL, ,);
    BS_VALIDATE(out != NULL, ,);
    next.bs_v2QuadBezier(p0, p1, p2, out, out_length);
}

BSAPI void _preval_bs_v3CubicBezier(const bs_vec3* p0, const bs_vec3* p1, const bs_vec3* p2, const bs_vec3* p3, bs_vec3* out, int out_length) {
    BS_VALIDATE(p0 != NULL, ,);
    BS_VALIDATE(p1 != NULL, ,);
    BS_VALIDATE(p2 != NULL, ,);
    BS_VALIDATE(p3 != NULL, ,);
    BS_VALIDATE(out != NULL, ,);
    next.bs_v3CubicBezier(p0, p1, p2, p3, out, out_length);
}

BSAPI void _preval_bs_v3QuadBezier(const bs_vec3* p0, const bs_vec3* p1, const bs_vec3* p2, bs_vec3* out, int out_length) {
    BS_VALIDATE(p0 != NULL, ,);
    BS_VALIDATE(p1 != NULL, ,);
    BS_VALIDATE(p2 != NULL, ,);
    BS_VALIDATE(out != NULL, ,);
    next.bs_v3QuadBezier(p0, p1, p2, out, out_length);
}

BSAPI void _preval_bs_rotateAabb(const bs_Aabb* aabb, const bs_mat3* rotation_matrix, bs_Aabb* out) {
    BS_VALIDATE(aabb != NULL, ,);
    BS_VALIDATE(rotation_matrix != NULL, ,);
    BS_VALIDATE(out != NULL, ,);
    next.bs_rotateAabb(aabb, rotation_matrix, out);
}

BSAPI void _preval_bs_fitAabb(const bs_Aabb* aabb, const bs_vec2* size, const bs_vec4* rotation, bs_mat4* out) {
    BS_VALIDATE(aabb != NULL, ,);
    BS_VALIDATE(size != NULL, ,);
    BS_VALIDATE(rotation != NULL, ,);
    BS_VALIDATE(out != NULL, ,);
    next.bs_fitAabb(aabb, size, rotation, out);
}

BSAPI void _preval_bs_quad(const bs_vec3* position, const bs_vec2* dimensions, bs_Quad* out) {
    BS_VALIDATE(position != NULL, ,);
    BS_VALIDATE(dimensions != NULL, ,);
    BS_VALIDATE(out != NULL, ,);
    next.bs_quad(position, dimensions, out);
}

BSAPI float _preval_bs_linearTosRGB(float value) {
    return next.bs_linearTosRGB(value);
}

BSAPI float _preval_bs_sRGBToLinear(float value) {
    return next.bs_sRGBToLinear(value);
}

BSAPI bs_vec3 _preval_bs_linearV3TosRGB(const bs_vec3* value) {
    BS_VALIDATE(value != NULL, (bs_vec3) { 0 },);
    return next.bs_linearV3TosRGB(value);
}

BSAPI bs_vec3 _preval_bs_sRGBToLinearV3(const bs_vec3* value) {
    BS_VALIDATE(value != NULL, (bs_vec3) { 0 },);
    return next.bs_sRGBToLinearV3(value);
}

BSAPI bs_RGBA _preval_bs_rgbV4ToUChar(const bs_vec4* value) {
    BS_VALIDATE(value != NULL, (bs_RGBA) { 0 },);
    return next.bs_rgbV4ToUChar(value);
}

BSAPI bs_vec4 _preval_bs_rgbUCharToV4(bs_RGBA value) {
    return next.bs_rgbUCharToV4(value);
}

BSAPI bs_vec3 _preval_bs_hsvToRgb(const bs_vec3* hsv) {
    BS_VALIDATE(hsv != NULL, (bs_vec3) { 0 },);
    return next.bs_hsvToRgb(hsv);
}

BSAPI bs_vec3 _preval_bs_rgbToHsv(const bs_vec3* rgb) {
    BS_VALIDATE(rgb != NULL, (bs_vec3) { 0 },);
    return next.bs_rgbToHsv(rgb);
}

BSAPI bs_Result _preval_bs_convertYyjsonResult(int code) {
    return next.bs_convertYyjsonResult(code);
}

BSAPI bs_Result _preval_bs_convertVulkanResult(int code) {
    return next.bs_convertVulkanResult(code);
}

BSAPI bs_Result _preval_bs_convertWin32Error(int code) {
    return next.bs_convertWin32Error(code);
}

BSAPI const char* _preval_bs_serializeWin32Error(int code) {
    return next.bs_serializeWin32Error(code);
}

BSAPI bs_Result _preval_bs_convertErrno() {
    return next.bs_convertErrno();
}

BSAPI const char* _preval_bs_serializeErrno() {
    return next.bs_serializeErrno();
}

BSAPI bs_Result _preval_bs_playSound(bs_Sound* sound, float volume) {
    BS_VALIDATE(sound != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_playSound(sound, volume);
}

BSAPI bs_Result _preval_bs_sound(bs_Resource* resource, bs_U32 flags) {
    BS_VALIDATE(resource != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_sound(resource, flags);
}

BSAPI bs_Result _preval_bs_iniAudio() {
    return next.bs_iniAudio();
}

BSAPI void _preval_bs_rayVsObb(const bs_Ray* ray, const bs_vec3* position, const bs_vec4* rotation, const bs_vec3* scale, bs_RayVsObb* out) {
    BS_VALIDATE(ray != NULL, ,);
    BS_VALIDATE(position != NULL, ,);
    BS_VALIDATE(rotation != NULL, ,);
    BS_VALIDATE(scale != NULL, ,);
    BS_VALIDATE(out != NULL, ,);
    next.bs_rayVsObb(ray, position, rotation, scale, out);
}

BSAPI bool _preval_bs_sphereVsPoint(const bs_vec3* center, float radius, const bs_vec3* point, bs_SphereVsPoint* out) {
    BS_VALIDATE(center != NULL, false,);
    BS_VALIDATE(point != NULL, false,);
    BS_VALIDATE(out != NULL, false,);
    return next.bs_sphereVsPoint(center, radius, point, out);
}

BSAPI bool _preval_bs_sphereVsObbTest(const bs_vec3* center, float radius, const bs_vec3* position, const bs_vec4* rotation, const bs_vec3* scale) {
    BS_VALIDATE(center != NULL, false,);
    BS_VALIDATE(position != NULL, false,);
    BS_VALIDATE(rotation != NULL, false,);
    BS_VALIDATE(scale != NULL, false,);
    return next.bs_sphereVsObbTest(center, radius, position, rotation, scale);
}

BSAPI bool _preval_bs_sphereVsObb(const bs_vec3* center, float radius, const bs_vec3* position, const bs_vec4* rotation, const bs_vec3* scale, bs_SphereVsBox* out) {
    BS_VALIDATE(center != NULL, false,);
    BS_VALIDATE(position != NULL, false,);
    BS_VALIDATE(rotation != NULL, false,);
    BS_VALIDATE(scale != NULL, false,);
    BS_VALIDATE(out != NULL, false,);
    return next.bs_sphereVsObb(center, radius, position, rotation, scale, out);
}

BSAPI bool _preval_bs_rectangleVsPoint(const bs_vec2* position, const bs_vec2* dimensions, const bs_vec2* point) {
    BS_VALIDATE(position != NULL, false,);
    BS_VALIDATE(dimensions != NULL, false,);
    BS_VALIDATE(point != NULL, false,);
    return next.bs_rectangleVsPoint(position, dimensions, point);
}

BSAPI bool _preval_bs_lineVsLine(const bs_vec2* l1_start, const bs_vec2* l1_end, const bs_vec2* l2_start, const bs_vec2* l2_end, bs_LineVsLine* out) {
    BS_VALIDATE(l1_start != NULL, false,);
    BS_VALIDATE(l1_end != NULL, false,);
    BS_VALIDATE(l2_start != NULL, false,);
    BS_VALIDATE(l2_end != NULL, false,);
    BS_VALIDATE(out != NULL, false,);
    return next.bs_lineVsLine(l1_start, l1_end, l2_start, l2_end, out);
}

BSAPI void _preval_bs_populateVertexDeclaration(bs_VertexDeclaration* declaration, bs_Attribute* attributes, int attributes_count) {
    BS_VALIDATE(declaration != NULL, ,);
    BS_VALIDATE(attributes != NULL, ,);
    next.bs_populateVertexDeclaration(declaration, attributes, attributes_count);
}

BSAPI void _preval_bs_beginComment(bs_Queue* queue, char* value) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(value != NULL, ,);
    next.bs_beginComment(queue, value);
}

BSAPI void _preval_bs_beginCommentN(bs_Queue* queue, char* value, int value_length) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(value != NULL, ,);
    next.bs_beginCommentN(queue, value, value_length);
}

BSAPI void _preval_bs_beginCommentV(bs_Queue* queue, char* format, va_list args) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(format != NULL, ,);
    next.bs_beginCommentV(queue, format, args);
}

BSAPI void _preval_bs_endComment(bs_Queue* queue) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    next.bs_endComment(queue);
}

BSAPI bs_Image* _preval_bs_swapchainImage() {
    return next.bs_swapchainImage();
}

BSAPI void _preval_bs_clearStencil(bs_Queue* queue, bs_U32 index, bs_ivec2 resolution, bs_U32 value) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    next.bs_clearStencil(queue, index, resolution, value);
}

BSAPI void _preval_bs_clearDepth(bs_Queue* queue, bs_U32 index, bs_ivec2 dim, float value) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    next.bs_clearDepth(queue, index, dim, value);
}

BSAPI void _preval_bs_clearDepthStencil(bs_Queue* queue, bs_U32 index, bs_ivec2 dim, float depth_value, bs_U32 stencil_value) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    next.bs_clearDepthStencil(queue, index, dim, depth_value, stencil_value);
}

BSAPI void _preval_bs_clearColor(bs_Queue* queue, bs_U32 index, bs_ivec2 dim, const bs_vec4* color) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(color != NULL, ,);
    next.bs_clearColor(queue, index, dim, color);
}

BSAPI void _preval_bs_stencilReference(bs_Queue* queue, bs_StencilFaceFlag face, bs_U32 reference) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    next.bs_stencilReference(queue, face, reference);
}

BSAPI void _preval_bs_cull(bs_Queue* queue, bs_CullFlags flags) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    next.bs_cull(queue, flags);
}

BSAPI void _preval_bs_setLineWidth(bs_Queue* queue, float width) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    next.bs_setLineWidth(queue, width);
}

BSAPI int _preval_bs_batchSize(bs_Batch* batch) {
    BS_VALIDATE(batch != NULL, 0,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, 0,);
    return next.bs_batchSize(batch);
}

BSAPI void _preval_bs_render(bs_Queue* queue, bs_Batch* batch, bs_Pipeline* pipeline, bs_U32 vertex_offset, bs_U32 vertex_count, bs_U32 first_instance, bs_U32 num_instances) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    BS_VALIDATE(pipeline != NULL, ,);
    next.bs_render(queue, batch, pipeline, vertex_offset, vertex_count, first_instance, num_instances);
}

BSAPI void _preval_bs_barrier(bs_Queue* queue, bs_U32 dependency_flags, bs_U32 src, bs_U32 dst, bs_U32 src_access, bs_U32 dst_access) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    next.bs_barrier(queue, dependency_flags, src, dst, src_access, dst_access);
}

BSAPI void _preval_bs_rayTrace(bs_RayTracer* ray_tracer, bs_Pipeline* pipeline, bs_U32 width, bs_U32 height, bs_U32 depth) {
    BS_VALIDATE(ray_tracer != NULL, ,);
    BS_VALIDATE(ray_tracer->head.type == BS_OBJECT_RAY_TRACER, ,);
    BS_VALIDATE(pipeline != NULL, ,);
    next.bs_rayTrace(ray_tracer, pipeline, width, height, depth);
}

BSAPI bs_Result _preval_bs_rayTracer(bs_Object* object, bs_U32 flags, bs_Shader* shaders[], int shaders_count) {
    BS_VALIDATE(object != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(shaders != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_rayTracer(object, flags, shaders, shaders_count);
}

BSAPI void _preval_bs_accelerateAabb(bs_RayTracer* ray_tracer, bs_Aabb aabb) {
    BS_VALIDATE(ray_tracer != NULL, ,);
    BS_VALIDATE(ray_tracer->head.type == BS_OBJECT_RAY_TRACER, ,);
    next.bs_accelerateAabb(ray_tracer, aabb);
}

BSAPI void _preval_bs_accelerateBatch(bs_RayTracer* ray_tracer, bs_Batch* batch) {
    BS_VALIDATE(ray_tracer != NULL, ,);
    BS_VALIDATE(ray_tracer->head.type == BS_OBJECT_RAY_TRACER, ,);
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    next.bs_accelerateBatch(ray_tracer, batch);
}

BSAPI bs_Result _preval_bs_build(bs_Queue* queue, bs_RayTracer* ray_tracer) {
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(ray_tracer != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(ray_tracer->head.type == BS_OBJECT_RAY_TRACER, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_build(queue, ray_tracer);
}

BSAPI void _preval_bs_destroyRayTracer(bs_RayTracer* ray_tracer) {
    BS_VALIDATE(ray_tracer != NULL, ,);
    BS_VALIDATE(ray_tracer->head.type == BS_OBJECT_RAY_TRACER, ,);
    next.bs_destroyRayTracer(ray_tracer);
}

BSAPI void _preval_bs_dispatchAsync(bs_Queue* queue, bs_Pipeline* pipeline, bs_U32 x, bs_U32 y, bs_U32 z) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(pipeline != NULL, ,);
    next.bs_dispatchAsync(queue, pipeline, x, y, z);
}

BSAPI bs_Result _preval_bs_bufferView(bs_Buffer* buffer, bs_Format format, bs_U64 start, bs_U64 count) {
    BS_VALIDATE(buffer != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(buffer->head.type == BS_OBJECT_BUFFER, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_bufferView(buffer, format, start, count);
}

BSAPI bs_Result _preval_bs_buffer(bs_Object* object, size_t num_bytes, bs_BufferUsageFlags usage_flags, bs_MemoryPropertyFlags memory_flags, bs_BufferBits flags) {
    BS_VALIDATE(object != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_buffer(object, num_bytes, usage_flags, memory_flags, flags);
}

BSAPI bool _preval_bs_bufferIsMapped(bs_Buffer* buffer) {
    BS_VALIDATE(buffer != NULL, false,);
    BS_VALIDATE(buffer->head.type == BS_OBJECT_BUFFER, false,);
    return next.bs_bufferIsMapped(buffer);
}

BSAPI char* _preval_bs_bufferMap(bs_Buffer* buffer) {
    BS_VALIDATE(buffer != NULL, NULL,);
    BS_VALIDATE(buffer->head.type == BS_OBJECT_BUFFER, NULL,);
    return next.bs_bufferMap(buffer);
}

BSAPI bs_Result _preval_bs_mapBuffer(bs_Buffer* buffer, bs_U32 num_bytes) {
    BS_VALIDATE(buffer != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(buffer->head.type == BS_OBJECT_BUFFER, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_mapBuffer(buffer, num_bytes);
}

BSAPI void _preval_bs_unmapBuffer(bs_Buffer* buffer) {
    BS_VALIDATE(buffer != NULL, ,);
    BS_VALIDATE(buffer->head.type == BS_OBJECT_BUFFER, ,);
    next.bs_unmapBuffer(buffer);
}

BSAPI void _preval_bs_stageNull(bs_Buffer* buffer) {
    BS_VALIDATE(buffer != NULL, ,);
    BS_VALIDATE(buffer->head.type == BS_OBJECT_BUFFER, ,);
    next.bs_stageNull(buffer);
}

BSAPI void _preval_bs_stageList(bs_Buffer* buffer, bs_List* list) {
    BS_VALIDATE(buffer != NULL, ,);
    BS_VALIDATE(buffer->head.type == BS_OBJECT_BUFFER, ,);
    BS_VALIDATE(list != NULL, ,);
    BS_VALIDATE(list->unit_size > 0, ,);
    next.bs_stageList(buffer, list);
}

BSAPI void _preval_bs_stageImage(bs_Buffer* buffer, int channels_count, bs_ivec2 dim, const char* data) {
    BS_VALIDATE(buffer != NULL, ,);
    BS_VALIDATE(buffer->head.type == BS_OBJECT_BUFFER, ,);
    BS_VALIDATE(data != NULL, ,);
    next.bs_stageImage(buffer, channels_count, dim, data);
}

BSAPI void _preval_bs_destroyBuffer(bs_Buffer* buffer) {
    BS_VALIDATE(buffer != NULL, ,);
    BS_VALIDATE(buffer->head.type == BS_OBJECT_BUFFER, ,);
    next.bs_destroyBuffer(buffer);
}

BSAPI void _preval_bs_copyAsync(bs_Queue* queue, bs_Buffer* src, bs_Buffer* dst, bs_U32 src_offset, bs_U32 dst_offset, bs_U32 num_bytes) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(src != NULL, ,);
    BS_VALIDATE(src->head.type == BS_OBJECT_BUFFER, ,);
    BS_VALIDATE(dst != NULL, ,);
    BS_VALIDATE(dst->head.type == BS_OBJECT_BUFFER, ,);
    next.bs_copyAsync(queue, src, dst, src_offset, dst_offset, num_bytes);
}

BSAPI void _preval_bs_setBufferAsync(bs_Queue* queue, bs_Buffer* buffer, bs_U32 offset, bs_U32 num_bytes, bs_U32 value) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(buffer != NULL, ,);
    BS_VALIDATE(buffer->head.type == BS_OBJECT_BUFFER, ,);
    next.bs_setBufferAsync(queue, buffer, offset, num_bytes, value);
}

BSAPI bs_Result _preval_bs_batch(bs_Object* object, int index_size, bs_Shader* vertex_shader, bs_BatchBits flags) {
    BS_VALIDATE(object != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(vertex_shader != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_batch(object, index_size, vertex_shader, flags);
}

BSAPI bs_Attribute* _preval_bs_queryAttribute(bs_Batch* batch, char* name) {
    BS_VALIDATE(batch != NULL, NULL,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, NULL,);
    BS_VALIDATE(name != NULL, NULL,);
    return next.bs_queryAttribute(batch, name);
}

BSAPI bs_Attribute* _preval_bs_queryAttributeN(bs_Batch* batch, char* name, int name_length) {
    BS_VALIDATE(batch != NULL, NULL,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, NULL,);
    BS_VALIDATE(name != NULL, NULL,);
    return next.bs_queryAttributeN(batch, name, name_length);
}

BSAPI bs_Attribute* _preval_bs_queryAttributeV(bs_Batch* batch, char* format, va_list args) {
    BS_VALIDATE(batch != NULL, NULL,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, NULL,);
    BS_VALIDATE(format != NULL, NULL,);
    return next.bs_queryAttributeV(batch, format, args);
}

BSAPI bool _preval_bs_canPushBatch(bs_Batch* batch) {
    BS_VALIDATE(batch != NULL, false,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, false,);
    return next.bs_canPushBatch(batch);
}

BSAPI bool _preval_bs_batchIsIndexed(bs_Batch* batch) {
    BS_VALIDATE(batch != NULL, false,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, false,);
    return next.bs_batchIsIndexed(batch);
}

BSAPI void _preval_bs_minimizeBatch(bs_Batch* batch) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    next.bs_minimizeBatch(batch);
}

BSAPI bs_Result _preval_bs_pushBatch(bs_Queue* queue, bs_Batch* batch, bs_U32 num_index_bytes, bs_U32 num_vertex_bytes) {
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(batch != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_pushBatch(queue, batch, num_index_bytes, num_vertex_bytes);
}

BSAPI void _preval_bs_unpushBatch(bs_Batch* batch) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    next.bs_unpushBatch(batch);
}

BSAPI void _preval_bs_destroyBatch(bs_Batch* batch) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    next.bs_destroyBatch(batch);
}

BSAPI void _preval_bs_ensureBatchSize(bs_Batch* batch, bs_U32 num_indices, bs_U32 num_vertices) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    next.bs_ensureBatchSize(batch, num_indices, num_vertices);
}

BSAPI void _preval_bs_batchVertex(bs_VertexDeclaration* declaration, const unsigned char* src) {
    BS_VALIDATE(declaration != NULL, ,);
    BS_VALIDATE(src != NULL, ,);
    next.bs_batchVertex(declaration, src);
}

BSAPI bs_Range _preval_bs_batchRange(bs_Batch* batch, bs_U32 offset) {
    BS_VALIDATE(batch != NULL, (bs_Range) { 0 },);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, (bs_Range) { 0 },);
    return next.bs_batchRange(batch, offset);
}

BSAPI void _preval_bs_pushIndex(bs_Batch* batch, int index) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    next.bs_pushIndex(batch, index);
}

BSAPI void _preval_bs_pushIndices(bs_Batch* batch, int indices[], int indices_count) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    next.bs_pushIndices(batch, indices, indices_count);
}

BSAPI void _preval_bs_batchCube(bs_Batch* batch, bs_U32* offset, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    BS_VALIDATE(offset != NULL, ,);
    next.bs_batchCube(batch, offset, color);
}

BSAPI bs_Range _preval_bs_pushCube(bs_Batch* batch, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, (bs_Range) { 0 },);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, (bs_Range) { 0 },);
    return next.bs_pushCube(batch, color);
}

BSAPI void _preval_bs_batchCone(bs_Batch* batch, bs_U32* offset, int segments, float height, float radius, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    BS_VALIDATE(offset != NULL, ,);
    next.bs_batchCone(batch, offset, segments, height, radius, color);
}

BSAPI bs_Range _preval_bs_pushCone(bs_Batch* batch, int segments, float height, float radius, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, (bs_Range) { 0 },);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, (bs_Range) { 0 },);
    return next.bs_pushCone(batch, segments, height, radius, color);
}

BSAPI void _preval_bs_batchQuad(bs_Batch* batch, bs_U32* offset, const bs_Quad* quad, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    BS_VALIDATE(offset != NULL, ,);
    BS_VALIDATE(quad != NULL, ,);
    next.bs_batchQuad(batch, offset, quad, color);
}

BSAPI bs_Range _preval_bs_pushQuad(bs_Batch* batch, const bs_Quad* quad, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, (bs_Range) { 0 },);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, (bs_Range) { 0 },);
    BS_VALIDATE(quad != NULL, (bs_Range) { 0 },);
    return next.bs_pushQuad(batch, quad, color);
}

BSAPI void _preval_bs_batchTriangle(bs_Batch* batch, bs_U32* offset, bs_vec3 a, bs_vec3 b, bs_vec3 c, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    BS_VALIDATE(offset != NULL, ,);
    next.bs_batchTriangle(batch, offset, a, b, c, color);
}

BSAPI bs_Range _preval_bs_pushTriangle(bs_Batch* batch, bs_vec3 a, bs_vec3 b, bs_vec3 c, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, (bs_Range) { 0 },);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, (bs_Range) { 0 },);
    return next.bs_pushTriangle(batch, a, b, c, color);
}

BSAPI void _preval_bs_batchLine(bs_Batch* batch, bs_U32* offset, bs_vec3 start, bs_vec3 end, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    BS_VALIDATE(offset != NULL, ,);
    next.bs_batchLine(batch, offset, start, end, color);
}

BSAPI bs_Range _preval_bs_pushLine(bs_Batch* batch, bs_vec3 start, bs_vec3 end, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, (bs_Range) { 0 },);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, (bs_Range) { 0 },);
    return next.bs_pushLine(batch, start, end, color);
}

BSAPI void _preval_bs_batchPoint(bs_Batch* batch, bs_U32* offset, bs_vec3 position, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    BS_VALIDATE(offset != NULL, ,);
    next.bs_batchPoint(batch, offset, position, color);
}

BSAPI bs_Range _preval_bs_pushPoint(bs_Batch* batch, bs_vec3 position, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, (bs_Range) { 0 },);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, (bs_Range) { 0 },);
    return next.bs_pushPoint(batch, position, color);
}

BSAPI void _preval_bs_batchAabb(bs_Batch* batch, bs_U32* offset, bs_Aabb* aabb, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    BS_VALIDATE(offset != NULL, ,);
    BS_VALIDATE(aabb != NULL, ,);
    next.bs_batchAabb(batch, offset, aabb, color);
}

BSAPI bs_Range _preval_bs_pushAabb(bs_Batch* batch, bs_Aabb* aabb, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, (bs_Range) { 0 },);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, (bs_Range) { 0 },);
    BS_VALIDATE(aabb != NULL, (bs_Range) { 0 },);
    return next.bs_pushAabb(batch, aabb, color);
}

BSAPI void _preval_bs_batchSphere(bs_Batch* batch, bs_U32* offset, bs_vec3 position, float radius, bs_U32 lats, bs_U32 longs, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    BS_VALIDATE(offset != NULL, ,);
    next.bs_batchSphere(batch, offset, position, radius, lats, longs, color);
}

BSAPI bs_Range _preval_bs_pushSphere(bs_Batch* batch, bs_vec3 position, float radius, bs_U32 lats, bs_U32 longs, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, (bs_Range) { 0 },);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, (bs_Range) { 0 },);
    return next.bs_pushSphere(batch, position, radius, lats, longs, color);
}

BSAPI void _preval_bs_batchPyramid(bs_Batch* batch, bs_U32* offset, bs_vec3 pos, float width, float height, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    BS_VALIDATE(offset != NULL, ,);
    next.bs_batchPyramid(batch, offset, pos, width, height, color);
}

BSAPI bs_Range _preval_bs_pushPyramid(bs_Batch* batch, bs_vec3 pos, float width, float height, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, (bs_Range) { 0 },);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, (bs_Range) { 0 },);
    return next.bs_pushPyramid(batch, pos, width, height, color);
}

BSAPI void _preval_bs_batchBipyramid(bs_Batch* batch, bs_U32* offset, bs_vec3 pos, float width, float height, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    BS_VALIDATE(offset != NULL, ,);
    next.bs_batchBipyramid(batch, offset, pos, width, height, color);
}

BSAPI bs_Range _preval_bs_pushBipyramid(bs_Batch* batch, bs_vec3 pos, float width, float height, bs_RGBA color) {
    BS_VALIDATE(batch != NULL, (bs_Range) { 0 },);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, (bs_Range) { 0 },);
    return next.bs_pushBipyramid(batch, pos, width, height, color);
}

BSAPI void _preval_bs_batchPrimitive(bs_Batch* batch, bs_U32* offset, bs_Primitive* primitive) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    BS_VALIDATE(offset != NULL, ,);
    BS_VALIDATE(primitive != NULL, ,);
    next.bs_batchPrimitive(batch, offset, primitive);
}

BSAPI bs_Range _preval_bs_pushPrimitive(bs_Batch* batch, bs_Primitive* primitive) {
    BS_VALIDATE(batch != NULL, (bs_Range) { 0 },);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, (bs_Range) { 0 },);
    BS_VALIDATE(primitive != NULL, (bs_Range) { 0 },);
    return next.bs_pushPrimitive(batch, primitive);
}

BSAPI void _preval_bs_batchMesh(bs_Batch* batch, bs_U32* offset, bs_Mesh* mesh) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    BS_VALIDATE(offset != NULL, ,);
    BS_VALIDATE(mesh != NULL, ,);
    next.bs_batchMesh(batch, offset, mesh);
}

BSAPI bs_Range _preval_bs_pushMesh(bs_Batch* batch, bs_Mesh* mesh) {
    BS_VALIDATE(batch != NULL, (bs_Range) { 0 },);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, (bs_Range) { 0 },);
    BS_VALIDATE(mesh != NULL, (bs_Range) { 0 },);
    return next.bs_pushMesh(batch, mesh);
}

BSAPI void _preval_bs_batchModel(bs_Batch* batch, bs_U32* offset, bs_Model* model) {
    BS_VALIDATE(batch != NULL, ,);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, ,);
    BS_VALIDATE(offset != NULL, ,);
    BS_VALIDATE(model != NULL, ,);
    next.bs_batchModel(batch, offset, model);
}

BSAPI bs_Range _preval_bs_pushModel(bs_Batch* batch, bs_Model* model) {
    BS_VALIDATE(batch != NULL, (bs_Range) { 0 },);
    BS_VALIDATE(batch->head.type == BS_OBJECT_BATCH, (bs_Range) { 0 },);
    BS_VALIDATE(model != NULL, (bs_Range) { 0 },);
    return next.bs_pushModel(batch, model);
}

BSAPI bs_Result _preval_bs_renderer(bs_Object* object, bs_RendererBits flags) {
    BS_VALIDATE(object != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_renderer(object, flags);
}

BSAPI void _preval_bs_output(bs_Renderer* renderer, bs_Output output) {
    BS_VALIDATE(renderer != NULL, ,);
    BS_VALIDATE(renderer->head.type == BS_OBJECT_RENDERER, ,);
    next.bs_output(renderer, output);
}

BSAPI void _preval_bs_input(bs_Renderer* renderer, bs_Input input) {
    BS_VALIDATE(renderer != NULL, ,);
    BS_VALIDATE(renderer->head.type == BS_OBJECT_RENDERER, ,);
    next.bs_input(renderer, input);
}

BSAPI void _preval_bs_dependency(bs_Renderer* renderer, bs_U32 src_subpass, bs_U32 dst_subpass, bs_DependencyFlags flags, bs_PipelineStage src_stage, bs_PipelineStage dst_stage, bs_AccessMask src_access, bs_AccessMask dst_access) {
    BS_VALIDATE(renderer != NULL, ,);
    BS_VALIDATE(renderer->head.type == BS_OBJECT_RENDERER, ,);
    next.bs_dependency(renderer, src_subpass, dst_subpass, flags, src_stage, dst_stage, src_access, dst_access);
}

BSAPI bs_Result _preval_bs_renderPass(bs_Renderer* renderer) {
    BS_VALIDATE(renderer != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(renderer->head.type == BS_OBJECT_RENDERER, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_renderPass(renderer);
}

BSAPI bs_Result _preval_bs_framebuffer(bs_Renderer* renderer, bs_ivec2 resolution) {
    BS_VALIDATE(renderer != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(renderer->head.type == BS_OBJECT_RENDERER, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_framebuffer(renderer, resolution);
}

BSAPI void _preval_bs_runPass(bs_Queue* queue, bs_Renderer* renderer, bs_SubpassCallbackFunction callbacks[], int callbacks_count) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(renderer != NULL, ,);
    BS_VALIDATE(renderer->head.type == BS_OBJECT_RENDERER, ,);
    next.bs_runPass(queue, renderer, callbacks, callbacks_count);
}

BSAPI bool _preval_bs_rendererIsDynamic(bs_Renderer* renderer) {
    BS_VALIDATE(renderer != NULL, false,);
    BS_VALIDATE(renderer->head.type == BS_OBJECT_RENDERER, false,);
    return next.bs_rendererIsDynamic(renderer);
}

BSAPI bs_RendererScope _preval_bs_beginRender(bs_Queue* queue, bs_Renderer* renderer) {
    BS_VALIDATE(queue != NULL, (bs_RendererScope) { 0 },);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, (bs_RendererScope) { 0 },);
    BS_VALIDATE(renderer != NULL, (bs_RendererScope) { 0 },);
    BS_VALIDATE(renderer->head.type == BS_OBJECT_RENDERER, (bs_RendererScope) { 0 },);
    return next.bs_beginRender(queue, renderer);
}

BSAPI void _preval_bs_endRender(bs_Queue* queue, bs_Renderer* renderer) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(renderer != NULL, ,);
    BS_VALIDATE(renderer->head.type == BS_OBJECT_RENDERER, ,);
    next.bs_endRender(queue, renderer);
}

BSAPI void _preval_bs_destroyRenderer(bs_Renderer* renderer) {
    BS_VALIDATE(renderer != NULL, ,);
    BS_VALIDATE(renderer->head.type == BS_OBJECT_RENDERER, ,);
    next.bs_destroyRenderer(renderer);
}

BSAPI void _preval_bs_resizeRenderer(bs_Renderer* renderer, bs_ivec2 resolution) {
    BS_VALIDATE(renderer != NULL, ,);
    BS_VALIDATE(renderer->head.type == BS_OBJECT_RENDERER, ,);
    next.bs_resizeRenderer(renderer, resolution);
}

BSAPI bs_I32 _preval_bs_queueFamily(bs_QueueBits flags) {
    return next.bs_queueFamily(flags);
}

BSAPI void _preval_bs_present(bs_Queue* queue, bs_Queue* wait_queues[], int wait_queues_count) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(wait_queues != NULL, ,);
    next.bs_present(queue, wait_queues, wait_queues_count);
}

BSAPI void _preval_bs_acquire() {
    next.bs_acquire();
}

BSAPI int _preval_bs_queueSwap(bs_Queue* queue) {
    BS_VALIDATE(queue != NULL, 0,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, 0,);
    return next.bs_queueSwap(queue);
}

BSAPI void _preval_bs_enqueue(bs_Queue* queue, bs_Callback function) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    next.bs_enqueue(queue, function);
}

BSAPI int _preval_bs_imageIndex() {
    return next.bs_imageIndex();
}

BSAPI bs_Result _preval_bs_queue(bs_Object* object, bs_U32 queue_index, bs_QueueBits flags) {
    BS_VALIDATE(object != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_queue(object, queue_index, flags);
}

BSAPI void _preval_bs_destroyQueue(bs_Queue* queue) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    next.bs_destroyQueue(queue);
}

BSAPI void _preval_bs_stallGPU() {
    next.bs_stallGPU();
}

BSAPI void _preval_bs_stallQueue(bs_Queue* queue) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    next.bs_stallQueue(queue);
}

BSAPI bs_Result _preval_bs_stall(bs_Queue* queue) {
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_stall(queue);
}

BSAPI bs_Result _preval_bs_poll(bs_Queue* queue) {
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_poll(queue);
}

BSAPI bs_Result _preval_bs_image(bs_Object* object, bs_ivec2 dim, int num_indices, bs_Format format, bs_U32 flags) {
    BS_VALIDATE(object != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_image(object, dim, num_indices, format, flags);
}

BSAPI void _preval_bs_transition(bs_Queue* queue, bs_Image* image, int index, bs_ImageLayout old_layout, bs_ImageLayout new_layout) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(image != NULL, ,);
    BS_VALIDATE(image->head.type == BS_OBJECT_IMAGE, ,);
    next.bs_transition(queue, image, index, old_layout, new_layout);
}

BSAPI bs_Result _preval_bs_peekPng(bs_PngData* out_png_data, char* path) {
    BS_VALIDATE(out_png_data != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_peekPng(out_png_data, path);
}

BSAPI bs_Result _preval_bs_peekPngN(bs_PngData* out_png_data, char* path, int path_length) {
    BS_VALIDATE(out_png_data != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_peekPngN(out_png_data, path, path_length);
}

BSAPI bs_Result _preval_bs_peekPngV(bs_PngData* out_png_data, char* format, va_list args) {
    BS_VALIDATE(out_png_data != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_peekPngV(out_png_data, format, args);
}

BSAPI bs_Result _preval_bs_loadPngData(char* data, size_t size, int channels_count, bs_PngData* out_png_data) {
    BS_VALIDATE(data != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out_png_data != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadPngData(data, size, channels_count, out_png_data);
}

BSAPI bs_Result _preval_bs_loadPng(const char* path, int channels_count, bs_PngData* out_png_data) {
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out_png_data != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadPng(path, channels_count, out_png_data);
}

BSAPI bs_Result _preval_bs_peekFile(bs_FileInfo* out, char* path, int path_length) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_peekFile(out, path, path_length);
}

BSAPI bs_Result _preval_bs_savePng(char* data, bs_ivec2 resolution, bs_PngType type, char* path) {
    BS_VALIDATE(data != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_savePng(data, resolution, type, path);
}

BSAPI bs_Result _preval_bs_savePngN(char* data, bs_ivec2 resolution, bs_PngType type, char* path, int path_length) {
    BS_VALIDATE(data != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_savePngN(data, resolution, type, path, path_length);
}

BSAPI bs_Result _preval_bs_savePngV(char* data, bs_ivec2 resolution, bs_PngType type, char* format, va_list args) {
    BS_VALIDATE(data != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_savePngV(data, resolution, type, format, args);
}

BSAPI bs_Result _preval_bs_encodePng(size_t* out_size, const unsigned char* data, bs_ivec2 size, bs_PngType type, unsigned char** out) {
    BS_VALIDATE(out_size != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(data != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_encodePng(out_size, data, size, type, out);
}

BSAPI void _preval_bs_destroyImage(bs_Image* image) {
    BS_VALIDATE(image != NULL, ,);
    BS_VALIDATE(image->head.type == BS_OBJECT_IMAGE, ,);
    next.bs_destroyImage(image);
}

BSAPI bs_Result _preval_bs_resizeImage(bs_Image* image, bs_ivec2 size, int indices_count) {
    BS_VALIDATE(image != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(image->head.type == BS_OBJECT_IMAGE, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_resizeImage(image, size, indices_count);
}

BSAPI bs_Result _preval_bs_queryImageIndexHash(bs_Image* image, bs_U64 name_hash, int* out) {
    BS_VALIDATE(image != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(image->head.type == BS_OBJECT_IMAGE, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_queryImageIndexHash(image, name_hash, out);
}

BSAPI bs_Result _preval_bs_queryImageIndex(bs_Image* image, char* name, int* out) {
    BS_VALIDATE(image != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(image->head.type == BS_OBJECT_IMAGE, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(name != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_queryImageIndex(image, name, out);
}

BSAPI void _preval_bs_copyImageToBufferAsync(bs_Queue* queue, bs_Image* image, bs_Buffer* buffer, int image_index, bs_ImageLayout layout, bs_U64 buffer_offset, bs_ivec2 offset, bs_ivec2 resolution) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(image != NULL, ,);
    BS_VALIDATE(image->head.type == BS_OBJECT_IMAGE, ,);
    BS_VALIDATE(buffer != NULL, ,);
    BS_VALIDATE(buffer->head.type == BS_OBJECT_BUFFER, ,);
    next.bs_copyImageToBufferAsync(queue, image, buffer, image_index, layout, buffer_offset, offset, resolution);
}

BSAPI void _preval_bs_copyBufferToImage(bs_Queue* queue, bs_Buffer* buffer, bs_Image* image, int index, bs_ImageLayout layout) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(buffer != NULL, ,);
    BS_VALIDATE(buffer->head.type == BS_OBJECT_BUFFER, ,);
    BS_VALIDATE(image != NULL, ,);
    BS_VALIDATE(image->head.type == BS_OBJECT_IMAGE, ,);
    next.bs_copyBufferToImage(queue, buffer, image, index, layout);
}

BSAPI void _preval_bs_blit(bs_Queue* queue, bs_BlitOperation operation) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    next.bs_blit(queue, operation);
}

BSAPI bs_Result _preval_bs_loadImage(bs_Queue* queue, bs_Object* object, int package_id, bs_ImageBits flags, char* path) {
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(object != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadImage(queue, object, package_id, flags, path);
}

BSAPI bs_Result _preval_bs_loadImageN(bs_Queue* queue, bs_Object* object, int package_id, bs_ImageBits flags, char* path, int path_length) {
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(object != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadImageN(queue, object, package_id, flags, path, path_length);
}

BSAPI bs_Result _preval_bs_loadImageV(bs_Queue* queue, bs_Object* object, int package_id, bs_ImageBits flags, char* format, va_list args) {
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(object != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadImageV(queue, object, package_id, flags, format, args);
}

BSAPI bool _preval_bs_isStencilFormat(bs_Format format) {
    return next.bs_isStencilFormat(format);
}

BSAPI bool _preval_bs_isDepthFormat(bs_Format format) {
    return next.bs_isDepthFormat(format);
}

BSAPI bool _preval_bs_hasAlpha(bs_Format format) {
    return next.bs_hasAlpha(format);
}

BSAPI void _preval_bs_destroySampler(bs_Sampler* sampler) {
    BS_VALIDATE(sampler != NULL, ,);
    BS_VALIDATE(sampler->head.type == BS_OBJECT_SAMPLER, ,);
    next.bs_destroySampler(sampler);
}

BSAPI bs_Result _preval_bs_sampler(bs_Object* object, bs_ImageFilter filter, bs_SamplerBits flags) {
    BS_VALIDATE(object != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_sampler(object, filter, flags);
}

BSAPI bs_Result _preval_bs_loadAtlas(bs_Queue* queue, bs_Object* object, int package_id, bs_U32 flags, char* path) {
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(object != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadAtlas(queue, object, package_id, flags, path);
}

BSAPI bs_Result _preval_bs_loadAtlasN(bs_Queue* queue, bs_Object* object, int package_id, bs_U32 flags, char* path, int path_length) {
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(object != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadAtlasN(queue, object, package_id, flags, path, path_length);
}

BSAPI bs_Result _preval_bs_loadAtlasV(bs_Queue* queue, bs_Object* object, int package_id, bs_U32 flags, char* format, va_list args) {
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(object != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadAtlasV(queue, object, package_id, flags, format, args);
}

BSAPI bs_vec4 _preval_bs_atlasCoordinates(bs_Atlas* atlas, int texture_id) {
    BS_VALIDATE(atlas != NULL, (bs_vec4) { 0 },);
    BS_VALIDATE(atlas->head.type == BS_OBJECT_ATLAS, (bs_vec4) { 0 },);
    return next.bs_atlasCoordinates(atlas, texture_id);
}

BSAPI bs_vec4 _preval_bs_mirrorUV(bs_vec4 uv) {
    return next.bs_mirrorUV(uv);
}

BSAPI bs_vec4 _preval_bs_flipUV(bs_vec4 uv) {
    return next.bs_flipUV(uv);
}

BSAPI bs_vec2 _preval_bs_atlasSize(bs_Atlas* atlas, int texture) {
    BS_VALIDATE(atlas != NULL, (bs_vec2) { 0 },);
    BS_VALIDATE(atlas->head.type == BS_OBJECT_ATLAS, (bs_vec2) { 0 },);
    return next.bs_atlasSize(atlas, texture);
}

BSAPI int _preval_bs_queryAtlasHash(bs_Atlas* atlas, bs_U64 hash) {
    BS_VALIDATE(atlas != NULL, 0,);
    BS_VALIDATE(atlas->head.type == BS_OBJECT_ATLAS, 0,);
    return next.bs_queryAtlasHash(atlas, hash);
}

BSAPI int _preval_bs_queryAtlas(bs_Atlas* atlas, const char* name) {
    BS_VALIDATE(atlas != NULL, 0,);
    BS_VALIDATE(atlas->head.type == BS_OBJECT_ATLAS, 0,);
    BS_VALIDATE(name != NULL, 0,);
    return next.bs_queryAtlas(atlas, name);
}

BSAPI void _preval_bs_destroyAtlas(bs_Atlas* atlas) {
    BS_VALIDATE(atlas != NULL, ,);
    BS_VALIDATE(atlas->head.type == BS_OBJECT_ATLAS, ,);
    next.bs_destroyAtlas(atlas);
}

BSAPI bs_Result _preval_bs_loadAtlasMemory(bs_Queue* queue, bs_Object* object, int package_id, char* resource_name, char* data, bs_U32 flags) {
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(object != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(resource_name != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(data != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadAtlasMemory(queue, object, package_id, resource_name, data, flags);
}

BSAPI void _preval_bs_parseArgs(int argc, char* argv[]) {
    BS_VALIDATE(argv != NULL, ,);
    next.bs_parseArgs(argc, argv);
}

BSAPI void _preval_bs_ini() {
    next.bs_ini();
}

BSAPI void _preval_bs_queryProcedures(bs_Procedure* procedures, int count, void* dll_handle, unsigned char* destination) {
    BS_VALIDATE(procedures != NULL, ,);
    BS_VALIDATE(dll_handle != NULL, ,);
    BS_VALIDATE(destination != NULL, ,);
    next.bs_queryProcedures(procedures, count, dll_handle, destination);
}

BSAPI bs_WaitSemaphore _preval_bs_queueSemaphore(bs_Queue* queue, bs_PipelineStage stage) {
    BS_VALIDATE(queue != NULL, (bs_WaitSemaphore) { 0 },);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, (bs_WaitSemaphore) { 0 },);
    return next.bs_queueSemaphore(queue, stage);
}

BSAPI bs_WaitSemaphore _preval_bs_acquisitionSemaphore() {
    return next.bs_acquisitionSemaphore();
}

BSAPI bs_Result _preval_bs_resetQueue(bs_Queue* queue) {
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_resetQueue(queue);
}

BSAPI bs_Result _preval_bs_pushQueue(bs_Queue* queue, int wait_semaphores_count, bs_WaitSemaphore wait_semaphores[]) {
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_pushQueue(queue, wait_semaphores_count, wait_semaphores);
}

BSAPI void _preval_bsi_nameHandle(bs_U64 handle, bs_U32 type, char* value) {
    BS_VALIDATE(value != NULL, ,);
    next.bsi_nameHandle(handle, type, value);
}

BSAPI void _preval_bsi_nameHandleN(bs_U64 handle, bs_U32 type, char* value, int value_length) {
    BS_VALIDATE(value != NULL, ,);
    next.bsi_nameHandleN(handle, type, value, value_length);
}

BSAPI void _preval_bsi_nameHandleV(bs_U64 handle, bs_U32 type, char* format, va_list args) {
    BS_VALIDATE(format != NULL, ,);
    next.bsi_nameHandleV(handle, type, format, args);
}

BSAPI bs_JsonEnumeration _preval_bs_beginEnumeration(bs_Json* json) {
    BS_VALIDATE(json != NULL, (bs_JsonEnumeration) { 0 },);
    return next.bs_beginEnumeration(json);
}

BSAPI void _preval_bs_enumerateJson(bs_Json* json, bs_JsonEnumeration* e) {
    BS_VALIDATE(json != NULL, ,);
    BS_VALIDATE(e != NULL, ,);
    next.bs_enumerateJson(json, e);
}

BSAPI bs_Json _preval_bs_jsonRoot(bs_Json* json, bs_JsonObject object) {
    BS_VALIDATE(json != NULL, (bs_Json) { 0 },);
    return next.bs_jsonRoot(json, object);
}

BSAPI void _preval_bs_ensureJsonMutable(bs_Json* root) {
    BS_VALIDATE(root != NULL, ,);
    next.bs_ensureJsonMutable(root);
}

BSAPI bs_Json _preval_bs_jsonCopy(const bs_Json* root) {
    BS_VALIDATE(root != NULL, (bs_Json) { 0 },);
    return next.bs_jsonCopy(root);
}

BSAPI bs_Result _preval_bs_saveJson(bs_Json* json, bs_SaveJsonBits flags, char** out) {
    BS_VALIDATE(json != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_saveJson(json, flags, out);
}

BSAPI bs_Json _preval_bs_emptyJson() {
    return next.bs_emptyJson();
}

BSAPI bs_Json _preval_bs_emptyJsonArray() {
    return next.bs_emptyJsonArray();
}

BSAPI bs_Result _preval_bs_json(char* raw, int len, bs_Json* out) {
    BS_VALIDATE(raw != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_json(raw, len, out);
}

BSAPI bs_Result _preval_bs_loadJson(bs_Json* out, char* path) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadJson(out, path);
}

BSAPI bs_Result _preval_bs_loadJsonN(bs_Json* out, char* path, int path_length) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadJsonN(out, path, path_length);
}

BSAPI bs_Result _preval_bs_loadJsonV(bs_Json* out, char* format, va_list args) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadJsonV(out, format, args);
}

BSAPI void _preval_bs_destroyJson(bs_Json* json) {
    BS_VALIDATE(json != NULL, ,);
    next.bs_destroyJson(json);
}

BSAPI bs_JsonValue _preval_bs_parseJsonValue(char* raw) {
    BS_VALIDATE(raw != NULL, (bs_JsonValue) { 0 },);
    return next.bs_parseJsonValue(raw);
}

BSAPI bs_JsonValue _preval_bs_fetchJson(bs_Json* root, bs_JsonType expect, char* path) {
    BS_VALIDATE(root != NULL, (bs_JsonValue) { 0 },);
    BS_VALIDATE(path != NULL, (bs_JsonValue) { 0 },);
    return next.bs_fetchJson(root, expect, path);
}

BSAPI bs_JsonValue _preval_bs_fetchJsonN(bs_Json* root, bs_JsonType expect, char* path, int path_length) {
    BS_VALIDATE(root != NULL, (bs_JsonValue) { 0 },);
    BS_VALIDATE(path != NULL, (bs_JsonValue) { 0 },);
    return next.bs_fetchJsonN(root, expect, path, path_length);
}

BSAPI bs_JsonValue _preval_bs_fetchJsonV(bs_Json* root, bs_JsonType expect, char* format, va_list args) {
    BS_VALIDATE(root != NULL, (bs_JsonValue) { 0 },);
    BS_VALIDATE(format != NULL, (bs_JsonValue) { 0 },);
    return next.bs_fetchJsonV(root, expect, format, args);
}

BSAPI void _preval_bs_deleteJson(bs_Json* root, char* path) {
    BS_VALIDATE(root != NULL, ,);
    BS_VALIDATE(path != NULL, ,);
    next.bs_deleteJson(root, path);
}

BSAPI void _preval_bs_deleteJsonN(bs_Json* root, char* path, int path_length) {
    BS_VALIDATE(root != NULL, ,);
    BS_VALIDATE(path != NULL, ,);
    next.bs_deleteJsonN(root, path, path_length);
}

BSAPI void _preval_bs_deleteJsonV(bs_Json* root, char* format, va_list args) {
    BS_VALIDATE(root != NULL, ,);
    BS_VALIDATE(format != NULL, ,);
    next.bs_deleteJsonV(root, format, args);
}

BSAPI bs_Result _preval_bs_ensureJson(bs_Json* root, bs_JsonValue value, char* path) {
    BS_VALIDATE(root != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_ensureJson(root, value, path);
}

BSAPI bs_Result _preval_bs_ensureJsonN(bs_Json* root, bs_JsonValue value, char* path, int path_length) {
    BS_VALIDATE(root != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_ensureJsonN(root, value, path, path_length);
}

BSAPI bs_Result _preval_bs_ensureJsonV(bs_Json* root, bs_JsonValue value, char* format, va_list args) {
    BS_VALIDATE(root != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_ensureJsonV(root, value, format, args);
}

BSAPI bs_JsonValue _preval_bs_jsonValueFromObject(bs_JsonObject x) {
    return next.bs_jsonValueFromObject(x);
}

BSAPI bs_JsonValue _preval_bs_jsonValueFromRoot(bs_Json x) {
    return next.bs_jsonValueFromRoot(x);
}

BSAPI bs_JsonValue _preval_bs_jsonValueFromBool(bool x) {
    return next.bs_jsonValueFromBool(x);
}

BSAPI bs_JsonValue _preval_bs_jsonValueFromInteger(int x) {
    return next.bs_jsonValueFromInteger(x);
}

BSAPI bs_JsonValue _preval_bs_jsonValueFromFloat(double x) {
    return next.bs_jsonValueFromFloat(x);
}

BSAPI bs_JsonValue _preval_bs_jsonValueFromString(char* x) {
    BS_VALIDATE(x != NULL, (bs_JsonValue) { 0 },);
    return next.bs_jsonValueFromString(x);
}

BSAPI bs_JsonValue _preval_bs_jsonValueFromStringPointer(char* x) {
    BS_VALIDATE(x != NULL, (bs_JsonValue) { 0 },);
    return next.bs_jsonValueFromStringPointer(x);
}

BSAPI bs_JsonValue _preval_bs_jsonValueFromDateTime(bs_DateTime x) {
    return next.bs_jsonValueFromDateTime(x);
}

BSAPI bs_JsonValue _preval_bs_jsonObject(bs_Json* json) {
    BS_VALIDATE(json != NULL, (bs_JsonValue) { 0 },);
    return next.bs_jsonObject(json);
}

BSAPI bs_JsonValue _preval_bs_jsonArray(bs_JsonType type, char* data, int count) {
    BS_VALIDATE(data != NULL, (bs_JsonValue) { 0 },);
    return next.bs_jsonArray(type, data, count);
}

BSAPI bs_JsonValue _preval_bs_jsonVec2(bs_vec2* vector) {
    BS_VALIDATE(vector != NULL, (bs_JsonValue) { 0 },);
    return next.bs_jsonVec2(vector);
}

BSAPI bs_JsonValue _preval_bs_jsonVec3(bs_vec3* vector) {
    BS_VALIDATE(vector != NULL, (bs_JsonValue) { 0 },);
    return next.bs_jsonVec3(vector);
}

BSAPI bs_JsonValue _preval_bs_jsonVec4(bs_vec4* vector) {
    BS_VALIDATE(vector != NULL, (bs_JsonValue) { 0 },);
    return next.bs_jsonVec4(vector);
}

BSAPI bs_JsonValue _preval_bs_jsonRGBA(bs_RGBA color) {
    return next.bs_jsonRGBA(color);
}

BSAPI void _preval_bs_logSection(char* value) {
    BS_VALIDATE(value != NULL, ,);
    next.bs_logSection(value);
}

BSAPI void _preval_bs_logSectionN(char* value, int value_length) {
    BS_VALIDATE(value != NULL, ,);
    next.bs_logSectionN(value, value_length);
}

BSAPI void _preval_bs_logSectionV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, ,);
    next.bs_logSectionV(format, args);
}

BSAPI void _preval_bs_logEndOfSection() {
    next.bs_logEndOfSection();
}

BSAPI void _preval_bs_logWithTimestamp(bs_MessageLevel level, char* value) {
    BS_VALIDATE(value != NULL, ,);
    next.bs_logWithTimestamp(level, value);
}

BSAPI void _preval_bs_logWithTimestampN(bs_MessageLevel level, char* value, int value_length) {
    BS_VALIDATE(value != NULL, ,);
    next.bs_logWithTimestampN(level, value, value_length);
}

BSAPI void _preval_bs_logWithTimestampV(bs_MessageLevel level, char* format, va_list args) {
    BS_VALIDATE(format != NULL, ,);
    next.bs_logWithTimestampV(level, format, args);
}

BSAPI void _preval_bs_log(char* message) {
    BS_VALIDATE(message != NULL, ,);
    next.bs_log(message);
}

BSAPI void _preval_bs_logN(char* message, int message_length) {
    BS_VALIDATE(message != NULL, ,);
    next.bs_logN(message, message_length);
}

BSAPI void _preval_bs_logV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, ,);
    next.bs_logV(format, args);
}

BSAPI void _preval_bs_info(char* message) {
    BS_VALIDATE(message != NULL, ,);
    next.bs_info(message);
}

BSAPI void _preval_bs_infoN(char* message, int message_length) {
    BS_VALIDATE(message != NULL, ,);
    next.bs_infoN(message, message_length);
}

BSAPI void _preval_bs_infoV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, ,);
    next.bs_infoV(format, args);
}

BSAPI void _preval_bs_warn(char* message) {
    BS_VALIDATE(message != NULL, ,);
    next.bs_warn(message);
}

BSAPI void _preval_bs_warnN(char* message, int message_length) {
    BS_VALIDATE(message != NULL, ,);
    next.bs_warnN(message, message_length);
}

BSAPI void _preval_bs_warnV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, ,);
    next.bs_warnV(format, args);
}

BSAPI void _preval_bs_critical(char* message) {
    BS_VALIDATE(message != NULL, ,);
    next.bs_critical(message);
}

BSAPI void _preval_bs_criticalN(char* message, int message_length) {
    BS_VALIDATE(message != NULL, ,);
    next.bs_criticalN(message, message_length);
}

BSAPI void _preval_bs_criticalV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, ,);
    next.bs_criticalV(format, args);
}

BSAPI bs_Instance* _preval_bs_instance() {
    return next.bs_instance();
}

BSAPI bs_Args* _preval_bs_args() {
    return next.bs_args();
}

BSAPI bs_Features* _preval_bs_features() {
    return next.bs_features();
}

BSAPI bs_Props* _preval_bs_props() {
    return next.bs_props();
}

BSAPI bs_Config* _preval_bs_config() {
    return next.bs_config();
}

BSAPI void _preval_bs_system(char* value) {
    BS_VALIDATE(value != NULL, ,);
    next.bs_system(value);
}

BSAPI void _preval_bs_systemN(char* value, int value_length) {
    BS_VALIDATE(value != NULL, ,);
    next.bs_systemN(value, value_length);
}

BSAPI void _preval_bs_systemV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, ,);
    next.bs_systemV(format, args);
}

BSAPI void _preval_bs_createThread(bs_ThreadFunction function, void* param) {
    BS_VALIDATE(param != NULL, ,);
    next.bs_createThread(function, param);
}

BSAPI int _preval_bs_formatStringLength(const char* format, va_list args) {
    BS_VALIDATE(format != NULL, 0,);
    return next.bs_formatStringLength(format, args);
}

BSAPI const char* _preval_bs_checkStringPool(bs_List* pool, char* string) {
    BS_VALIDATE(pool != NULL, NULL,);
    BS_VALIDATE(pool->unit_size > 0, NULL,);
    BS_VALIDATE(string != NULL, NULL,);
    return next.bs_checkStringPool(pool, string);
}

BSAPI bs_String* _preval_bs_stringAlloc(bs_String* old, int len) {
    BS_VALIDATE(old != NULL, NULL,);
    return next.bs_stringAlloc(old, len);
}

BSAPI bs_String* _preval_bs_emptyString(bs_String* old) {
    BS_VALIDATE(old != NULL, NULL,);
    return next.bs_emptyString(old);
}

BSAPI bs_String* _preval_bs_string(bs_String* old, char* value) {
    BS_VALIDATE(value != NULL, NULL,);
    return next.bs_string(old, value);
}

BSAPI bs_String* _preval_bs_stringN(bs_String* old, char* value, int value_length) {
    BS_VALIDATE(value != NULL, NULL,);
    return next.bs_stringN(old, value, value_length);
}

BSAPI bs_String* _preval_bs_stringV(bs_String* old, char* format, va_list args) {
    BS_VALIDATE(format != NULL, NULL,);
    return next.bs_stringV(old, format, args);
}

BSAPI void _preval_bs_toUpper(char* string, int len) {
    BS_VALIDATE(string != NULL, ,);
    next.bs_toUpper(string, len);
}

BSAPI void _preval_bs_toLower(char* string, int len) {
    BS_VALIDATE(string != NULL, ,);
    next.bs_toLower(string, len);
}

BSAPI bs_U64 _preval_bs_hash(unsigned char* data, size_t size) {
    BS_VALIDATE(data != NULL, 0,);
    return next.bs_hash(data, size);
}

BSAPI bs_U64 _preval_bs_stringHash(char* string) {
    BS_VALIDATE(string != NULL, 0,);
    return next.bs_stringHash(string);
}

BSAPI bool _preval_bs_startsWith(char* string, const char* prefix) {
    BS_VALIDATE(string != NULL, false,);
    BS_VALIDATE(prefix != NULL, false,);
    return next.bs_startsWith(string, prefix);
}

BSAPI bool _preval_bs_endsWith(char* string, const char* suffix) {
    BS_VALIDATE(string != NULL, false,);
    BS_VALIDATE(suffix != NULL, false,);
    return next.bs_endsWith(string, suffix);
}

BSAPI char _preval_bs_lastChar(char* string, int len) {
    BS_VALIDATE(string != NULL, 0,);
    return next.bs_lastChar(string, len);
}

BSAPI bool _preval_bs_stringContainsChar(char* string, char c) {
    BS_VALIDATE(string != NULL, false,);
    return next.bs_stringContainsChar(string, c);
}

BSAPI bs_String* _preval_bs_workingDirectory() {
    return next.bs_workingDirectory();
}

BSAPI bs_Result _preval_bs_setWorkingDirectory(char* path) {
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_setWorkingDirectory(path);
}

BSAPI bs_Result _preval_bs_setWorkingDirectoryN(char* path, int path_length) {
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_setWorkingDirectoryN(path, path_length);
}

BSAPI bs_Result _preval_bs_setWorkingDirectoryV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_setWorkingDirectoryV(format, args);
}

BSAPI bs_String* _preval_bs_executablePath() {
    return next.bs_executablePath();
}

BSAPI char* _preval_bs_appdataPath() {
    return next.bs_appdataPath();
}

BSAPI void _preval_bs_shortenString(bs_String* string, int len) {
    BS_VALIDATE(string != NULL, ,);
    next.bs_shortenString(string, len);
}

BSAPI bs_String* _preval_bs_appendChar(bs_String* string, char c) {
    BS_VALIDATE(string != NULL, NULL,);
    return next.bs_appendChar(string, c);
}

BSAPI void _preval_bs_removeCharRange(bs_String* string, int start, int count) {
    BS_VALIDATE(string != NULL, ,);
    next.bs_removeCharRange(string, start, count);
}

BSAPI bs_String* _preval_bs_insertChar(bs_String* string, int index, char c) {
    BS_VALIDATE(string != NULL, NULL,);
    return next.bs_insertChar(string, index, c);
}

BSAPI bs_String* _preval_bs_appendPath(bs_String* string, char* path, int path_len) {
    BS_VALIDATE(string != NULL, NULL,);
    BS_VALIDATE(path != NULL, NULL,);
    return next.bs_appendPath(string, path, path_len);
}

BSAPI void _preval_bs_replaceCharOccurrences(char* string, int string_len, char a, char b) {
    BS_VALIDATE(string != NULL, ,);
    next.bs_replaceCharOccurrences(string, string_len, a, b);
}

BSAPI char* _preval_bs_strndup(const char* s, size_t n) {
    BS_VALIDATE(s != NULL, NULL,);
    return next.bs_strndup(s, n);
}

BSAPI size_t _preval_bs_strnlen(const char* src, size_t n) {
    BS_VALIDATE(src != NULL, 0,);
    return next.bs_strnlen(src, n);
}

BSAPI char* _preval_bs_strsep(char** stringp, const char* delim) {
    BS_VALIDATE(stringp != NULL, NULL,);
    BS_VALIDATE(delim != NULL, NULL,);
    return next.bs_strsep(stringp, delim);
}

BSAPI void* _preval_bs_memmem(const void* haystack, bs_U32 haystack_len, const void* const needle, const bs_U32 needle_len) {
    BS_VALIDATE(haystack != NULL, NULL,);
    BS_VALIDATE(needle != NULL, NULL,);
    return next.bs_memmem(haystack, haystack_len, needle, needle_len);
}

BSAPI bs_U32 _preval_bs_alignUp(bs_U32 value, bs_U32 alignment) {
    return next.bs_alignUp(value, alignment);
}

BSAPI bs_Result _preval_bs_widen(char* src, wchar_t* dst, bs_U32 dst_size) {
    BS_VALIDATE(src != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(dst != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_widen(src, dst, dst_size);
}

BSAPI bs_Result _preval_bs_unwiden(wchar_t* src, char* dst, bs_U32 dst_size) {
    BS_VALIDATE(src != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(dst != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_unwiden(src, dst, dst_size);
}

BSAPI char* _preval_bs_charStringV(const char* format, va_list args) {
    BS_VALIDATE(format != NULL, NULL,);
    return next.bs_charStringV(format, args);
}

BSAPI void* _preval_bs_free(void* p) {
    BS_VALIDATE(p != NULL, NULL,);
    return next.bs_free(p);
}

BSAPI void* _preval_bs_malloc(bs_U64 size) {
    return next.bs_malloc(size);
}

BSAPI void* _preval_bs_calloc(bs_U64 num_units, bs_U64 unit_size) {
    return next.bs_calloc(num_units, unit_size);
}

BSAPI void* _preval_bs_realloc(void* p, bs_U64 size) {
    BS_VALIDATE(p != NULL, NULL,);
    return next.bs_realloc(p, size);
}

BSAPI bool _preval_bs_listContains(bs_List* list, void* data) {
    BS_VALIDATE(list != NULL, false,);
    BS_VALIDATE(list->unit_size > 0, false,);
    BS_VALIDATE(data != NULL, false,);
    return next.bs_listContains(list, data);
}

BSAPI void* _preval_bs_fetchUnit(bs_List* list, bs_U32 index) {
    BS_VALIDATE(list != NULL, NULL,);
    BS_VALIDATE(list->unit_size > 0, NULL,);
    return next.bs_fetchUnit(list, index);
}

BSAPI void* _preval_bs_fetchLast(bs_List* list) {
    BS_VALIDATE(list != NULL, NULL,);
    BS_VALIDATE(list->unit_size > 0, NULL,);
    return next.bs_fetchLast(list);
}

BSAPI void _preval_bs_ensureSize(bs_List* list, bs_U32 num_units) {
    BS_VALIDATE(list != NULL, ,);
    BS_VALIDATE(list->unit_size > 0, ,);
    next.bs_ensureSize(list, num_units);
}

BSAPI void _preval_bs_erase(bs_List* list, int index, bs_U32 count) {
    BS_VALIDATE(list != NULL, ,);
    BS_VALIDATE(list->unit_size > 0, ,);
    next.bs_erase(list, index, count);
}

BSAPI void* _preval_bs_pushBack(bs_List* list, void* data) {
    BS_VALIDATE(list != NULL, NULL,);
    BS_VALIDATE(list->unit_size > 0, NULL,);
    BS_VALIDATE(data != NULL, NULL,);
    return next.bs_pushBack(list, data);
}

BSAPI void* _preval_bs_pushBackList(bs_List* source, bs_List* destination) {
    BS_VALIDATE(source != NULL, NULL,);
    BS_VALIDATE(source->unit_size > 0, NULL,);
    BS_VALIDATE(destination != NULL, NULL,);
    BS_VALIDATE(destination->unit_size > 0, NULL,);
    return next.bs_pushBackList(source, destination);
}

BSAPI void _preval_bs_destroyList(bs_List* list) {
    BS_VALIDATE(list != NULL, ,);
    BS_VALIDATE(list->unit_size > 0, ,);
    next.bs_destroyList(list);
}

BSAPI void _preval_bs_seekList(bs_List* list, bs_U32 unit_index) {
    BS_VALIDATE(list != NULL, ,);
    BS_VALIDATE(list->unit_size > 0, ,);
    next.bs_seekList(list, unit_index);
}

BSAPI void _preval_bs_minimizeList(bs_List* list) {
    BS_VALIDATE(list != NULL, ,);
    BS_VALIDATE(list->unit_size > 0, ,);
    next.bs_minimizeList(list);
}

BSAPI bs_List _preval_bs_list(int unit_size, int increment) {
    return next.bs_list(unit_size, increment);
}

BSAPI void _preval_bs_guidToString(bs_GUID* guid, char out[37]) {
    BS_VALIDATE(guid != NULL, ,);
    next.bs_guidToString(guid, out);
}

BSAPI bs_GUID _preval_bs_stringToGuid(const char* str) {
    BS_VALIDATE(str != NULL, (bs_GUID) { 0 },);
    return next.bs_stringToGuid(str);
}

BSAPI bool _preval_bs_sameGuid(bs_GUID* a, bs_GUID* b) {
    BS_VALIDATE(a != NULL, false,);
    BS_VALIDATE(b != NULL, false,);
    return next.bs_sameGuid(a, b);
}

BSAPI bs_GUID _preval_bs_guid() {
    return next.bs_guid();
}

BSAPI bool _preval_bs_guidIsNull(bs_GUID* guid) {
    BS_VALIDATE(guid != NULL, false,);
    return next.bs_guidIsNull(guid);
}

BSAPI int _preval_bs_numDigits(int n) {
    return next.bs_numDigits(n);
}

BSAPI bool _preval_bs_directoryExists(char* path) {
    BS_VALIDATE(path != NULL, false,);
    return next.bs_directoryExists(path);
}

BSAPI bool _preval_bs_directoryExistsN(char* path, int path_length) {
    BS_VALIDATE(path != NULL, false,);
    return next.bs_directoryExistsN(path, path_length);
}

BSAPI bool _preval_bs_directoryExistsV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, false,);
    return next.bs_directoryExistsV(format, args);
}

BSAPI char* _preval_bs_fileExtension(const char* path) {
    BS_VALIDATE(path != NULL, NULL,);
    return next.bs_fileExtension(path);
}

BSAPI bool _preval_bs_fileExtensionIs(const char* path, char* extension) {
    BS_VALIDATE(path != NULL, false,);
    BS_VALIDATE(extension != NULL, false,);
    return next.bs_fileExtensionIs(path, extension);
}

BSAPI char* _preval_bs_fileName(const char* path) {
    BS_VALIDATE(path != NULL, NULL,);
    return next.bs_fileName(path);
}

BSAPI bs_Result _preval_bs_appendFile(char* data, bs_U32 data_len, char* value) {
    BS_VALIDATE(data != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(value != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_appendFile(data, data_len, value);
}

BSAPI bs_Result _preval_bs_appendFileN(char* data, bs_U32 data_len, char* value, int value_length) {
    BS_VALIDATE(data != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(value != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_appendFileN(data, data_len, value, value_length);
}

BSAPI bs_Result _preval_bs_appendFileV(char* data, bs_U32 data_len, char* format, va_list args) {
    BS_VALIDATE(data != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_appendFileV(data, data_len, format, args);
}

BSAPI bs_Result _preval_bs_saveFile(char* data, bs_U32 data_len, char* path) {
    BS_VALIDATE(data != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_saveFile(data, data_len, path);
}

BSAPI bs_Result _preval_bs_saveFileN(char* data, bs_U32 data_len, char* path, int path_length) {
    BS_VALIDATE(data != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_saveFileN(data, data_len, path, path_length);
}

BSAPI bs_Result _preval_bs_saveFileV(char* data, bs_U32 data_len, char* format, va_list args) {
    BS_VALIDATE(data != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_saveFileV(data, data_len, format, args);
}

BSAPI void _preval_bs_convertWin32Path(char* path) {
    BS_VALIDATE(path != NULL, ,);
    next.bs_convertWin32Path(path);
}

BSAPI void _preval_bs_convertWin32PathN(char* path, int path_length) {
    BS_VALIDATE(path != NULL, ,);
    next.bs_convertWin32PathN(path, path_length);
}

BSAPI void _preval_bs_convertWin32PathV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, ,);
    next.bs_convertWin32PathV(format, args);
}

BSAPI bs_Result _preval_bs_ensureDirectory(char* path) {
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_ensureDirectory(path);
}

BSAPI bs_Result _preval_bs_ensureDirectoryN(char* path, int path_length) {
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_ensureDirectoryN(path, path_length);
}

BSAPI bs_Result _preval_bs_ensureDirectoryV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_ensureDirectoryV(format, args);
}

BSAPI bs_Result _preval_bs_fileModifiedDate(bs_DateTime* out, char* path) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_fileModifiedDate(out, path);
}

BSAPI bs_Result _preval_bs_fileModifiedDateN(bs_DateTime* out, char* path, int path_length) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_fileModifiedDateN(out, path, path_length);
}

BSAPI bs_Result _preval_bs_fileModifiedDateV(bs_DateTime* out, char* format, va_list args) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_fileModifiedDateV(out, format, args);
}

BSAPI bs_Result _preval_bs_setFileModifiedDate(bs_DateTime* date, char* path) {
    BS_VALIDATE(date != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_setFileModifiedDate(date, path);
}

BSAPI bs_Result _preval_bs_setFileModifiedDateN(bs_DateTime* date, char* path, int path_length) {
    BS_VALIDATE(date != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_setFileModifiedDateN(date, path, path_length);
}

BSAPI bs_Result _preval_bs_setFileModifiedDateV(bs_DateTime* date, char* format, va_list args) {
    BS_VALIDATE(date != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_setFileModifiedDateV(date, format, args);
}

BSAPI bs_String* _preval_bs_fullPath(bs_String* old, const char* path, int path_len) {
    BS_VALIDATE(old != NULL, NULL,);
    BS_VALIDATE(path != NULL, NULL,);
    return next.bs_fullPath(old, path, path_len);
}

BSAPI bool _preval_bs_fileExists(char* path) {
    BS_VALIDATE(path != NULL, false,);
    return next.bs_fileExists(path);
}

BSAPI bool _preval_bs_fileExistsN(char* path, int path_length) {
    BS_VALIDATE(path != NULL, false,);
    return next.bs_fileExistsN(path, path_length);
}

BSAPI bool _preval_bs_fileExistsV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, false,);
    return next.bs_fileExistsV(format, args);
}

BSAPI bs_I64 _preval_bs_toLong(const char* str) {
    BS_VALIDATE(str != NULL, 0,);
    return next.bs_toLong(str);
}

BSAPI bs_U64 _preval_bs_toULong(const char* str) {
    BS_VALIDATE(str != NULL, 0,);
    return next.bs_toULong(str);
}

BSAPI bs_F64 _preval_bs_toDouble(const char* str) {
    BS_VALIDATE(str != NULL, 0,);
    return next.bs_toDouble(str);
}

BSAPI bs_Result _preval_bs_model(int package_id, const char* name, bs_U32 flags, bs_Resource** out) {
    BS_VALIDATE(name != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_model(package_id, name, flags, out);
}

BSAPI void _preval_bs_destroyModel(bs_Model* model) {
    BS_VALIDATE(model != NULL, ,);
    next.bs_destroyModel(model);
}

BSAPI bs_vec4 _preval_bs_interpolateRotation(bs_AnimationBone* animation_joint, float time) {
    BS_VALIDATE(animation_joint != NULL, (bs_vec4) { 0 },);
    return next.bs_interpolateRotation(animation_joint, time);
}

BSAPI bs_vec3 _preval_bs_interpolateTranslation(bs_AnimationBone* animation_joint, float time) {
    BS_VALIDATE(animation_joint != NULL, (bs_vec3) { 0 },);
    return next.bs_interpolateTranslation(animation_joint, time);
}

BSAPI bs_vec3 _preval_bs_interpolateScale(bs_AnimationBone* animation_joint, float time) {
    BS_VALIDATE(animation_joint != NULL, (bs_vec3) { 0 },);
    return next.bs_interpolateScale(animation_joint, time);
}

BSAPI bs_mat4 _preval_bs_boneTransform(bs_Armature* armature, bs_Bone* bone) {
    BS_VALIDATE(armature != NULL, (bs_mat4) { 0 },);
    BS_VALIDATE(bone != NULL, (bs_mat4) { 0 },);
    return next.bs_boneTransform(armature, bone);
}

BSAPI bs_vec3 _preval_bs_bonePosition(bs_Armature* armature, bs_Bone* bone) {
    BS_VALIDATE(armature != NULL, (bs_vec3) { 0 },);
    BS_VALIDATE(bone != NULL, (bs_vec3) { 0 },);
    return next.bs_bonePosition(armature, bone);
}

BSAPI bs_mat4* _preval_bs_transformBone(bs_Armature* armature, bs_Bone* bone, const bs_mat4* transform) {
    BS_VALIDATE(armature != NULL, NULL,);
    BS_VALIDATE(bone != NULL, NULL,);
    BS_VALIDATE(transform != NULL, NULL,);
    return next.bs_transformBone(armature, bone, transform);
}

BSAPI void _preval_bs_blendPose(bs_Armature* armature, bs_Animation* animation_a, bs_Animation* animation_b, float factor, float time_a, float time_b) {
    BS_VALIDATE(armature != NULL, ,);
    BS_VALIDATE(animation_a != NULL, ,);
    BS_VALIDATE(animation_b != NULL, ,);
    next.bs_blendPose(armature, animation_a, animation_b, factor, time_a, time_b);
}

BSAPI int _preval_bs_bone(bs_Armature* armature, bs_mat4 local_transform, int parent_id, const char* name) {
    BS_VALIDATE(armature != NULL, 0,);
    BS_VALIDATE(name != NULL, 0,);
    return next.bs_bone(armature, local_transform, parent_id, name);
}

BSAPI void _preval_bs_fabrik(bs_Armature* armature, int end_effector_id, bs_vec3 target, int chain_length, float* chain) {
    BS_VALIDATE(armature != NULL, ,);
    BS_VALIDATE(chain != NULL, ,);
    next.bs_fabrik(armature, end_effector_id, target, chain_length, chain);
}

BSAPI void _preval_bs_bindPose(bs_Armature* armature) {
    BS_VALIDATE(armature != NULL, ,);
    next.bs_bindPose(armature);
}

BSAPI void _preval_bs_keyframePosition(bs_AnimationBone* bone, float timestamp, bs_vec3 position) {
    BS_VALIDATE(bone != NULL, ,);
    next.bs_keyframePosition(bone, timestamp, position);
}

BSAPI void _preval_bs_keyframeRotation(bs_AnimationBone* bone, float timestamp, bs_vec4 rotation) {
    BS_VALIDATE(bone != NULL, ,);
    next.bs_keyframeRotation(bone, timestamp, rotation);
}

BSAPI void _preval_bs_keyframeScale(bs_AnimationBone* bone, float timestamp, bs_vec3 scale) {
    BS_VALIDATE(bone != NULL, ,);
    next.bs_keyframeScale(bone, timestamp, scale);
}

BSAPI bs_Result _preval_bs_loadAnimation(bs_Model* model, const char* name, bs_Animation* out) {
    BS_VALIDATE(model != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(name != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadAnimation(model, name, out);
}

BSAPI int _preval_bs_queryBoneId(bs_Armature* armature, const char* name) {
    BS_VALIDATE(armature != NULL, 0,);
    BS_VALIDATE(name != NULL, 0,);
    return next.bs_queryBoneId(armature, name);
}

BSAPI bs_Armature* _preval_bs_queryArmature(bs_Model* model, const char* name) {
    BS_VALIDATE(model != NULL, NULL,);
    BS_VALIDATE(name != NULL, NULL,);
    return next.bs_queryArmature(model, name);
}

BSAPI bs_Bone* _preval_bs_queryBone(bs_Armature* armature, const char* name) {
    BS_VALIDATE(armature != NULL, NULL,);
    BS_VALIDATE(name != NULL, NULL,);
    return next.bs_queryBone(armature, name);
}

BSAPI bs_Mesh* _preval_bs_queryMesh(bs_Model* model, const char * name) {
    BS_VALIDATE(model != NULL, NULL,);
    BS_VALIDATE(name != NULL, NULL,);
    return next.bs_queryMesh(model, name);
}

BSAPI bs_Mesh* _preval_bs_queryMeshHash(bs_Model* model, bs_U64 hash) {
    BS_VALIDATE(model != NULL, NULL,);
    return next.bs_queryMeshHash(model, hash);
}

BSAPI bs_Material* _preval_bs_queryMaterial(bs_Model* model, const char* name) {
    BS_VALIDATE(model != NULL, NULL,);
    BS_VALIDATE(name != NULL, NULL,);
    return next.bs_queryMaterial(model, name);
}

BSAPI const char* _preval_bs_idName(bs_U32 source_id, bs_U32 id) {
    return next.bs_idName(source_id, id);
}

BSAPI void _preval_bs_resetObject(bs_Header* head, size_t size) {
    BS_VALIDATE(head != NULL, ,);
    next.bs_resetObject(head, size);
}

BSAPI bs_Object* _preval_bs_object(bs_U32 source_id, bs_U32 id, size_t size, size_t flexible_size, int flexible_count, bs_U32 flags, bs_ObjectType object_type) {
    return next.bs_object(source_id, id, size, flexible_size, flexible_count, flags, object_type);
}

BSAPI bs_List* _preval_bs_packages() {
    return next.bs_packages();
}

BSAPI bs_List* _preval_bs_objectSources() {
    return next.bs_objectSources();
}

BSAPI void _preval_bs_destroyResource(bs_Resource* resource) {
    BS_VALIDATE(resource != NULL, ,);
    next.bs_destroyResource(resource);
}

BSAPI bs_Result _preval_bs_queryResource(int package_id, int resource_type, const char* name, bs_Resource** out) {
    BS_VALIDATE(name != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_queryResource(package_id, resource_type, name, out);
}

BSAPI int _preval_bs_queryPackage(const char* name) {
    BS_VALIDATE(name != NULL, 0,);
    return next.bs_queryPackage(name);
}

BSAPI bs_Result _preval_bs_loadResource(int package_id, bs_U32 flags, bs_ResourceType type, bs_Resource** out, char* value) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(value != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadResource(package_id, flags, type, out, value);
}

BSAPI bs_Result _preval_bs_loadResourceN(int package_id, bs_U32 flags, bs_ResourceType type, bs_Resource** out, char* value, int value_length) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(value != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadResourceN(package_id, flags, type, out, value, value_length);
}

BSAPI bs_Result _preval_bs_loadResourceV(int package_id, bs_U32 flags, bs_ResourceType type, bs_Resource** out, char* format, va_list args) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadResourceV(package_id, flags, type, out, format, args);
}

BSAPI bs_Result _preval_bs_loadPackage(int* out, char* path) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadPackage(out, path);
}

BSAPI bs_Result _preval_bs_loadPackageN(int* out, char* path, int path_length) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadPackageN(out, path, path_length);
}

BSAPI bs_Result _preval_bs_loadPackageV(int* out, char* format, va_list args) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadPackageV(out, format, args);
}

BSAPI int _preval_bs_configureSource(bs_ObjectType type, int count, const char** names) {
    BS_VALIDATE(names != NULL, 0,);
    return next.bs_configureSource(type, count, names);
}

BSAPI bool _preval_bs_exists(bs_U32 source_id, bs_U32 id) {
    return next.bs_exists(source_id, id);
}

BSAPI bs_Object* _preval_bs_fetch(bs_U32 source_id, bs_U32 id) {
    return next.bs_fetch(source_id, id);
}

BSAPI bool _preval_bs_shouldLoadId(bs_U32 source_id, bs_U32 id) {
    return next.bs_shouldLoadId(source_id, id);
}

BSAPI bs_Result _preval_bs_shader(int package_id, const char* name, bs_U32 flags, bs_Resource** out) {
    BS_VALIDATE(name != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_shader(package_id, name, flags, out);
}

BSAPI void _preval_bs_destroyShader(bs_Shader* shader) {
    BS_VALIDATE(shader != NULL, ,);
    next.bs_destroyShader(shader);
}

BSAPI bs_Result _preval_bs_computePipeline(bs_Shader* compute_shader, bs_PipelineFlags flags, bs_Pipeline** out) {
    BS_VALIDATE(compute_shader != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_computePipeline(compute_shader, flags, out);
}

BSAPI void _preval_bs_destroyComputePipeline(bs_Pipeline* pipeline) {
    BS_VALIDATE(pipeline != NULL, ,);
    next.bs_destroyComputePipeline(pipeline);
}

BSAPI bs_Pipeline* _preval_bs_queryPipeline(bs_PipelineType type, bs_U64 hash) {
    return next.bs_queryPipeline(type, hash);
}

BSAPI bs_U64 _preval_bs_pipelineHash(bs_PipelineHash* descriptor) {
    BS_VALIDATE(descriptor != NULL, 0,);
    return next.bs_pipelineHash(descriptor);
}

BSAPI bs_Result _preval_bs_pipeline(bs_RendererScope* scope, bs_Queue* queue, bs_PipelineHash* descriptor, bs_Pipeline** out) {
    BS_VALIDATE(scope != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(descriptor != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_pipeline(scope, queue, descriptor, out);
}

BSAPI void _preval_bs_destroyPipeline(bs_Pipeline* pipeline) {
    BS_VALIDATE(pipeline != NULL, ,);
    next.bs_destroyPipeline(pipeline);
}

BSAPI void _preval_bs_pushConstant(bs_Queue* queue, bs_Pipeline* pipeline, bs_U32 offset, bs_U32 size, void* data) {
    BS_VALIDATE(queue != NULL, ,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, ,);
    BS_VALIDATE(pipeline != NULL, ,);
    BS_VALIDATE(data != NULL, ,);
    next.bs_pushConstant(queue, pipeline, offset, size, data);
}

BSAPI bs_Result _preval_bs_rayTracingPipeline(bs_Queue* queue, bs_RayTracePipelineHash* pipeline_hash, bs_Pipeline** out) {
    BS_VALIDATE(queue != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(queue->head.type == BS_OBJECT_QUEUE, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(pipeline_hash != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_rayTracingPipeline(queue, pipeline_hash, out);
}

BSAPI void _preval_bs_loadBindings() {
    next.bs_loadBindings();
}

BSAPI bs_Result _preval_bs_binding(bs_BindSet* bind_set, bs_Binding* bind_point, bs_Descriptor* descriptors, int descriptors_count) {
    BS_VALIDATE(bind_set != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(bind_point != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(descriptors != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_binding(bind_set, bind_point, descriptors, descriptors_count);
}

BSAPI bs_Result _preval_bs_bindImage(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_Image* image, bs_Sampler* sampler, bs_ImageLayout layout) {
    BS_VALIDATE(image != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(image->head.type == BS_OBJECT_IMAGE, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(sampler != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(sampler->head.type == BS_OBJECT_SAMPLER, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_bindImage(bind_set_slot, bind_point_slot, image, sampler, layout);
}

BSAPI bs_Result _preval_bs_bindImages(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_ImageDescriptor* images, int images_count) {
    BS_VALIDATE(images != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_bindImages(bind_set_slot, bind_point_slot, images, images_count);
}

BSAPI bs_Result _preval_bs_bindBuffer(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_Buffer* buffer) {
    BS_VALIDATE(buffer != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(buffer->head.type == BS_OBJECT_BUFFER, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_bindBuffer(bind_set_slot, bind_point_slot, buffer);
}

BSAPI bs_Result _preval_bs_bindBuffers(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_Buffer** buffers, int buffers_count) {
    BS_VALIDATE(buffers != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_bindBuffers(bind_set_slot, bind_point_slot, buffers, buffers_count);
}

BSAPI bs_Result _preval_bs_bindAccelerationStructure(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_RayTracer* ray_tracer) {
    BS_VALIDATE(ray_tracer != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(ray_tracer->head.type == BS_OBJECT_RAY_TRACER, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_bindAccelerationStructure(bind_set_slot, bind_point_slot, ray_tracer);
}

BSAPI bs_Result _preval_bs_bindAccelerationStructures(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_RayTracer** ray_tracers, int ray_tracers_count) {
    BS_VALIDATE(ray_tracers != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_bindAccelerationStructures(bind_set_slot, bind_point_slot, ray_tracers, ray_tracers_count);
}

BSAPI void _preval_bs_pushDescriptors() {
    next.bs_pushDescriptors();
}

BSAPI void _preval_bs_pushBindings() {
    next.bs_pushBindings();
}

BSAPI bs_BindSet* _preval_bs_queryBindSet(bs_U32 id) {
    return next.bs_queryBindSet(id);
}

BSAPI bs_Binding* _preval_bs_queryBinding(const bs_BindSet* bind_set, bs_U32 id) {
    BS_VALIDATE(bind_set != NULL, NULL,);
    return next.bs_queryBinding(bind_set, id);
}

BSAPI void _preval_bs_configureAttribute(const char* name, bs_Format base_format) {
    BS_VALIDATE(name != NULL, ,);
    next.bs_configureAttribute(name, base_format);
}

BSAPI bs_Result _preval_bs_timeZoneBias(int* out) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_timeZoneBias(out);
}

BSAPI bs_DateTime _preval_bs_dateTime() {
    return next.bs_dateTime();
}

BSAPI bs_I64 _preval_bs_totalSeconds(const bs_DateTime* date_time) {
    BS_VALIDATE(date_time != NULL, 0,);
    return next.bs_totalSeconds(date_time);
}

BSAPI bool _preval_bs_isLaterThan(const bs_DateTime* a, const bs_DateTime* b) {
    BS_VALIDATE(a != NULL, false,);
    BS_VALIDATE(b != NULL, false,);
    return next.bs_isLaterThan(a, b);
}

BSAPI bs_vec2 _preval_bs_windowCursorPosition(bs_Context* context) {
    BS_VALIDATE(context != NULL, (bs_vec2) { 0 },);
    return next.bs_windowCursorPosition(context);
}

BSAPI bs_ivec2 _preval_bs_windowPosition() {
    return next.bs_windowPosition();
}

BSAPI bs_vec2 _preval_bs_screenCursorPosition() {
    return next.bs_screenCursorPosition();
}

BSAPI bool _preval_bs_middleClick() {
    return next.bs_middleClick();
}

BSAPI bool _preval_bs_middleClickOnce() {
    return next.bs_middleClickOnce();
}

BSAPI bool _preval_bs_middleClickUpOnce() {
    return next.bs_middleClickUpOnce();
}

BSAPI bool _preval_bs_leftClick() {
    return next.bs_leftClick();
}

BSAPI bool _preval_bs_rightClick() {
    return next.bs_rightClick();
}

BSAPI bool _preval_bs_rightClickOnce() {
    return next.bs_rightClickOnce();
}

BSAPI bool _preval_bs_leftClickOnce() {
    return next.bs_leftClickOnce();
}

BSAPI bool _preval_bs_rightClickUpOnce() {
    return next.bs_rightClickUpOnce();
}

BSAPI bool _preval_bs_leftClickUpOnce() {
    return next.bs_leftClickUpOnce();
}

BSAPI bool _preval_bs_keyDown(bs_U32 code) {
    return next.bs_keyDown(code);
}

BSAPI bool _preval_bs_keyHeld(bs_U32 code) {
    return next.bs_keyHeld(code);
}

BSAPI bool _preval_bs_keyDownOnce(bs_U32 code) {
    return next.bs_keyDownOnce(code);
}

BSAPI bool _preval_bs_keyUpOnce(bs_U32 code) {
    return next.bs_keyUpOnce(code);
}

BSAPI bool _preval_bs_charDown(unsigned char c) {
    return next.bs_charDown(c);
}

BSAPI bool _preval_bs_charDownOnce(unsigned char c) {
    return next.bs_charDownOnce(c);
}

BSAPI bool _preval_bs_charUpOnce(unsigned char c) {
    return next.bs_charUpOnce(c);
}

BSAPI int _preval_bs_scroll() {
    return next.bs_scroll();
}

BSAPI void _preval_bs_resizeWindow(bs_Context* context, bs_U32 width, bs_U32 height) {
    BS_VALIDATE(context != NULL, ,);
    next.bs_resizeWindow(context, width, height);
}

BSAPI void _preval_bs_moveWindow(bs_Context* context, int x, int y) {
    BS_VALIDATE(context != NULL, ,);
    next.bs_moveWindow(context, x, y);
}

BSAPI void _preval_bs_overrideTitleBar(int height) {
    next.bs_overrideTitleBar(height);
}

BSAPI bs_Result _preval_bs_window(bs_Context* context, bs_Callback tick, bs_U32 width, bs_U32 height, const char* title) {
    BS_VALIDATE(context != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(title != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_window(context, tick, width, height, title);
}

BSAPI void _preval_bs_device(bs_Context* context, bs_PhysicalDevice* device) {
    BS_VALIDATE(context != NULL, ,);
    next.bs_device(context, device);
}

BSAPI void _preval_bs_tickContext(bs_Context* context) {
    BS_VALIDATE(context != NULL, ,);
    next.bs_tickContext(context);
}

BSAPI void _preval_bs_tick(bs_Callback fixed_tick) {
    next.bs_tick(fixed_tick);
}

BSAPI void _preval_bs_exit() {
    next.bs_exit();
}

BSAPI void _preval_bs_setCursor(bs_CursorIcon type) {
    next.bs_setCursor(type);
}

BSAPI double _preval_bs_deltaTime() {
    return next.bs_deltaTime();
}

BSAPI void _preval_bs_pause() {
    next.bs_pause();
}

BSAPI void _preval_bs_advance() {
    next.bs_advance();
}

BSAPI double _preval_bs_elapsedTime() {
    return next.bs_elapsedTime();
}

BSAPI bs_ivec2 _preval_bs_resolution(bs_Context* context) {
    BS_VALIDATE(context != NULL, (bs_ivec2) { 0 },);
    return next.bs_resolution(context);
}

BSAPI void _preval_bs_titleWindow(bs_Context* context, char* name) {
    BS_VALIDATE(context != NULL, ,);
    BS_VALIDATE(name != NULL, ,);
    next.bs_titleWindow(context, name);
}

BSAPI void _preval_bs_titleWindowN(bs_Context* context, char* name, int name_length) {
    BS_VALIDATE(context != NULL, ,);
    BS_VALIDATE(name != NULL, ,);
    next.bs_titleWindowN(context, name, name_length);
}

BSAPI void _preval_bs_titleWindowV(bs_Context* context, char* format, va_list args) {
    BS_VALIDATE(context != NULL, ,);
    BS_VALIDATE(format != NULL, ,);
    next.bs_titleWindowV(context, format, args);
}

BSAPI bool _preval_bs_inFixedTick() {
    return next.bs_inFixedTick();
}

BSAPI void _preval_bs_setTargetFramerate(int fps) {
    next.bs_setTargetFramerate(fps);
}

BSAPI bs_Timer _preval_bs_timer() {
    return next.bs_timer();
}

BSAPI void _preval_bs_checkTimer(bs_Timer* timer) {
    BS_VALIDATE(timer != NULL, ,);
    next.bs_checkTimer(timer);
}

BSAPI void _preval_bs_copyToClipboard(char* value) {
    BS_VALIDATE(value != NULL, ,);
    next.bs_copyToClipboard(value);
}

BSAPI void _preval_bs_copyToClipboardN(char* value, int value_length) {
    BS_VALIDATE(value != NULL, ,);
    next.bs_copyToClipboardN(value, value_length);
}

BSAPI void _preval_bs_copyToClipboardV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, ,);
    next.bs_copyToClipboardV(format, args);
}

BSAPI bs_String* _preval_bs_appendString(bs_String* destination, char* value) {
    BS_VALIDATE(destination != NULL, NULL,);
    BS_VALIDATE(value != NULL, NULL,);
    return next.bs_appendString(destination, value);
}

BSAPI bs_String* _preval_bs_appendStringN(bs_String* destination, char* value, int value_length) {
    BS_VALIDATE(destination != NULL, NULL,);
    BS_VALIDATE(value != NULL, NULL,);
    return next.bs_appendStringN(destination, value, value_length);
}

BSAPI bs_String* _preval_bs_appendStringV(bs_String* destination, char* format, va_list args) {
    BS_VALIDATE(destination != NULL, NULL,);
    BS_VALIDATE(format != NULL, NULL,);
    return next.bs_appendStringV(destination, format, args);
}

BSAPI bs_Result _preval_bs_foreachFile(bs_ForeachDocumentFunction x, void* param, char* value) {
    BS_VALIDATE(param != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(value != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_foreachFile(x, param, value);
}

BSAPI bs_Result _preval_bs_foreachFileN(bs_ForeachDocumentFunction x, void* param, char* value, int value_length) {
    BS_VALIDATE(param != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(value != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_foreachFileN(x, param, value, value_length);
}

BSAPI bs_Result _preval_bs_foreachFileV(bs_ForeachDocumentFunction x, void* param, char* format, va_list args) {
    BS_VALIDATE(param != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_foreachFileV(x, param, format, args);
}

BSAPI bs_Result _preval_bs_foreachDirectory(bs_ForeachDocumentFunction x, void* param, char* path) {
    BS_VALIDATE(param != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_foreachDirectory(x, param, path);
}

BSAPI bs_Result _preval_bs_foreachDirectoryN(bs_ForeachDocumentFunction x, void* param, char* path, int path_length) {
    BS_VALIDATE(param != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_foreachDirectoryN(x, param, path, path_length);
}

BSAPI bs_Result _preval_bs_foreachDirectoryV(bs_ForeachDocumentFunction x, void* param, char* format, va_list args) {
    BS_VALIDATE(param != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_foreachDirectoryV(x, param, format, args);
}

BSAPI int _preval_bs_numFiles(char* path) {
    BS_VALIDATE(path != NULL, 0,);
    return next.bs_numFiles(path);
}

BSAPI int _preval_bs_numFilesN(char* path, int path_length) {
    BS_VALIDATE(path != NULL, 0,);
    return next.bs_numFilesN(path, path_length);
}

BSAPI int _preval_bs_numFilesV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, 0,);
    return next.bs_numFilesV(format, args);
}

BSAPI int _preval_bs_numDirectories(char* path) {
    BS_VALIDATE(path != NULL, 0,);
    return next.bs_numDirectories(path);
}

BSAPI int _preval_bs_numDirectoriesN(char* path, int path_length) {
    BS_VALIDATE(path != NULL, 0,);
    return next.bs_numDirectoriesN(path, path_length);
}

BSAPI int _preval_bs_numDirectoriesV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, 0,);
    return next.bs_numDirectoriesV(format, args);
}

BSAPI bs_Result _preval_bs_openFile(const char* mode, bs_File* out, char* path) {
    BS_VALIDATE(mode != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_openFile(mode, out, path);
}

BSAPI bs_Result _preval_bs_openFileN(const char* mode, bs_File* out, char* path, int path_length) {
    BS_VALIDATE(mode != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_openFileN(mode, out, path, path_length);
}

BSAPI bs_Result _preval_bs_openFileV(const char* mode, bs_File* out, char* format, va_list args) {
    BS_VALIDATE(mode != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_openFileV(mode, out, format, args);
}

BSAPI void _preval_bs_closeFile(bs_File* file) {
    BS_VALIDATE(file != NULL, ,);
    next.bs_closeFile(file);
}

BSAPI bs_Result _preval_bs_loadFile(bs_String** out, char* path) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadFile(out, path);
}

BSAPI bs_Result _preval_bs_loadFileN(bs_String** out, char* path, int path_length) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadFileN(out, path, path_length);
}

BSAPI bs_Result _preval_bs_loadFileV(bs_String** out, char* format, va_list args) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadFileV(out, format, args);
}

BSAPI bs_Result _preval_bs_loadFileChunk(long offset, size_t size, bs_String** out, char* path) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadFileChunk(offset, size, out, path);
}

BSAPI bs_Result _preval_bs_loadFileChunkN(long offset, size_t size, bs_String** out, char* path, int path_length) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadFileChunkN(offset, size, out, path, path_length);
}

BSAPI bs_Result _preval_bs_loadFileChunkV(long offset, size_t size, bs_String** out, char* format, va_list args) {
    BS_VALIDATE(out != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_loadFileChunkV(offset, size, out, format, args);
}

BSAPI bs_Result _preval_bs_deleteFile(char* path) {
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_deleteFile(path);
}

BSAPI bs_Result _preval_bs_deleteFileN(char* path, int path_length) {
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_deleteFileN(path, path_length);
}

BSAPI bs_Result _preval_bs_deleteFileV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_deleteFileV(format, args);
}

BSAPI bs_Result _preval_bs_deleteDirectoryContents(char* path) {
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_deleteDirectoryContents(path);
}

BSAPI bs_Result _preval_bs_deleteDirectoryContentsN(char* path, int path_length) {
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_deleteDirectoryContentsN(path, path_length);
}

BSAPI bs_Result _preval_bs_deleteDirectoryContentsV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_deleteDirectoryContentsV(format, args);
}

BSAPI bs_Result _preval_bs_deleteDirectory(char* path) {
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_deleteDirectory(path);
}

BSAPI bs_Result _preval_bs_deleteDirectoryN(char* path, int path_length) {
    BS_VALIDATE(path != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_deleteDirectoryN(path, path_length);
}

BSAPI bs_Result _preval_bs_deleteDirectoryV(char* format, va_list args) {
    BS_VALIDATE(format != NULL, BS_RESULT_VALIDATION_ERROR,);
    return next.bs_deleteDirectoryV(format, args);
}

bs_FunctionTable* _preval_bs_getFunctionTable() {
    static bs_FunctionTable functions = { 0 };

    functions.bs_callbacks = _preval_bs_callbacks;
    functions.bs_scope = _preval_bs_scope;
    functions.bs_writeLogFile = _preval_bs_writeLogFile;
    functions.bs_writeLogFileN = _preval_bs_writeLogFileN;
    functions.bs_writeLogFileV = _preval_bs_writeLogFileV;
    functions.bs_v2Mid = _preval_bs_v2Mid;
    functions.bs_v3Mid = _preval_bs_v3Mid;
    functions.bs_m4x3 = _preval_bs_m4x3;
    functions.bs_eulToQ = _preval_bs_eulToQ;
    functions.bs_qToEul = _preval_bs_qToEul;
    functions.bs_v2CubicBezier = _preval_bs_v2CubicBezier;
    functions.bs_v2QuadBezier = _preval_bs_v2QuadBezier;
    functions.bs_v3CubicBezier = _preval_bs_v3CubicBezier;
    functions.bs_v3QuadBezier = _preval_bs_v3QuadBezier;
    functions.bs_rotateAabb = _preval_bs_rotateAabb;
    functions.bs_fitAabb = _preval_bs_fitAabb;
    functions.bs_quad = _preval_bs_quad;
    functions.bs_linearTosRGB = _preval_bs_linearTosRGB;
    functions.bs_sRGBToLinear = _preval_bs_sRGBToLinear;
    functions.bs_linearV3TosRGB = _preval_bs_linearV3TosRGB;
    functions.bs_sRGBToLinearV3 = _preval_bs_sRGBToLinearV3;
    functions.bs_rgbV4ToUChar = _preval_bs_rgbV4ToUChar;
    functions.bs_rgbUCharToV4 = _preval_bs_rgbUCharToV4;
    functions.bs_hsvToRgb = _preval_bs_hsvToRgb;
    functions.bs_rgbToHsv = _preval_bs_rgbToHsv;
    functions.bs_convertYyjsonResult = _preval_bs_convertYyjsonResult;
    functions.bs_convertVulkanResult = _preval_bs_convertVulkanResult;
    functions.bs_convertWin32Error = _preval_bs_convertWin32Error;
    functions.bs_serializeWin32Error = _preval_bs_serializeWin32Error;
    functions.bs_convertErrno = _preval_bs_convertErrno;
    functions.bs_serializeErrno = _preval_bs_serializeErrno;
    functions.bs_playSound = _preval_bs_playSound;
    functions.bs_sound = _preval_bs_sound;
    functions.bs_iniAudio = _preval_bs_iniAudio;
    functions.bs_rayVsObb = _preval_bs_rayVsObb;
    functions.bs_sphereVsPoint = _preval_bs_sphereVsPoint;
    functions.bs_sphereVsObbTest = _preval_bs_sphereVsObbTest;
    functions.bs_sphereVsObb = _preval_bs_sphereVsObb;
    functions.bs_rectangleVsPoint = _preval_bs_rectangleVsPoint;
    functions.bs_lineVsLine = _preval_bs_lineVsLine;
    functions.bs_populateVertexDeclaration = _preval_bs_populateVertexDeclaration;
    functions.bs_beginComment = _preval_bs_beginComment;
    functions.bs_beginCommentN = _preval_bs_beginCommentN;
    functions.bs_beginCommentV = _preval_bs_beginCommentV;
    functions.bs_endComment = _preval_bs_endComment;
    functions.bs_swapchainImage = _preval_bs_swapchainImage;
    functions.bs_clearStencil = _preval_bs_clearStencil;
    functions.bs_clearDepth = _preval_bs_clearDepth;
    functions.bs_clearDepthStencil = _preval_bs_clearDepthStencil;
    functions.bs_clearColor = _preval_bs_clearColor;
    functions.bs_stencilReference = _preval_bs_stencilReference;
    functions.bs_cull = _preval_bs_cull;
    functions.bs_setLineWidth = _preval_bs_setLineWidth;
    functions.bs_batchSize = _preval_bs_batchSize;
    functions.bs_render = _preval_bs_render;
    functions.bs_barrier = _preval_bs_barrier;
    functions.bs_rayTrace = _preval_bs_rayTrace;
    functions.bs_rayTracer = _preval_bs_rayTracer;
    functions.bs_accelerateAabb = _preval_bs_accelerateAabb;
    functions.bs_accelerateBatch = _preval_bs_accelerateBatch;
    functions.bs_build = _preval_bs_build;
    functions.bs_destroyRayTracer = _preval_bs_destroyRayTracer;
    functions.bs_dispatchAsync = _preval_bs_dispatchAsync;
    functions.bs_bufferView = _preval_bs_bufferView;
    functions.bs_buffer = _preval_bs_buffer;
    functions.bs_bufferIsMapped = _preval_bs_bufferIsMapped;
    functions.bs_bufferMap = _preval_bs_bufferMap;
    functions.bs_mapBuffer = _preval_bs_mapBuffer;
    functions.bs_unmapBuffer = _preval_bs_unmapBuffer;
    functions.bs_stageNull = _preval_bs_stageNull;
    functions.bs_stageList = _preval_bs_stageList;
    functions.bs_stageImage = _preval_bs_stageImage;
    functions.bs_destroyBuffer = _preval_bs_destroyBuffer;
    functions.bs_copyAsync = _preval_bs_copyAsync;
    functions.bs_setBufferAsync = _preval_bs_setBufferAsync;
    functions.bs_batch = _preval_bs_batch;
    functions.bs_queryAttribute = _preval_bs_queryAttribute;
    functions.bs_queryAttributeN = _preval_bs_queryAttributeN;
    functions.bs_queryAttributeV = _preval_bs_queryAttributeV;
    functions.bs_canPushBatch = _preval_bs_canPushBatch;
    functions.bs_batchIsIndexed = _preval_bs_batchIsIndexed;
    functions.bs_minimizeBatch = _preval_bs_minimizeBatch;
    functions.bs_pushBatch = _preval_bs_pushBatch;
    functions.bs_unpushBatch = _preval_bs_unpushBatch;
    functions.bs_destroyBatch = _preval_bs_destroyBatch;
    functions.bs_ensureBatchSize = _preval_bs_ensureBatchSize;
    functions.bs_batchVertex = _preval_bs_batchVertex;
    functions.bs_batchRange = _preval_bs_batchRange;
    functions.bs_pushIndex = _preval_bs_pushIndex;
    functions.bs_pushIndices = _preval_bs_pushIndices;
    functions.bs_batchCube = _preval_bs_batchCube;
    functions.bs_pushCube = _preval_bs_pushCube;
    functions.bs_batchCone = _preval_bs_batchCone;
    functions.bs_pushCone = _preval_bs_pushCone;
    functions.bs_batchQuad = _preval_bs_batchQuad;
    functions.bs_pushQuad = _preval_bs_pushQuad;
    functions.bs_batchTriangle = _preval_bs_batchTriangle;
    functions.bs_pushTriangle = _preval_bs_pushTriangle;
    functions.bs_batchLine = _preval_bs_batchLine;
    functions.bs_pushLine = _preval_bs_pushLine;
    functions.bs_batchPoint = _preval_bs_batchPoint;
    functions.bs_pushPoint = _preval_bs_pushPoint;
    functions.bs_batchAabb = _preval_bs_batchAabb;
    functions.bs_pushAabb = _preval_bs_pushAabb;
    functions.bs_batchSphere = _preval_bs_batchSphere;
    functions.bs_pushSphere = _preval_bs_pushSphere;
    functions.bs_batchPyramid = _preval_bs_batchPyramid;
    functions.bs_pushPyramid = _preval_bs_pushPyramid;
    functions.bs_batchBipyramid = _preval_bs_batchBipyramid;
    functions.bs_pushBipyramid = _preval_bs_pushBipyramid;
    functions.bs_batchPrimitive = _preval_bs_batchPrimitive;
    functions.bs_pushPrimitive = _preval_bs_pushPrimitive;
    functions.bs_batchMesh = _preval_bs_batchMesh;
    functions.bs_pushMesh = _preval_bs_pushMesh;
    functions.bs_batchModel = _preval_bs_batchModel;
    functions.bs_pushModel = _preval_bs_pushModel;
    functions.bs_renderer = _preval_bs_renderer;
    functions.bs_output = _preval_bs_output;
    functions.bs_input = _preval_bs_input;
    functions.bs_dependency = _preval_bs_dependency;
    functions.bs_renderPass = _preval_bs_renderPass;
    functions.bs_framebuffer = _preval_bs_framebuffer;
    functions.bs_runPass = _preval_bs_runPass;
    functions.bs_rendererIsDynamic = _preval_bs_rendererIsDynamic;
    functions.bs_beginRender = _preval_bs_beginRender;
    functions.bs_endRender = _preval_bs_endRender;
    functions.bs_destroyRenderer = _preval_bs_destroyRenderer;
    functions.bs_resizeRenderer = _preval_bs_resizeRenderer;
    functions.bs_queueFamily = _preval_bs_queueFamily;
    functions.bs_present = _preval_bs_present;
    functions.bs_acquire = _preval_bs_acquire;
    functions.bs_queueSwap = _preval_bs_queueSwap;
    functions.bs_enqueue = _preval_bs_enqueue;
    functions.bs_imageIndex = _preval_bs_imageIndex;
    functions.bs_queue = _preval_bs_queue;
    functions.bs_destroyQueue = _preval_bs_destroyQueue;
    functions.bs_stallGPU = _preval_bs_stallGPU;
    functions.bs_stallQueue = _preval_bs_stallQueue;
    functions.bs_stall = _preval_bs_stall;
    functions.bs_poll = _preval_bs_poll;
    functions.bs_image = _preval_bs_image;
    functions.bs_transition = _preval_bs_transition;
    functions.bs_peekPng = _preval_bs_peekPng;
    functions.bs_peekPngN = _preval_bs_peekPngN;
    functions.bs_peekPngV = _preval_bs_peekPngV;
    functions.bs_loadPngData = _preval_bs_loadPngData;
    functions.bs_loadPng = _preval_bs_loadPng;
    functions.bs_peekFile = _preval_bs_peekFile;
    functions.bs_savePng = _preval_bs_savePng;
    functions.bs_savePngN = _preval_bs_savePngN;
    functions.bs_savePngV = _preval_bs_savePngV;
    functions.bs_encodePng = _preval_bs_encodePng;
    functions.bs_destroyImage = _preval_bs_destroyImage;
    functions.bs_resizeImage = _preval_bs_resizeImage;
    functions.bs_queryImageIndexHash = _preval_bs_queryImageIndexHash;
    functions.bs_queryImageIndex = _preval_bs_queryImageIndex;
    functions.bs_copyImageToBufferAsync = _preval_bs_copyImageToBufferAsync;
    functions.bs_copyBufferToImage = _preval_bs_copyBufferToImage;
    functions.bs_blit = _preval_bs_blit;
    functions.bs_loadImage = _preval_bs_loadImage;
    functions.bs_loadImageN = _preval_bs_loadImageN;
    functions.bs_loadImageV = _preval_bs_loadImageV;
    functions.bs_isStencilFormat = _preval_bs_isStencilFormat;
    functions.bs_isDepthFormat = _preval_bs_isDepthFormat;
    functions.bs_hasAlpha = _preval_bs_hasAlpha;
    functions.bs_destroySampler = _preval_bs_destroySampler;
    functions.bs_sampler = _preval_bs_sampler;
    functions.bs_loadAtlas = _preval_bs_loadAtlas;
    functions.bs_loadAtlasN = _preval_bs_loadAtlasN;
    functions.bs_loadAtlasV = _preval_bs_loadAtlasV;
    functions.bs_atlasCoordinates = _preval_bs_atlasCoordinates;
    functions.bs_mirrorUV = _preval_bs_mirrorUV;
    functions.bs_flipUV = _preval_bs_flipUV;
    functions.bs_atlasSize = _preval_bs_atlasSize;
    functions.bs_queryAtlasHash = _preval_bs_queryAtlasHash;
    functions.bs_queryAtlas = _preval_bs_queryAtlas;
    functions.bs_destroyAtlas = _preval_bs_destroyAtlas;
    functions.bs_loadAtlasMemory = _preval_bs_loadAtlasMemory;
    functions.bs_parseArgs = _preval_bs_parseArgs;
    functions.bs_ini = _preval_bs_ini;
    functions.bs_queryProcedures = _preval_bs_queryProcedures;
    functions.bs_queueSemaphore = _preval_bs_queueSemaphore;
    functions.bs_acquisitionSemaphore = _preval_bs_acquisitionSemaphore;
    functions.bs_resetQueue = _preval_bs_resetQueue;
    functions.bs_pushQueue = _preval_bs_pushQueue;
    functions.bsi_nameHandle = _preval_bsi_nameHandle;
    functions.bsi_nameHandleN = _preval_bsi_nameHandleN;
    functions.bsi_nameHandleV = _preval_bsi_nameHandleV;
    functions.bs_beginEnumeration = _preval_bs_beginEnumeration;
    functions.bs_enumerateJson = _preval_bs_enumerateJson;
    functions.bs_jsonRoot = _preval_bs_jsonRoot;
    functions.bs_ensureJsonMutable = _preval_bs_ensureJsonMutable;
    functions.bs_jsonCopy = _preval_bs_jsonCopy;
    functions.bs_saveJson = _preval_bs_saveJson;
    functions.bs_emptyJson = _preval_bs_emptyJson;
    functions.bs_emptyJsonArray = _preval_bs_emptyJsonArray;
    functions.bs_json = _preval_bs_json;
    functions.bs_loadJson = _preval_bs_loadJson;
    functions.bs_loadJsonN = _preval_bs_loadJsonN;
    functions.bs_loadJsonV = _preval_bs_loadJsonV;
    functions.bs_destroyJson = _preval_bs_destroyJson;
    functions.bs_parseJsonValue = _preval_bs_parseJsonValue;
    functions.bs_fetchJson = _preval_bs_fetchJson;
    functions.bs_fetchJsonN = _preval_bs_fetchJsonN;
    functions.bs_fetchJsonV = _preval_bs_fetchJsonV;
    functions.bs_deleteJson = _preval_bs_deleteJson;
    functions.bs_deleteJsonN = _preval_bs_deleteJsonN;
    functions.bs_deleteJsonV = _preval_bs_deleteJsonV;
    functions.bs_ensureJson = _preval_bs_ensureJson;
    functions.bs_ensureJsonN = _preval_bs_ensureJsonN;
    functions.bs_ensureJsonV = _preval_bs_ensureJsonV;
    functions.bs_jsonValueFromObject = _preval_bs_jsonValueFromObject;
    functions.bs_jsonValueFromRoot = _preval_bs_jsonValueFromRoot;
    functions.bs_jsonValueFromBool = _preval_bs_jsonValueFromBool;
    functions.bs_jsonValueFromInteger = _preval_bs_jsonValueFromInteger;
    functions.bs_jsonValueFromFloat = _preval_bs_jsonValueFromFloat;
    functions.bs_jsonValueFromString = _preval_bs_jsonValueFromString;
    functions.bs_jsonValueFromStringPointer = _preval_bs_jsonValueFromStringPointer;
    functions.bs_jsonValueFromDateTime = _preval_bs_jsonValueFromDateTime;
    functions.bs_jsonObject = _preval_bs_jsonObject;
    functions.bs_jsonArray = _preval_bs_jsonArray;
    functions.bs_jsonVec2 = _preval_bs_jsonVec2;
    functions.bs_jsonVec3 = _preval_bs_jsonVec3;
    functions.bs_jsonVec4 = _preval_bs_jsonVec4;
    functions.bs_jsonRGBA = _preval_bs_jsonRGBA;
    functions.bs_logSection = _preval_bs_logSection;
    functions.bs_logSectionN = _preval_bs_logSectionN;
    functions.bs_logSectionV = _preval_bs_logSectionV;
    functions.bs_logEndOfSection = _preval_bs_logEndOfSection;
    functions.bs_logWithTimestamp = _preval_bs_logWithTimestamp;
    functions.bs_logWithTimestampN = _preval_bs_logWithTimestampN;
    functions.bs_logWithTimestampV = _preval_bs_logWithTimestampV;
    functions.bs_log = _preval_bs_log;
    functions.bs_logN = _preval_bs_logN;
    functions.bs_logV = _preval_bs_logV;
    functions.bs_info = _preval_bs_info;
    functions.bs_infoN = _preval_bs_infoN;
    functions.bs_infoV = _preval_bs_infoV;
    functions.bs_warn = _preval_bs_warn;
    functions.bs_warnN = _preval_bs_warnN;
    functions.bs_warnV = _preval_bs_warnV;
    functions.bs_critical = _preval_bs_critical;
    functions.bs_criticalN = _preval_bs_criticalN;
    functions.bs_criticalV = _preval_bs_criticalV;
    functions.bs_instance = _preval_bs_instance;
    functions.bs_args = _preval_bs_args;
    functions.bs_features = _preval_bs_features;
    functions.bs_props = _preval_bs_props;
    functions.bs_config = _preval_bs_config;
    functions.bs_system = _preval_bs_system;
    functions.bs_systemN = _preval_bs_systemN;
    functions.bs_systemV = _preval_bs_systemV;
    functions.bs_createThread = _preval_bs_createThread;
    functions.bs_formatStringLength = _preval_bs_formatStringLength;
    functions.bs_checkStringPool = _preval_bs_checkStringPool;
    functions.bs_stringAlloc = _preval_bs_stringAlloc;
    functions.bs_emptyString = _preval_bs_emptyString;
    functions.bs_string = _preval_bs_string;
    functions.bs_stringN = _preval_bs_stringN;
    functions.bs_stringV = _preval_bs_stringV;
    functions.bs_toUpper = _preval_bs_toUpper;
    functions.bs_toLower = _preval_bs_toLower;
    functions.bs_hash = _preval_bs_hash;
    functions.bs_stringHash = _preval_bs_stringHash;
    functions.bs_startsWith = _preval_bs_startsWith;
    functions.bs_endsWith = _preval_bs_endsWith;
    functions.bs_lastChar = _preval_bs_lastChar;
    functions.bs_stringContainsChar = _preval_bs_stringContainsChar;
    functions.bs_workingDirectory = _preval_bs_workingDirectory;
    functions.bs_setWorkingDirectory = _preval_bs_setWorkingDirectory;
    functions.bs_setWorkingDirectoryN = _preval_bs_setWorkingDirectoryN;
    functions.bs_setWorkingDirectoryV = _preval_bs_setWorkingDirectoryV;
    functions.bs_executablePath = _preval_bs_executablePath;
    functions.bs_appdataPath = _preval_bs_appdataPath;
    functions.bs_shortenString = _preval_bs_shortenString;
    functions.bs_appendChar = _preval_bs_appendChar;
    functions.bs_removeCharRange = _preval_bs_removeCharRange;
    functions.bs_insertChar = _preval_bs_insertChar;
    functions.bs_appendPath = _preval_bs_appendPath;
    functions.bs_replaceCharOccurrences = _preval_bs_replaceCharOccurrences;
    functions.bs_strndup = _preval_bs_strndup;
    functions.bs_strnlen = _preval_bs_strnlen;
    functions.bs_strsep = _preval_bs_strsep;
    functions.bs_memmem = _preval_bs_memmem;
    functions.bs_alignUp = _preval_bs_alignUp;
    functions.bs_widen = _preval_bs_widen;
    functions.bs_unwiden = _preval_bs_unwiden;
    functions.bs_charStringV = _preval_bs_charStringV;
    functions.bs_free = _preval_bs_free;
    functions.bs_malloc = _preval_bs_malloc;
    functions.bs_calloc = _preval_bs_calloc;
    functions.bs_realloc = _preval_bs_realloc;
    functions.bs_listContains = _preval_bs_listContains;
    functions.bs_fetchUnit = _preval_bs_fetchUnit;
    functions.bs_fetchLast = _preval_bs_fetchLast;
    functions.bs_ensureSize = _preval_bs_ensureSize;
    functions.bs_erase = _preval_bs_erase;
    functions.bs_pushBack = _preval_bs_pushBack;
    functions.bs_pushBackList = _preval_bs_pushBackList;
    functions.bs_destroyList = _preval_bs_destroyList;
    functions.bs_seekList = _preval_bs_seekList;
    functions.bs_minimizeList = _preval_bs_minimizeList;
    functions.bs_list = _preval_bs_list;
    functions.bs_guidToString = _preval_bs_guidToString;
    functions.bs_stringToGuid = _preval_bs_stringToGuid;
    functions.bs_sameGuid = _preval_bs_sameGuid;
    functions.bs_guid = _preval_bs_guid;
    functions.bs_guidIsNull = _preval_bs_guidIsNull;
    functions.bs_numDigits = _preval_bs_numDigits;
    functions.bs_directoryExists = _preval_bs_directoryExists;
    functions.bs_directoryExistsN = _preval_bs_directoryExistsN;
    functions.bs_directoryExistsV = _preval_bs_directoryExistsV;
    functions.bs_fileExtension = _preval_bs_fileExtension;
    functions.bs_fileExtensionIs = _preval_bs_fileExtensionIs;
    functions.bs_fileName = _preval_bs_fileName;
    functions.bs_appendFile = _preval_bs_appendFile;
    functions.bs_appendFileN = _preval_bs_appendFileN;
    functions.bs_appendFileV = _preval_bs_appendFileV;
    functions.bs_saveFile = _preval_bs_saveFile;
    functions.bs_saveFileN = _preval_bs_saveFileN;
    functions.bs_saveFileV = _preval_bs_saveFileV;
    functions.bs_convertWin32Path = _preval_bs_convertWin32Path;
    functions.bs_convertWin32PathN = _preval_bs_convertWin32PathN;
    functions.bs_convertWin32PathV = _preval_bs_convertWin32PathV;
    functions.bs_ensureDirectory = _preval_bs_ensureDirectory;
    functions.bs_ensureDirectoryN = _preval_bs_ensureDirectoryN;
    functions.bs_ensureDirectoryV = _preval_bs_ensureDirectoryV;
    functions.bs_fileModifiedDate = _preval_bs_fileModifiedDate;
    functions.bs_fileModifiedDateN = _preval_bs_fileModifiedDateN;
    functions.bs_fileModifiedDateV = _preval_bs_fileModifiedDateV;
    functions.bs_setFileModifiedDate = _preval_bs_setFileModifiedDate;
    functions.bs_setFileModifiedDateN = _preval_bs_setFileModifiedDateN;
    functions.bs_setFileModifiedDateV = _preval_bs_setFileModifiedDateV;
    functions.bs_fullPath = _preval_bs_fullPath;
    functions.bs_fileExists = _preval_bs_fileExists;
    functions.bs_fileExistsN = _preval_bs_fileExistsN;
    functions.bs_fileExistsV = _preval_bs_fileExistsV;
    functions.bs_toLong = _preval_bs_toLong;
    functions.bs_toULong = _preval_bs_toULong;
    functions.bs_toDouble = _preval_bs_toDouble;
    functions.bs_model = _preval_bs_model;
    functions.bs_destroyModel = _preval_bs_destroyModel;
    functions.bs_interpolateRotation = _preval_bs_interpolateRotation;
    functions.bs_interpolateTranslation = _preval_bs_interpolateTranslation;
    functions.bs_interpolateScale = _preval_bs_interpolateScale;
    functions.bs_boneTransform = _preval_bs_boneTransform;
    functions.bs_bonePosition = _preval_bs_bonePosition;
    functions.bs_transformBone = _preval_bs_transformBone;
    functions.bs_blendPose = _preval_bs_blendPose;
    functions.bs_bone = _preval_bs_bone;
    functions.bs_fabrik = _preval_bs_fabrik;
    functions.bs_bindPose = _preval_bs_bindPose;
    functions.bs_keyframePosition = _preval_bs_keyframePosition;
    functions.bs_keyframeRotation = _preval_bs_keyframeRotation;
    functions.bs_keyframeScale = _preval_bs_keyframeScale;
    functions.bs_loadAnimation = _preval_bs_loadAnimation;
    functions.bs_queryBoneId = _preval_bs_queryBoneId;
    functions.bs_queryArmature = _preval_bs_queryArmature;
    functions.bs_queryBone = _preval_bs_queryBone;
    functions.bs_queryMesh = _preval_bs_queryMesh;
    functions.bs_queryMeshHash = _preval_bs_queryMeshHash;
    functions.bs_queryMaterial = _preval_bs_queryMaterial;
    functions.bs_idName = _preval_bs_idName;
    functions.bs_resetObject = _preval_bs_resetObject;
    functions.bs_object = _preval_bs_object;
    functions.bs_packages = _preval_bs_packages;
    functions.bs_objectSources = _preval_bs_objectSources;
    functions.bs_destroyResource = _preval_bs_destroyResource;
    functions.bs_queryResource = _preval_bs_queryResource;
    functions.bs_queryPackage = _preval_bs_queryPackage;
    functions.bs_loadResource = _preval_bs_loadResource;
    functions.bs_loadResourceN = _preval_bs_loadResourceN;
    functions.bs_loadResourceV = _preval_bs_loadResourceV;
    functions.bs_loadPackage = _preval_bs_loadPackage;
    functions.bs_loadPackageN = _preval_bs_loadPackageN;
    functions.bs_loadPackageV = _preval_bs_loadPackageV;
    functions.bs_configureSource = _preval_bs_configureSource;
    functions.bs_exists = _preval_bs_exists;
    functions.bs_fetch = _preval_bs_fetch;
    functions.bs_shouldLoadId = _preval_bs_shouldLoadId;
    functions.bs_shader = _preval_bs_shader;
    functions.bs_destroyShader = _preval_bs_destroyShader;
    functions.bs_computePipeline = _preval_bs_computePipeline;
    functions.bs_destroyComputePipeline = _preval_bs_destroyComputePipeline;
    functions.bs_queryPipeline = _preval_bs_queryPipeline;
    functions.bs_pipelineHash = _preval_bs_pipelineHash;
    functions.bs_pipeline = _preval_bs_pipeline;
    functions.bs_destroyPipeline = _preval_bs_destroyPipeline;
    functions.bs_pushConstant = _preval_bs_pushConstant;
    functions.bs_rayTracingPipeline = _preval_bs_rayTracingPipeline;
    functions.bs_loadBindings = _preval_bs_loadBindings;
    functions.bs_binding = _preval_bs_binding;
    functions.bs_bindImage = _preval_bs_bindImage;
    functions.bs_bindImages = _preval_bs_bindImages;
    functions.bs_bindBuffer = _preval_bs_bindBuffer;
    functions.bs_bindBuffers = _preval_bs_bindBuffers;
    functions.bs_bindAccelerationStructure = _preval_bs_bindAccelerationStructure;
    functions.bs_bindAccelerationStructures = _preval_bs_bindAccelerationStructures;
    functions.bs_pushDescriptors = _preval_bs_pushDescriptors;
    functions.bs_pushBindings = _preval_bs_pushBindings;
    functions.bs_queryBindSet = _preval_bs_queryBindSet;
    functions.bs_queryBinding = _preval_bs_queryBinding;
    functions.bs_configureAttribute = _preval_bs_configureAttribute;
    functions.bs_timeZoneBias = _preval_bs_timeZoneBias;
    functions.bs_dateTime = _preval_bs_dateTime;
    functions.bs_totalSeconds = _preval_bs_totalSeconds;
    functions.bs_isLaterThan = _preval_bs_isLaterThan;
    functions.bs_windowCursorPosition = _preval_bs_windowCursorPosition;
    functions.bs_windowPosition = _preval_bs_windowPosition;
    functions.bs_screenCursorPosition = _preval_bs_screenCursorPosition;
    functions.bs_middleClick = _preval_bs_middleClick;
    functions.bs_middleClickOnce = _preval_bs_middleClickOnce;
    functions.bs_middleClickUpOnce = _preval_bs_middleClickUpOnce;
    functions.bs_leftClick = _preval_bs_leftClick;
    functions.bs_rightClick = _preval_bs_rightClick;
    functions.bs_rightClickOnce = _preval_bs_rightClickOnce;
    functions.bs_leftClickOnce = _preval_bs_leftClickOnce;
    functions.bs_rightClickUpOnce = _preval_bs_rightClickUpOnce;
    functions.bs_leftClickUpOnce = _preval_bs_leftClickUpOnce;
    functions.bs_keyDown = _preval_bs_keyDown;
    functions.bs_keyHeld = _preval_bs_keyHeld;
    functions.bs_keyDownOnce = _preval_bs_keyDownOnce;
    functions.bs_keyUpOnce = _preval_bs_keyUpOnce;
    functions.bs_charDown = _preval_bs_charDown;
    functions.bs_charDownOnce = _preval_bs_charDownOnce;
    functions.bs_charUpOnce = _preval_bs_charUpOnce;
    functions.bs_scroll = _preval_bs_scroll;
    functions.bs_resizeWindow = _preval_bs_resizeWindow;
    functions.bs_moveWindow = _preval_bs_moveWindow;
    functions.bs_overrideTitleBar = _preval_bs_overrideTitleBar;
    functions.bs_window = _preval_bs_window;
    functions.bs_device = _preval_bs_device;
    functions.bs_tickContext = _preval_bs_tickContext;
    functions.bs_tick = _preval_bs_tick;
    functions.bs_exit = _preval_bs_exit;
    functions.bs_setCursor = _preval_bs_setCursor;
    functions.bs_deltaTime = _preval_bs_deltaTime;
    functions.bs_pause = _preval_bs_pause;
    functions.bs_advance = _preval_bs_advance;
    functions.bs_elapsedTime = _preval_bs_elapsedTime;
    functions.bs_resolution = _preval_bs_resolution;
    functions.bs_titleWindow = _preval_bs_titleWindow;
    functions.bs_titleWindowN = _preval_bs_titleWindowN;
    functions.bs_titleWindowV = _preval_bs_titleWindowV;
    functions.bs_inFixedTick = _preval_bs_inFixedTick;
    functions.bs_setTargetFramerate = _preval_bs_setTargetFramerate;
    functions.bs_timer = _preval_bs_timer;
    functions.bs_checkTimer = _preval_bs_checkTimer;
    functions.bs_copyToClipboard = _preval_bs_copyToClipboard;
    functions.bs_copyToClipboardN = _preval_bs_copyToClipboardN;
    functions.bs_copyToClipboardV = _preval_bs_copyToClipboardV;
    functions.bs_appendString = _preval_bs_appendString;
    functions.bs_appendStringN = _preval_bs_appendStringN;
    functions.bs_appendStringV = _preval_bs_appendStringV;
    functions.bs_foreachFile = _preval_bs_foreachFile;
    functions.bs_foreachFileN = _preval_bs_foreachFileN;
    functions.bs_foreachFileV = _preval_bs_foreachFileV;
    functions.bs_foreachDirectory = _preval_bs_foreachDirectory;
    functions.bs_foreachDirectoryN = _preval_bs_foreachDirectoryN;
    functions.bs_foreachDirectoryV = _preval_bs_foreachDirectoryV;
    functions.bs_numFiles = _preval_bs_numFiles;
    functions.bs_numFilesN = _preval_bs_numFilesN;
    functions.bs_numFilesV = _preval_bs_numFilesV;
    functions.bs_numDirectories = _preval_bs_numDirectories;
    functions.bs_numDirectoriesN = _preval_bs_numDirectoriesN;
    functions.bs_numDirectoriesV = _preval_bs_numDirectoriesV;
    functions.bs_openFile = _preval_bs_openFile;
    functions.bs_openFileN = _preval_bs_openFileN;
    functions.bs_openFileV = _preval_bs_openFileV;
    functions.bs_closeFile = _preval_bs_closeFile;
    functions.bs_loadFile = _preval_bs_loadFile;
    functions.bs_loadFileN = _preval_bs_loadFileN;
    functions.bs_loadFileV = _preval_bs_loadFileV;
    functions.bs_loadFileChunk = _preval_bs_loadFileChunk;
    functions.bs_loadFileChunkN = _preval_bs_loadFileChunkN;
    functions.bs_loadFileChunkV = _preval_bs_loadFileChunkV;
    functions.bs_deleteFile = _preval_bs_deleteFile;
    functions.bs_deleteFileN = _preval_bs_deleteFileN;
    functions.bs_deleteFileV = _preval_bs_deleteFileV;
    functions.bs_deleteDirectoryContents = _preval_bs_deleteDirectoryContents;
    functions.bs_deleteDirectoryContentsN = _preval_bs_deleteDirectoryContentsN;
    functions.bs_deleteDirectoryContentsV = _preval_bs_deleteDirectoryContentsV;
    functions.bs_deleteDirectory = _preval_bs_deleteDirectory;
    functions.bs_deleteDirectoryN = _preval_bs_deleteDirectoryN;
    functions.bs_deleteDirectoryV = _preval_bs_deleteDirectoryV;

    return &functions;
}

