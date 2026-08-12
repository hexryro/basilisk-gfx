
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

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>

#include <basilisk-core.h>
#include <bs_internal.h>

struct bs_List _bs_pipelines_[BS_PIPELINE_TYPE_COUNT] = {0};



  /*==============================================================================
   * Descriptors
   *============================================================================*/

static VkDescriptorSetLayout _bs_pushDescriptorLayout(bs_BindSet* bind_set) {
    VkResult result;

    VkDescriptorSetLayoutBinding* layout_bindings = _bs_calloc(bind_set->bindings_count, sizeof(VkDescriptorSetLayoutBinding));

    for (int i = 0; i < bind_set->bindings_count; i++) {
        VkDescriptorSetLayoutBinding* layout_binding = layout_bindings + i;
        bs_Binding* binding = bind_set->bindings + i;

        if (binding->stages == 0) {
            _bs_warnF("Failed to push descriptor layouts for binding (%d, %d), binding has no shader stages", bind_set->slot, binding->slot);
            continue;
        }
        
        layout_binding->binding = binding->slot;
        layout_binding->descriptorCount = binding->descriptors_count; // == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE) ? _bs_num_objects.images : 1;
        layout_binding->descriptorType = (VkDescriptorType)binding->type;
        layout_binding->stageFlags = binding->stages;
    }

    VkDescriptorSetLayoutCreateInfo layout_i = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = bind_set->bindings_count,
        .pBindings = layout_bindings,
    };
    
    VkDescriptorSetLayout layout = VK_NULL_HANDLE;
    result = vkCreateDescriptorSetLayout(_bs_instance_->device, &layout_i, NULL, &layout);
    if (result != VK_SUCCESS) {
        _bs_warnF("Failed to create descriptor set layout for bind set %d (Vulkan result = %d)", bind_set->slot, result);
        _bs_free(layout_bindings);
        return VK_NULL_HANDLE;
    }

    _bs_instance_->layouts[bind_set->slot] = layout;

    for (int i = 0; i < BS_PIPELINE_TYPE_COUNT; i++) {
        for (int j = 0; j < _bs_pipelines_[i].count; j++) {
            bs_Pipeline* pipeline = *(bs_Pipeline**)_bs_fetchUnit(_bs_pipelines_ + i, j);
            if (bind_set->slot < pipeline->num_bind_sets)
                pipeline->flags |= BS_PIPELINE_NEEDS_UPDATING;
        }
    }

    _bs_free(layout_bindings);
    return layout;
}

static VkDescriptorSet _bs_pushDescriptorSet(bs_BindSet* bind_set, VkDescriptorSetLayout layout, VkDescriptorPool pool) {
    VkResult result;

    VkDescriptorSetAllocateInfo alloc_i = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = pool,
        .descriptorSetCount = 1,
        .pSetLayouts = &layout,
    };

    VkDescriptorSet set = VK_NULL_HANDLE;
    result = vkAllocateDescriptorSets(_bs_instance_->device, &alloc_i, &set);
    if (result != VK_SUCCESS) {
        _bs_warnF("Failed to create descriptor set for bind set %d (Vulkan result = %d)", bind_set->slot, result);
        return VK_NULL_HANDLE;
    }

    _bs_instance_->sets[bind_set->slot] = set;

    bsi_nameHandleF(set, VK_OBJECT_TYPE_DESCRIPTOR_SET, "Bind set %d", bind_set->slot);

    return set;
}

static void _bs_destroyDescriptors() {

} 

static void _bs_pushDescriptorPools() {
//    if (_bs_instance->descriptor_pool_needs_update) {
//        _bs_instance->descriptor_pool_needs_update = false;
//    }
//    else return;
    static VkDescriptorPool descriptor_pool = VK_NULL_HANDLE;
    if (descriptor_pool) {
        for (int i = 0; i < BS_MAX_NUM_BIND_SETS; i++) {
            if (_bs_instance_->sets[i])
                vkFreeDescriptorSets(_bs_instance_->device, descriptor_pool, 1, _bs_instance_->sets + i); // @todo reuse
            if (_bs_instance_->layouts[i])
                vkDestroyDescriptorSetLayout(_bs_instance_->device, _bs_instance_->layouts[i], NULL);
        }

        vkDestroyDescriptorPool(_bs_instance_->device, descriptor_pool, NULL);
    }

    VkDescriptorPoolSize pool_sizes[BS_DESCRIPTOR_TYPES_COUNT] = { 0 };
    VkDescriptorPoolSize pool_sizes_contiguous[BS_DESCRIPTOR_TYPES_COUNT] = { 0 };
    bs_U32 num_pool_sizes = 0;

    for(int i = 0; i < _bs_instance_->bind_sets_count; i++) {
        bs_BindSet* bind_set = _bs_instance_->bind_sets + i;

        if (bind_set->bindings_count == 0)
            continue;

        for(int j = 0; j < bind_set->bindings_count; j++) {
            bs_Binding* binding = bind_set->bindings + j;

            pool_sizes[binding->type_index].descriptorCount++;
            pool_sizes[binding->type_index].type = (VkDescriptorType)binding->type;
        }
    }

    for(int i = 0; i < BS_DESCRIPTOR_TYPES_COUNT; i++) {
        if (pool_sizes[i].descriptorCount == 0) 
            continue;

        pool_sizes_contiguous[num_pool_sizes++] = pool_sizes[i];
    }

    VkDescriptorPoolCreateInfo pool_i = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
        .poolSizeCount = num_pool_sizes,
        .pPoolSizes = pool_sizes_contiguous,
        .maxSets = BS_MAX_NUM_BIND_SETS,
    };

    VkResult result = vkCreateDescriptorPool(_bs_instance_->device, &pool_i, NULL, &descriptor_pool);
    if (result != VK_SUCCESS) {
        _bs_warnF("vkCreateDescriptorPool failed (Vulkan result = %d)", result);
        return;
    }

    for (int i = 0; i < _bs_instance_->bind_sets_count; i++) {
        bs_BindSet* bind_set = _bs_instance_->bind_sets + i;

        if (bind_set->bindings_count == 0) 
            continue;

        bind_set->vk_layout = _bs_pushDescriptorLayout(bind_set);
        bind_set->vk_set    = _bs_pushDescriptorSet(bind_set, bind_set->vk_layout, descriptor_pool);
    }

    bs_logN(BS_CONSTANT_STRING("Pushed descriptor pools"));
}

 /**
  Push descriptors
  */
BSAPI void _val_bs_pushDescriptors() {
    for (int i = 0; i < _bs_instance_->bind_sets_count; i++) {
        bs_BindSet* bind_set = _bs_instance_->bind_sets + i;
        if (!bind_set->needs_update)
            continue;

        BS_VALIDATE(bind_set->vk_update_template != NULL,,);
    }

    _bs_pushDescriptors();
}

BSAPI void _bs_pushDescriptors() {
    for (int i = 0; i < _bs_instance_->bind_sets_count; i++) {
        bs_BindSet* bind_set = _bs_instance_->bind_sets + i;

        if (!bind_set->needs_update)
            continue;

        bind_set->needs_update = false;
        vkUpdateDescriptorSetWithTemplate(_bs_instance_->device, bind_set->vk_set, bind_set->vk_update_template, bind_set->descriptors);

        bs_logF("Updated bind set %d descriptors", bind_set->slot);
    }
}

static inline bool _bs_bindIsImageType(bs_BindType type) {
    _bs_criticalF("%s: Not implemented", __func__);
    return false;
    //return type == BS_BIND_TYPE_SAMPLER || type == BS_BIND_TYPE_COMBINED_IMAGE_SAMPLER || type == BS_BIND_TYPE_SAMPLED_IMAGE || type == BS_BIND_TYPE_STORAGE_IMAGE;
}

static void _bs_prepareDescriptorTemplate(bs_BindSet* bind_set) {
    if (!bind_set->vk_layout)
        return;

    VkDescriptorUpdateTemplateEntry entries[BS_MAX_NUM_BINDINGS];
    bs_U32 num_entries = 0;

    if (bind_set->vk_update_template)
        vkDestroyDescriptorUpdateTemplate(_bs_instance_->device, bind_set->vk_update_template, NULL);

    for (bs_U32 i = 0; i < bind_set->bindings_count; i++) {
        bs_Binding* binding = bind_set->bindings + i;
        bs_U32 stride = sizeof(bs_Descriptor);

        if (!binding->in_use) continue;
        
        entries[num_entries++] = (VkDescriptorUpdateTemplateEntry) {
            .dstBinding = binding->slot,
            .descriptorCount = binding->descriptors_count,
            .descriptorType = (VkDescriptorType)binding->type,
            .offset = binding->location,
            .stride = stride,
        };
    }

    if (num_entries == 0) 
        return;

    VkDescriptorUpdateTemplateCreateInfo ci = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO,
        .pDescriptorUpdateEntries = entries,
        .descriptorUpdateEntryCount = num_entries,
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .templateType = VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_DESCRIPTOR_SET,
        .descriptorSetLayout = bind_set->vk_layout,
    };

    vkCreateDescriptorUpdateTemplate(_bs_instance_->device, &ci, NULL, &bind_set->vk_update_template);
}

BSAPI void _bs_pushBindings() {
    for (bs_U32 i = 0; i < _bs_instance_->bind_sets_count; i++) {
        bs_BindSet* bind_set = _bs_instance_->bind_sets + i;
        if (bind_set->bindings_count == 0) continue;

        _bs_prepareDescriptorTemplate(bind_set);
    }
}



  /*==============================================================================
   * Bindings
   *============================================================================*/

static inline bs_Result _bs_validateBinding(bs_U32 bind_set_slot, bs_U32 bind_point_slot, int descriptors_count) {
   // BS_VALIDATE(_bs_instance_->descriptor_lookup != NULL, BS_RESULT_VALIDATION_ERROR, "No bindings have been loaded");

    bs_BindSet* bind_set;
    bs_Binding* binding;

    bind_set = bs_queryBindSet(bind_set_slot);
    BS_VALIDATE(bind_set != NULL, BS_RESULT_VALIDATION_ERROR, );

    binding = bs_queryBinding(bind_set, bind_point_slot);
    BS_VALIDATE(binding != NULL, BS_RESULT_VALIDATION_ERROR, "Binding (%d, %d) is not used by any shader", bind_set_slot, bind_point_slot);

    if (!binding->in_use) {
        BS_VALIDATE(descriptors_count <= binding->descriptors_count, BS_RESULT_VALIDATION_ERROR, );
        BS_VALIDATE((bind_set->bound_descriptors_count + descriptors_count) <= bind_set->descriptors_count, BS_RESULT_VALIDATION_ERROR, );
    }

    return BS_RESULT_OK;
}

BSAPI bs_Result _val_bs_binding(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_Descriptor* descriptors, int descriptors_count) {
    BS_VALIDATE(_bs_validateBinding(bind_set_slot, bind_point_slot, descriptors_count) == BS_RESULT_OK, BS_RESULT_VALIDATION_ERROR,);

    return _bs_binding(bind_set_slot, bind_point_slot, descriptors, descriptors_count);
}

BSAPI bs_Result _bs_binding(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_Descriptor* descriptors, int descriptors_count) {
   // _bs_pushDescriptorPools();

    bs_BindSet* bind_set = _bs_queryBindSet(bind_set_slot);
    bs_Binding* binding = _bs_queryBinding(bind_set, bind_point_slot);

    if (!binding->in_use) {
        binding->location = bind_set->bound_descriptors_count * sizeof(bs_Descriptor);
        bind_set->bound_descriptors_count += descriptors_count;
       // binding->location = bind_set->descriptors_size;

        bs_logWithTimestampF(BS_MESSAGE_INFO, BS_PRINT_COLOR("+", BS_PRINT_GREEN) " Binding %d, %d", bind_set_slot, bind_point_slot);
        binding->in_use = true;
    }
    memcpy(((unsigned char*)bind_set->descriptors) + binding->location, descriptors, descriptors_count * sizeof(bs_Descriptor));
    //else if (binding->object.type != type)
    //    _bs_throwBasiliskF(BSXI_INTERNAL | BSX_INVALID_TYPE, "Attempted to bind (bs_ObjectType)%d to previously bound (bs_ObjectType)%d (%d, %d)", type, binding->object.type, bind_set_slot, slot);

  //  memcpy(bind_set->descriptors + binding->location, info, info_size);

    bind_set->needs_update = true;

    return BS_RESULT_OK;
}

 /**
  Bind images
  */
BSAPI bs_Result _val_bs_bindImages(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_ImageDescriptor* in_descriptors, int images_count) {
    for (int i = 0; i < images_count; i++) {
        bs_ImageDescriptor* descriptor = in_descriptors + i;

        BS_VALIDATE(descriptor->image != NULL, BS_RESULT_VALIDATION_ERROR,);
        BS_VALIDATE(descriptor->sampler != NULL, BS_RESULT_VALIDATION_ERROR,);

        BS_VALIDATE(descriptor->image->head.type == BS_OBJECT_IMAGE, BS_RESULT_VALIDATION_ERROR,);
        BS_VALIDATE(descriptor->sampler->head.type == BS_OBJECT_SAMPLER, BS_RESULT_VALIDATION_ERROR,);
    }

    BS_VALIDATE(_bs_validateBinding(bind_set_slot, bind_point_slot, images_count) == BS_RESULT_OK, BS_RESULT_VALIDATION_ERROR, );

    return _bs_bindImages(bind_set_slot, bind_point_slot, in_descriptors, images_count);
}

BSAPI bs_Result _bs_bindImages(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_ImageDescriptor* in_descriptors, int images_count) {
    size_t size = images_count * sizeof(bs_Descriptor);
    bs_Descriptor* descriptors = _alloca(size);

    for (int i = 0; i < images_count; i++) {
        bs_ImageDescriptor* descriptor = in_descriptors + i;

        descriptors[i] = (bs_Descriptor) {
            .as_image = {
                .vk_image_layout = (VkImageLayout)descriptor->layout,
                .vk_image_view = descriptor->image->_[descriptor->image->flags & BS_IMAGE_SWAPS_BIT ? _bs_context_->frame : 0].vk_image_view,
                .vk_sampler = descriptor->sampler ? descriptor->sampler->_->vk_sampler : VK_NULL_HANDLE,
                .image = descriptor->image,
                .sampler = descriptor->sampler,
            },
            .bind_set = bind_set_slot,
            .bind_point = bind_point_slot,
        };
    }

    return _bs_binding(bind_set_slot, bind_point_slot, descriptors, images_count);
}

BSAPI bs_Result _val_bs_bindImage(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_Image* image, bs_Sampler* sampler, bs_ImageLayout layout) {
    BS_VALIDATE(_bs_validateBinding(bind_set_slot, bind_point_slot, 1) == BS_RESULT_OK, BS_RESULT_VALIDATION_ERROR, );
    return _bs_bindImage(bind_set_slot, bind_point_slot, image, sampler, layout);
}

BSAPI bs_Result _bs_bindImage(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_Image* image, bs_Sampler* sampler, bs_ImageLayout layout) {
    return _bs_bindImages(bind_set_slot, bind_point_slot, &(bs_ImageDescriptor) {
        .sampler = sampler,
        .layout = layout,
        .image = image,
    }, 1);
}

 /**
  Bind buffers
  */
BSAPI bs_Result _val_bs_bindBuffers(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_Buffer** buffers, int buffers_count) {
    BS_VALIDATE(_bs_validateBinding(bind_set_slot, bind_point_slot, 1) == BS_RESULT_OK, BS_RESULT_VALIDATION_ERROR, );
    return _bs_bindBuffers(bind_set_slot, bind_point_slot, buffers, buffers_count);
}

BSAPI bs_Result _bs_bindBuffers(bs_U32 bind_set_slot, bs_U32 slot, bs_Buffer** buffers, int buffers_count) {
    bs_Result result;

    size_t size = buffers_count * sizeof(bs_Descriptor);
    bs_Descriptor* descriptors = _alloca(size);

    for (int i = 0; i < buffers_count; i++) {
        bs_Buffer* buffer = buffers[i];

        descriptors[i] = (bs_Descriptor) {
            .as_buffer = {
                .vk_buffer = buffer->_[buffer->flags & BSI_BUFFER_SWAPS_BIT ? _bs_context_->frame : 0].vk_buffer,
                .vk_range = buffer->num_bytes,
                .buffer = buffer,
            },
            .bind_set = bind_set_slot,
            .bind_point = slot,
        };

        buffer->flags |= BSI_BUFFER_IS_BOUND;
        buffer->bind_set = bind_set_slot;
        buffer->binding = slot;
    }

    return _bs_binding(bind_set_slot, slot, descriptors, buffers_count);
}

BSAPI bs_Result _val_bs_bindBuffer(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_Buffer* buffer) {
    BS_VALIDATE(_bs_validateBinding(bind_set_slot, bind_point_slot, 1) == BS_RESULT_OK, BS_RESULT_VALIDATION_ERROR,);
    return _bs_bindBuffer(bind_set_slot, bind_point_slot, buffer);
}

BSAPI bs_Result _bs_bindBuffer(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_Buffer* buffer) {
    return _bs_bindBuffers(bind_set_slot, bind_point_slot, &buffer, 1);
}


 /**
  Bind acceleration structures
  */
BSAPI bs_Result _val_bs_bindAccelerationStructures(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_RayTracer** ray_tracers, int ray_tracers_count) {
    BS_VALIDATE(_bs_validateBinding(bind_set_slot, bind_point_slot, 1) == BS_RESULT_OK, BS_RESULT_VALIDATION_ERROR,);
    return _bs_bindAccelerationStructures(bind_set_slot, bind_point_slot, ray_tracers, ray_tracers_count);
}

BSAPI bs_Result _bs_bindAccelerationStructures(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_RayTracer** ray_tracers, int ray_tracers_count) {
    _bs_warnN(BS_CONSTANT_STRING("_bs_bindAccelerationStructures has not been implemented yet"));
    return BS_RESULT_NOT_IMPLEMENTED;
}

BSAPI bs_Result _val_bs_bindAccelerationStructure(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_RayTracer* ray_tracer) {
    BS_VALIDATE(_bs_validateBinding(bind_set_slot, bind_point_slot, 1) == BS_RESULT_OK, BS_RESULT_VALIDATION_ERROR,);
    return _bs_bindAccelerationStructure(bind_set_slot, bind_point_slot, ray_tracer);
}

BSAPI bs_Result _bs_bindAccelerationStructure(bs_U32 bind_set_slot, bs_U32 bind_point_slot, bs_RayTracer* ray_tracer) {
    return _bs_bindAccelerationStructures(bind_set_slot, bind_point_slot, &ray_tracer, 1);
}

 /**
  Query bind set
  */
BSAPI bs_BindSet* _val_bs_queryBindSet(bs_U32 id) {
    //BS_VALIDATE(_bs_instance_->descriptor_lookup != NULL, NULL,);
    //BS_VALIDATE(id <= _bs_instance_->max_bind_set, NULL, );

    //int bind_set_id = _bs_instance_->descriptor_lookup[id].bind_set;
    //BS_VALIDATE(bind_set_id >= 0, NULL,);
    //BS_VALIDATE(bind_set_id < _bs_instance_->bind_sets_count, NULL, );

    return _bs_queryBindSet(id);
}

BSAPI bs_BindSet* _postval_bs_queryBindSet(bs_U32 id, bs_BindSet* _return) {
    BS_VALIDATE(_return->slot == id, NULL, );
    return _return;
}

BSAPI bs_BindSet* _bs_queryBindSet(bs_U32 id) {
    /*
    int bind_set = _bs_instance_->descriptor_lookup[id].bind_set;
    if (bind_set < 0) {
        _bs_warnF("Failed to query bind set %d\n", id);
        return NULL;
    }
    */

    for (int i = 0; i < _bs_instance_->bind_sets_count; i++) {
        if (_bs_instance_->bind_sets[i].slot == id)
            return _bs_instance_->bind_sets + i;
    }
 
    return NULL;
}

 /**
  Query binding
  */
BSAPI bs_Binding* _val_bs_queryBinding(bs_BindSet* bind_set, bs_U32 id) {
    BS_VALIDATE(id <= bind_set->max_binding, NULL, );
    return _bs_queryBinding(bind_set, id);
}

BSAPI bs_Binding* _postval_bs_queryBinding(bs_BindSet* bind_set, bs_U32 id, bs_Binding* _return) {
    BS_VALIDATE(_return->slot == id, NULL, );
    return _bs_queryBinding(bind_set, id);
}

BSAPI bs_Binding* _bs_queryBinding(const bs_BindSet* bind_set, bs_U32 id) {

    for (int i = 0; i < bind_set->bindings_count; i++) {
        if (bind_set->bindings[i].slot == id)
            return bind_set->bindings + i;
    }

    return NULL;

  //  int binding = _bs_instance_->descriptor_lookup[bind_set->slot].bindings[id];
  //  if (binding < 0) {
  //      _bs_warnF("Failed to query binding %d\n", id);
  //      return NULL;
  //  }
  //
  //  return _bs_instance_->bindings + binding;
}

 /**
  Load bindings

  TODO: Rework this, should not use JSON, write own format instead
  */
static int _bs_compareBindings(const bs_Binding* a, const bs_Binding* b) {
    if (a->set < b->set) return -1;
    else if (a->set > b->set) return 1;
    return 0;
}

static int _bs_compareBindSets(const bs_BindSet* a, const bs_BindSet* b) {
    if (a->slot < b->slot) return -1;
    else if (a->slot > b->slot) return 1;
    return 0;
}

BSAPI void _bs_loadBinding(bs_Binding* binding, int bind_set, int bind_point, int package_id, char* path) {
    bs_Result result;

    bs_Resource* resource;
    result = _bs_loadResource(package_id, 0, BS_RESOURCE_BINDING, &resource, path);
    if (result != BS_RESULT_OK) {
        return;
    }

    bs_BbndHeader* header = resource->data->value;

    if (header->magic != BS_BBND_MAGIC) {
        BS_WARN_INVALID_MAGIC("bindings", path);
        return BS_RESULT_CORRUPTED;
    }

    if (header->version != 1) {
        BS_WARN_UNSUPPORTED_VERSION("bindings", path);
        return BS_RESULT_NOT_SUPPORTED;
    }

    binding->descriptors_count = header->descriptors_count;
    binding->type = header->type;
    binding->type_index = header->type_index;
    binding->slot = bind_point;
    binding->set = bind_set;
    binding->size = header->size;
    binding->stages = header->shader_stages;

    _bs_instance_->bindings_count++;
}

static int _bs_loadPackageBindings(bs_Package* package, int package_id) {
    int descriptors_count = 0;
    for (int i = 0; i < package->resource_headers_count; i++) {
        bs_ResourceHeader* resource_header = package->resource_headers + i;
        if (resource_header->type != BS_RESOURCE_BINDING)
            continue;

        char* bind_set_string = strchr(resource_header->name, '/');
        if (bind_set_string == NULL) {
            bs_warnF("Binding \"%s\" has a missing bind set", resource_header->name);
            continue;
        }

        char* bind_point_string = strchr(bind_set_string + 1, '/');
        if (bind_point_string == NULL) {
            bs_warnF("Binding \"%s\" has a missing bind point", resource_header->name);
            continue;
        }

        bs_U64 bind_set = _bs_toULong(bind_set_string + 1);
        if (bind_set == BS_U64_MAX) continue;

        bs_U64 bind_point = _bs_toULong(bind_point_string + 1);
        if (bind_point == BS_U64_MAX) continue;

        bs_Binding* binding = _bs_instance_->bindings + _bs_instance_->bindings_count;
        _bs_loadBinding(binding, bind_set, bind_point, package_id, resource_header->name);

        descriptors_count += binding->descriptors_count;
        _bs_instance_->bind_sets_count = BS_MAX(_bs_instance_->bind_sets_count, bind_set + 1);
    }

    return descriptors_count;
}

BSAPI void _bs_loadBindings() {
    bs_List* packages = _bs_packages();

   /**
    Find total bindings count
    */
    int bindings_count = 0;

    for (int i = 0; i < packages->count; i++) {
        bs_Package* package = _bs_fetchUnit(packages, i);
        bindings_count += package->resource_type_offsets[BS_RESOURCE_BINDING].num;
    }

   /**
    Allocate memory
    */
    const size_t bind_sets_size = BS_MAX_NUM_BIND_SETS * sizeof(bs_BindSet);
    const size_t bindings_size = bindings_count * sizeof(bs_Binding);

    if (bindings_size == 0)
        return;

    _bs_instance_->bind_sets = _bs_realloc(_bs_instance_->bind_sets, bind_sets_size);
    _bs_instance_->bindings = _bs_realloc(_bs_instance_->bindings, bindings_size);
    memset(_bs_instance_->bind_sets, 0, bind_sets_size);
    memset(_bs_instance_->bindings, 0, bindings_size);
    _bs_instance_->descriptor_pool_needs_update = true;

   /**
    Load bindings
    */
    int desriptors_count = 0;
    for (int i = 0; i < packages->count; i++) {
        bs_Package* package = _bs_fetchUnit(packages, i);
        desriptors_count += _bs_loadPackageBindings(package, i);
    }

    const size_t descriptors_size = desriptors_count * sizeof(bs_Descriptor);
    _bs_instance_->descriptors = _bs_realloc(_bs_instance_->descriptors, descriptors_size);
    memset(_bs_instance_->descriptors, 0, descriptors_size);

   /**
    Sort bindings
    */
    qsort(_bs_instance_->bindings, _bs_instance_->bindings_count, sizeof(bs_Binding), _bs_compareBindings);

    int current_set = -1;
    int descriptor_offset = 0;
    for (int i = 0; i < bindings_count; i++) {
        bs_Binding* binding = _bs_instance_->bindings + i;
        bs_BindSet* bind_set = _bs_instance_->bind_sets + binding->set;

        assert(binding->set < _bs_instance_->bind_sets_count);

        if (binding->set != current_set) {
            current_set = binding->set;

            *bind_set = (bs_BindSet){
                .slot = current_set,
                .bindings = binding,
                .descriptors = _bs_instance_->descriptors + descriptor_offset,
            };
        }

        _bs_instance_->max_bind_set = BS_MAX(_bs_instance_->max_bind_set, bind_set->slot);
        bind_set->max_binding = BS_MAX(bind_set->max_binding, binding->slot);

        bind_set->bindings_count++;
        bind_set->descriptors_count += binding->descriptors_count;
        descriptor_offset += binding->descriptors_count;
    }

   /**
    Logging
    */
    static bs_String* s;
    for (int i = 0; i < _bs_instance_->bind_sets_count; i++) {
        bs_BindSet* bind_set = _bs_instance_->bind_sets + i;

        s = bs_appendStringF(s, "Bind set %d", bind_set->slot);

        for (int j = 0; j < bind_set->bindings_count; j++) {
            bs_Binding* binding = bind_set->bindings + j;
            s = bs_appendStringF(s, "    Binding %d", binding->slot);

        }
    }

    bs_logN(s->value, s->len);

   /**
    Create lookup table
    */
    /*
    int total_max_bindings = 0;
    for (int i = 0; i < _bs_instance_->bind_sets_count; i++)
        total_max_bindings += _bs_instance_->bind_sets[i].max_binding + 1;

    size_t bind_set_lookup_size = (_bs_instance_->max_bind_set + 1) * sizeof(*_bs_instance_->descriptor_lookup);
    size_t binding_lookup_size = total_max_bindings * sizeof(int);
    size_t lookup_size = bind_set_lookup_size + binding_lookup_size;
    _bs_instance_->descriptor_lookup = _bs_realloc(_bs_instance_->descriptor_lookup, lookup_size);
    memset(_bs_instance_->descriptor_lookup, -1, lookup_size);
    unsigned char* binding_lookup_offset = ((unsigned char*)_bs_instance_->descriptor_lookup) + bind_set_lookup_size;

    for (int i = 0; i < _bs_instance_->bind_sets_count; i++) {
        bs_BindSet* bind_set = _bs_instance_->bind_sets + i;

        _bs_instance_->descriptor_lookup[bind_set->slot].bindings = _bs_calloc(bind_set->max_binding + 1, sizeof(int));
        memset(_bs_instance_->descriptor_lookup[bind_set->slot].bindings, -1, (bind_set->max_binding + 1) * sizeof(int));
        _bs_instance_->descriptor_lookup[bind_set->slot].bind_set = i;

        for (int j = 0; j < bind_set->bindings_count; j++) {
            bs_Binding* binding = bind_set->bindings + j;
            _bs_instance_->descriptor_lookup[bind_set->slot].bindings[binding->slot] = (binding - _bs_instance_->bindings);
        }
        binding_lookup_offset += (bind_set->max_binding + 1) * sizeof(int);
    }

    */
    _bs_pushDescriptorPools();

    return BS_RESULT_OK;
}



  /*==============================================================================
   * Shaders
   *============================================================================*/

static inline bs_Format _bs_convertFormatFromBaseType(VkFormat format, bs_U32 size) {
    switch (format) {
    case VK_FORMAT_R8_UNORM: {
        if      (size ==  4) return BS_FORMAT_R8_UNORM;
        else if (size ==  8) return BS_FORMAT_R8G8_UNORM;
        else if (size == 12) return BS_FORMAT_R8G8B8_UNORM;
        else if (size == 16) return BS_FORMAT_R8G8B8A8_UNORM;
    } break;
    case VK_FORMAT_R32_SFLOAT: {
        if      (size ==  4) return BS_FORMAT_R32_SFLOAT;
        else if (size ==  8) return BS_FORMAT_R32G32_SFLOAT;
        else if (size == 12) return BS_FORMAT_R32G32B32_SFLOAT;
        else if (size == 16) return BS_FORMAT_R32G32B32A32_SFLOAT;
    } break;
    case VK_FORMAT_R32_SINT: {
        if      (size ==  4) return BS_FORMAT_R32_SINT;
        else if (size ==  8) return BS_FORMAT_R32G32_SINT;
        else if (size == 12) return BS_FORMAT_R32G32B32_SINT;
        else if (size == 16) return BS_FORMAT_R32G32B32A32_SINT;
    } break;
    case VK_FORMAT_R32_UINT: {
        if      (size ==  4) return BS_FORMAT_R32_UINT;
        else if (size ==  8) return BS_FORMAT_R32G32_UINT;
        else if (size == 12) return BS_FORMAT_R32G32B32_UINT;
        else if (size == 16) return BS_FORMAT_R32G32B32A32_UINT;
    } break;
    }

    _bs_warnF("Failed to convert base format %d of invalid size %d", format, size);
    return BS_FORMAT_UNDEFINED;
}

BSAPI void _bs_configureAttribute(const char* name, bs_Format base_format) {
    _bs_pushBack(&_bs_config_.attributes, &(bs_AttributeType) {
        .base_format = base_format,
        .name = name,
        .name_hash = _bs_stringHash(name),
    });
}

static int _bs_compareAttributes(const bs_Attribute* a, const bs_Attribute* b) {
    if      (a->location == b->location) return 0;
    else if (a->location <  b->location) return -1;
    else return 1;
}

BSAPI bs_Result _bs_shader(int package_id, const char* name, bs_U32 flags, bs_Resource** out) {
    bs_Result result;

    bs_Resource* resource;
    result = _bs_loadResource(package_id, flags, BS_RESOURCE_SHADER, &resource, name);
    if (result != BS_RESULT_OK)
        return result;

    bs_BshaHeader* header = resource->data->value;

    if (header->magic != BS_BSHA_MAGIC) {
        BS_WARN_INVALID_MAGIC("shader", name);
        return BS_RESULT_CORRUPTED;
    }

    if (header->version != 1) {
        BS_WARN_UNSUPPORTED_VERSION("shader", name);
        return BS_RESULT_NOT_SUPPORTED;
    }

    size_t attributes_size = header->attributes_count * sizeof(bs_BshaAttribute);
    size_t spirv_offset = sizeof(bs_BshaHeader) + attributes_size;

    bs_Shader shader = {
        .type = header->shader_type,
        .num_attributes = header->attributes_count,
        .constant_size = header->push_constant_size,
        .spirv = resource->data->value + spirv_offset,
        .spirv_length = header->spirv_size,
        .bind_sets = header->bind_set_flags,
        .resource = resource,
    };

   /**
    Read attributes
    */
    if (header->attributes_count > 0)
        shader.attributes = bs_calloc(header->attributes_count, sizeof(bs_Attribute));

    for (int i = 0; i < header->attributes_count; i++) {
        size_t offset = sizeof(bs_BshaHeader) + i * sizeof(bs_BshaAttribute);

        bs_BshaAttribute* attribute = resource->data->value + offset;
        bs_Attribute* result = shader.attributes + i;

        result->location = attribute->location;
        result->size = attribute->size;
        result->name_hash = attribute->name_hash;

        for (int j = 0; j < _bs_config_.attributes.count; j++) {
            bs_AttributeType* config = _bs_fetchUnit(&_bs_config_.attributes, j);
            if (config->name_hash == result->name_hash) {
                result->format = _bs_convertFormatFromBaseType((VkFormat)config->base_format, result->size);
                break;
            }
        }
        
        if (result->format == 0) {
            _bs_warnF("Attribute (location %d) from shader \"%s\" has not been configured, please configure with _bs_configureAttribute(...)", name);
            return BS_RESULT_INVALID_STATE; // TODO invalid config or sum
        }
    }

    qsort(shader.attributes, header->attributes_count, sizeof(bs_Attribute), _bs_compareAttributes);

    for (int i = 0, offset = 0; i < header->attributes_count; i++) {
        bs_Attribute* result = shader.attributes + i;
        result->offset = offset;
        offset += result->size;
    }

   /**
    Create module
    */
    VkShaderModuleCreateInfo shader_ci = {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = shader.spirv_length,
        .pCode = shader.spirv,
    };

    VkResult vk_result = vkCreateShaderModule(_bs_instance_->device, &shader_ci, NULL, &shader.vk_module);
    if (vk_result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkCreateShaderModule", vk_result, "");
        return _bs_convertVulkanResult(vk_result);
    }

    switch (shader.type) {
    case BS_SHADER_STAGE_VERTEX_BIT:
    case BS_SHADER_STAGE_FRAGMENT_BIT:
    case BS_SHADER_STAGE_GEOMETRY_BIT:
        shader.pipeline_type = BS_PIPELINE_GRAPHICS;
        break;
    case BS_SHADER_STAGE_COMPUTE_BIT:
        shader.pipeline_type = BS_PIPELINE_COMPUTE;
        break;
//    case BS_SHADER_STAGE_RAY_GEN_BIT:
//    case BS_SHADER_STAGE_ANY_HIT_BIT:
//    case BS_SHADER_STAGE_CLOSEST_HIT_BIT:
//    case BS_SHADER_STAGE_MISS_BIT:
//    case BS_SHADER_STAGE_INTERSECTION_BIT:
//        shader.pipeline_type = BS_PIPELINE_RAY_TRACE;
//        break;
    }

    for (int i = 0; i < _bs_pipelines_[shader.pipeline_type].count; i++) {
        bs_Pipeline* pipeline = *(bs_Pipeline**)_bs_fetchUnit(_bs_pipelines_ + shader.pipeline_type, i);

        for (int j = 0; j < pipeline->shaders_count; j++) {
            if (pipeline->_[j].shader == resource->shader) {
                pipeline->flags |= BS_PIPELINE_NEEDS_UPDATING;
                break;
            }
        }
    }

    resource->shader = _bs_malloc(sizeof(bs_Shader)); // todo dont do this
    memcpy(resource->shader, &shader, sizeof(bs_Shader));

    bsi_nameHandle(shader.vk_module, VK_OBJECT_TYPE_SHADER_MODULE, name);
    *out = resource;

    return BS_RESULT_OK;
}

BSAPI void _bs_destroyShader(bs_Shader* shader) {
    vkDestroyShaderModule(_bs_instance_->device, shader->vk_module, NULL);
}



  /*==============================================================================
   * Pipelines
   *============================================================================*/

BSAPI bs_Pipeline* _bs_queryPipeline(bs_PipelineType type, bs_U64 hash) {
    for (int i = 0; i < _bs_pipelines_[type].count; i++) {
        bs_Pipeline* pipeline = *(bs_Pipeline**)_bs_fetchUnit(_bs_pipelines_ + type, i);

        if (pipeline->hash == hash)
            return pipeline;
    }

    return NULL;
}

 /**
  Push constants
  */
BSAPI void _val_bs_pushConstant(bs_Queue* queue, bs_Pipeline* pipeline, bs_U32 offset, bs_U32 size, void* data) {
    BS_VALIDATE(pipeline != NULL, ,);
    BS_VALIDATE((offset + size) <= pipeline->constant_size, , "Push constant %d + %d > %d", offset, size, pipeline->constant_size);

    _bs_pushConstant(queue, pipeline, offset, size, data);
}

BSAPI void _bs_pushConstant(bs_Queue* queue, bs_Pipeline* pipeline, bs_U32 offset, bs_U32 size, void* data) {
    VkCommandBuffer command_buffer = _bsi_fetchCommands(queue);
    vkCmdPushConstants(command_buffer, pipeline->vk_layout, pipeline->shader_stages, offset, size, data);

    if (queue->flags & BS_QUEUE_SINGLE_TIMES_BIT) {
        _bs_pushQueue(queue, 0, NULL);
        vkQueueWaitIdle(queue->queue);
    }
}

static void val_bs_createPipelineLayout(bs_Pipeline* pipeline, VkPipelineLayout* out) {
    for (int i = 0; i < pipeline->num_bind_sets; i++) {
        if (_bs_instance_->layouts[i] == NULL) {
            _bs_warnF("Pipeline cannot be created with unordered bind sets (bind set %d is not used by any shader)", i);
            return;
        }
    }
}

static bs_Result _bs_createPipelineLayout(bs_Pipeline* pipeline) {
    VkResult vk_result;

    for (int i = _bs_instance_->bind_sets_count - 1; i >= 0; i--) { // TODO: active bind sets only
        if (!(pipeline->bind_sets & (1 << _bs_instance_->bind_sets[i].slot))) 
            continue;

        pipeline->num_bind_sets = _bs_instance_->bind_sets[i].slot + 1;
        break;
    }

    VkPushConstantRange range = { 0 };
    for (int i = 0; i < pipeline->shaders_count; i++) {
        bs_Shader* shader = pipeline->_[i].shader;

        if (!shader) 
            continue;

        if (shader->constant_size == 0) 
            continue;

        range.stageFlags = pipeline->shader_stages |= shader->type;
        range.size = pipeline->constant_size = BS_MAX(range.size, shader->constant_size);
    }

    VkPipelineLayoutCreateInfo pipeline_layout_i = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = pipeline->num_bind_sets,
        .pSetLayouts = _bs_instance_->layouts,
        .pPushConstantRanges = &range,
        .pushConstantRangeCount = range.size > 0 ? 1 : 0,
    };

    vk_result = vkCreatePipelineLayout(_bs_instance_->device, &pipeline_layout_i, NULL, &pipeline->vk_layout);
    if (vk_result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkCreatePipelineLayout", vk_result, "");
        return _bs_convertVulkanResult(vk_result);
    }

    return BS_RESULT_OK;
}

static inline VkPipelineShaderStageCreateInfo _bs_shaderStage(bs_Shader* shader, bs_SlotBits* bind_sets, VkShaderStageFlags flags) {
    *bind_sets |= shader->bind_sets;

    return (VkPipelineShaderStageCreateInfo) {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = flags,
        .module = shader->vk_module,
        .pName = "main"
    };
}

static inline bool _bs_samePipeline(bs_Pipeline* pipeline, bs_SlotBits bind_sets) {
    return pipeline->bind_sets == bind_sets; // todo maybe need more checks
}

static inline bool _bs_pipelineNeedsUpdating(bs_Pipeline* pipeline) {
    return pipeline->flags & BS_PIPELINE_NEEDS_UPDATING;
}

BSAPI void _bs_destroyComputePipeline(bs_Pipeline* pipeline) {
    vkDestroyPipelineLayout(_bs_instance_->device, pipeline->vk_layout, NULL);
    vkDestroyPipeline(_bs_instance_->device, pipeline->vk_pipeline, NULL);
}

typedef struct {
    bs_Shader* compute_shader;
    bs_PipelineFlags flags;
} bs_ComputePipelineHash;

static bs_Pipeline* _bs_preparePipeline(bs_PipelineType type, bs_U64 hash, bs_Pipeline init, bool* already_exists) {
    if (_bs_pipelines_[type].capacity == 0)
        _bs_pipelines_[type] = _bs_list(sizeof(bs_Pipeline*), 64);

    bs_Pipeline* existing = _bs_queryPipeline(type, hash);

    if (existing) {
        if (_bs_pipelineNeedsUpdating(existing)) {
            _bs_destroyPipeline(existing);
            existing->flags &= ~BS_PIPELINE_NEEDS_UPDATING;
        }
        else {
            *already_exists = true;
            return existing;
        }
    }

    if (!existing) {
        existing = _bs_object(-1, 0, sizeof(bs_Pipeline), BS_SWAP_SIZE(bs_Pipeline), init.shaders_count, 0, -1)->head;
        _bs_pushBack(_bs_pipelines_ + type, &existing);
    }

    memcpy(existing, &init, sizeof(bs_Pipeline));

    existing->type = type;
    existing->hash = hash;

    return existing;
}

BSAPI bs_Result _bs_computePipeline(bs_Shader* compute_shader, bs_PipelineFlags flags, bs_Pipeline** out) {
    bs_Result bs_result;

    bs_U64 hash = _bs_hash(&((bs_ComputePipelineHash) { 
        .compute_shader = compute_shader, 
        .flags = flags 
    }), sizeof(bs_ComputePipelineHash));

    bs_Pipeline init = {
        .type = BS_PIPELINE_COMPUTE,
        .shaders_count = 1,
        .bind_sets = compute_shader->bind_sets,
        .hash = hash,
    };

    bool already_exists = false;
    bs_Pipeline* pipeline = *out = _bs_preparePipeline(BS_PIPELINE_COMPUTE, hash, init, &already_exists);
    if (already_exists)
        return BS_RESULT_OK;

    bs_result = _bs_createPipelineLayout(pipeline);
    if (bs_result != BS_RESULT_OK)
        return bs_result;

    pipeline->_[0].shader = compute_shader;

    VkComputePipelineCreateInfo pipeline_ci = {
        .sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
        .stage = _bs_shaderStage(compute_shader, &pipeline->bind_sets, VK_SHADER_STAGE_COMPUTE_BIT),
        .layout = pipeline->vk_layout,
    };

    VkResult vk_result = vkCreateComputePipelines(_bs_instance_->device, VK_NULL_HANDLE, 1, &pipeline_ci, NULL, &pipeline->vk_pipeline);
    if (vk_result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkCreateComputePipelines", vk_result, "");
        return _bs_convertVulkanResult(vk_result);
    }

    const char* blue = (_bs_args_.color_log ? BS_PRINT_BLUE_BRIGHT : "");
    const char* cyan = (_bs_args_.color_log ? BS_PRINT_CYAN : "");
    const char* reset = (_bs_args_.color_log ? BS_PRINT_RESET : "");

    _bs_infoF("%s%" PRIx64 "%s %s", blue, pipeline->hash, reset, reset);

    return BS_RESULT_OK;
}

static inline VkStencilOpState _bs_mapStencilOpState(bs_StencilOperation op) {
    return (VkStencilOpState) {
        .failOp = (VkStencilOp)op.fail_op,
        .passOp = (VkStencilOp)op.pass_op,
        .depthFailOp = (VkStencilOp)op.depth_fail_op,
        .compareOp = (VkCompareOp)op.compare_op,
        .compareMask = op.compare_mask,
        .writeMask = op.write_mask,
        .reference = op.reference,
    };
}

BSAPI void _bs_destroyPipeline(bs_Pipeline* pipeline) {
    pipeline->name = _bs_free(pipeline->name);
    vkDestroyPipelineLayout(_bs_instance_->device, pipeline->vk_layout, NULL);
    vkDestroyPipeline(_bs_instance_->device, pipeline->vk_pipeline, NULL);
}

BSAPI bs_U64 _bs_pipelineHash(bs_PipelineHash* descriptor) {
    bs_U64 hash = 0xcbf29ce484222325;

    for (int i = 0; i < sizeof(bs_PipelineHash); i++) {
        hash ^= ((unsigned char*)descriptor)[i];
        hash *= 0x100000001b3;
    }

    return hash;
}

BSAPI bs_Result _val_bs_pipeline(bs_RendererScope* scope, bs_Queue* queue, bs_PipelineHash* descriptor, bs_Pipeline** out) {
    *out = NULL;
    BS_VALIDATE(scope->renderer != NULL, BS_RESULT_VALIDATION_ERROR, "Pipelines must be created within a renderer");
    BS_VALIDATE(descriptor->shaders[0] != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(descriptor->shaders[1] != NULL, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(descriptor->shaders[0]->type == BS_SHADER_STAGE_VERTEX_BIT, BS_RESULT_VALIDATION_ERROR,);
    BS_VALIDATE(descriptor->shaders[1]->type == BS_SHADER_STAGE_FRAGMENT_BIT, BS_RESULT_VALIDATION_ERROR,);

    bool is_dynamic_renderer = _bs_rendererIsDynamic(scope->renderer);
    if (!is_dynamic_renderer) {
        BS_VALIDATE(descriptor->subpass < scope->renderer->num_subpasses, BS_RESULT_VALIDATION_ERROR,
            "Pipeline subpass (%d) falls outside renderer (%d) subpass count (%d)",
            descriptor->subpass,
            scope->renderer->head.id,
            scope->renderer->num_subpasses);
    }

    return _bs_pipeline(scope, queue, descriptor, out);
}

BSAPI bs_Result _bs_pipeline(bs_RendererScope* scope, bs_Queue* queue, bs_PipelineHash* descriptor, bs_Pipeline** out) {
    VkResult vk_result;
    bs_Result bs_result;

    if (scope) {
        descriptor->subpass = scope->subpass;
        descriptor->renderer = scope->renderer;
    }

    bs_Shader* vs = descriptor->shaders[0];
    bs_Shader* fs = descriptor->shaders[1];

    bs_Pipeline init = {
        .type = BS_PIPELINE_GRAPHICS,
        .shaders_count = 2,
        .flags = descriptor->flags,
    };

    bs_U64 hash = _bs_pipelineHash(descriptor);

    bool already_exists = false;
    bs_Pipeline* pipeline = *out = _bs_preparePipeline(BS_PIPELINE_GRAPHICS, hash, init, &already_exists);
    if (already_exists)
        return BS_RESULT_OK;

    VkGraphicsPipelineCreateInfo pipeline_ci = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
    };

    VkPipelineRenderingCreateInfo render_info = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO,
    };

    VkPipelineDepthStencilStateCreateInfo depth_stencil_state;
    VkPipelineColorBlendAttachmentState blend_states[BS_MAX_ATTACHMENTS_COUNT];

    int num_blend_states = 0;

    bool is_dynamic_renderer = _bs_rendererIsDynamic(scope->renderer);
    if (!is_dynamic_renderer) {
        for (int i = 0; i < scope->renderer->num_outputs; i++) {
            bs_Output* output = scope->renderer->outputs + i;
            if (output->subpass != descriptor->subpass)
                continue;
            if (_bs_isDepthFormat(output->image->format))
                continue;

            if (!_bs_features_.independent_blend && num_blend_states > 0)
                memcpy(blend_states + num_blend_states++, blend_states, sizeof(VkPipelineColorBlendAttachmentState));
            else {
                blend_states[num_blend_states++] = (VkPipelineColorBlendAttachmentState){
                    .colorWriteMask = descriptor->attachments[num_blend_states].skip_write ? 0 : VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
                    .srcColorBlendFactor = (VkBlendFactor)descriptor->src_color_factor,
                    .dstColorBlendFactor = (VkBlendFactor)descriptor->dst_color_factor,
                    .colorBlendOp = (VkBlendOp)descriptor->color_op,
                    .srcAlphaBlendFactor = (VkBlendFactor)descriptor->src_alpha_factor,
                    .dstAlphaBlendFactor = (VkBlendFactor)descriptor->dst_alpha_factor,
                    .alphaBlendOp = (VkBlendOp)descriptor->alpha_op,
                    .blendEnable = descriptor->disable_blend ? false : _bs_hasAlpha(output->image->format),
                };
            }
  
        }
    }
    else {
        for (int i = 0; i < scope->renderer->num_outputs; i++) {
            bs_Output* output = scope->renderer->outputs + i;
            if (_bs_isDepthFormat(output->image->format)) {
                render_info.depthAttachmentFormat = (VkFormat)output->image->format; // TODO: ensure only one?
            }
        }
    }

    VkPipelineShaderStageCreateInfo shader_stages[] = {
        _bs_shaderStage(vs, &pipeline->bind_sets, VK_SHADER_STAGE_VERTEX_BIT),
        _bs_shaderStage(fs, &pipeline->bind_sets, VK_SHADER_STAGE_FRAGMENT_BIT)
    };

    pipeline->_[0].shader = vs;
    pipeline->_[1].shader = fs;

    _bs_pushBack(_bs_pipelines_ + BS_PIPELINE_GRAPHICS, &pipeline);

    bs_result = _bs_createPipelineLayout(pipeline);
    if (bs_result != BS_RESULT_OK)
        return bs_result;

    VkVertexInputAttributeDescription* attributes = NULL;
    VkVertexInputBindingDescription input_binding;
    VkViewport viewport = { 0 };
    VkRect2D scissor = { 0 };
    VkPipelineVertexInputStateCreateInfo vertex_ci;
    VkPipelineInputAssemblyStateCreateInfo assembly_ci;
    VkPipelineRasterizationStateCreateInfo rasterizer_ci;
    VkPipelineMultisampleStateCreateInfo multisampling_ci;
    VkPipelineColorBlendStateCreateInfo color_blending_ci;
    VkPipelineViewportStateCreateInfo viewport_state_ci;

    VkDynamicState states[] = { 
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR,
        VK_DYNAMIC_STATE_LINE_WIDTH
    };

    VkPipelineDynamicStateCreateInfo dynamic_state_i = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = sizeof(states) / sizeof(VkDynamicState),
        .pDynamicStates = states,
    };
    pipeline_ci.pDynamicState = &dynamic_state_i;

    // add attributes
    attributes = _alloca(vs->num_attributes * sizeof(VkVertexInputAttributeDescription));
    if (vs != NULL) {
        memset(attributes, vs->num_attributes * sizeof(VkVertexInputAttributeDescription), 0);

        int vertex_size = 0;
        for (int i = 0; i < vs->num_attributes; i++)
            vertex_size += vs->attributes[i].size;

        input_binding = (VkVertexInputBindingDescription) {
         //   .binding = object.pipeline->vs_binding,
            .stride = vertex_size,
            .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
        };

        bs_U32 offset = 0;
        for (int i = 0; i < vs->num_attributes; i++) {
            attributes[i].binding = 0;
            attributes[i].format = (VkFormat)vs->attributes[i].format;
            attributes[i].offset = offset;
            attributes[i].location = vs->attributes[i].location;
            offset += vs->attributes[i].size;
        }

        vertex_ci = (VkPipelineVertexInputStateCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
            .vertexBindingDescriptionCount = 1,
            .vertexAttributeDescriptionCount = vs->num_attributes,
            .pVertexBindingDescriptions = &input_binding,
            .pVertexAttributeDescriptions = attributes,
        };

        assembly_ci = (VkPipelineInputAssemblyStateCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
            .topology = (VkPrimitiveTopology)descriptor->topology_type,
            .primitiveRestartEnable = descriptor->restart_primitive,
        };

        pipeline_ci.pVertexInputState = &vertex_ci;
        pipeline_ci.pInputAssemblyState = &assembly_ci;
    }
    
    bs_ivec2 resolution = _bs_resolution();
    viewport.width = resolution.x;
    viewport.height = resolution.y;
    viewport.minDepth = 0.0;
    viewport.maxDepth = 1.0;

    scissor.extent.width = resolution.x;
    scissor.extent.height = resolution.y;

    viewport_state_ci = (VkPipelineViewportStateCreateInfo){
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .pViewports = &viewport,
        .pScissors = &scissor,
        .viewportCount = 1,
        .scissorCount = 1,
    };

    pipeline_ci.pViewportState = &viewport_state_ci;

    if (fs) {
        rasterizer_ci = (VkPipelineRasterizationStateCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
            .polygonMode = (VkPolygonMode)descriptor->polygon_type,
            .lineWidth = 1.0f,
            .cullMode = descriptor->cull_type,
            .depthClampEnable = descriptor->clamp_depth,
            .frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
        };

        multisampling_ci = (VkPipelineMultisampleStateCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
            .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
            .minSampleShading = 1.0f,
        };

        color_blending_ci = (VkPipelineColorBlendStateCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
            .logicOp = VK_LOGIC_OP_COPY,
            .attachmentCount = num_blend_states,
            .pAttachments = blend_states
        };

        bool has_stencil =
            descriptor->stencil_front.compare_op != 0 || descriptor->stencil_front.depth_fail_op != 0 ||
            descriptor->stencil_front.fail_op != 0 || descriptor->stencil_front.pass_op != 0 ||
            descriptor->stencil_back.compare_op != 0 || descriptor->stencil_back.depth_fail_op != 0 ||
            descriptor->stencil_back.fail_op != 0 || descriptor->stencil_back.pass_op != 0;

        depth_stencil_state = (VkPipelineDepthStencilStateCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
            .depthTestEnable = !descriptor->skip_depth_test,
            .depthWriteEnable = !descriptor->skip_depth_write,
            .depthCompareOp = (VkCompareOp)descriptor->depth_comparison,
            .depthBoundsTestEnable = VK_FALSE,
            .minDepthBounds = 0.0f,
            .maxDepthBounds = 1.0f,
            .stencilTestEnable = has_stencil && !descriptor->skip_stencil_test,
            .front = _bs_mapStencilOpState(descriptor->stencil_front),
            .back = _bs_mapStencilOpState(descriptor->stencil_back),
        };

        pipeline_ci.pRasterizationState = &rasterizer_ci;
        pipeline_ci.pMultisampleState = &multisampling_ci;
        pipeline_ci.pColorBlendState = &color_blending_ci;
        if (!is_dynamic_renderer)
            pipeline_ci.pDepthStencilState = BS_RENDERER_SUBPASS_HAS_DEPTH(scope->renderer->flags, 0) ? &depth_stencil_state : NULL; // todo should this be 0?
        else
            pipeline_ci.pDepthStencilState = &depth_stencil_state;
    }

    pipeline_ci.stageCount = sizeof(shader_stages) / sizeof(*shader_stages);
    pipeline_ci.pStages = shader_stages;
    pipeline_ci.layout = pipeline->vk_layout;
    if (!is_dynamic_renderer)
        pipeline_ci.renderPass = scope->renderer->render_pass;
    else
        pipeline_ci.pNext = &render_info;
    pipeline_ci.basePipelineIndex = -1;
    pipeline_ci.subpass = descriptor->subpass;

    vk_result = vkCreateGraphicsPipelines(_bs_instance_->device, VK_NULL_HANDLE, 1, &pipeline_ci, NULL, &pipeline->vk_pipeline);
    if (vk_result != VK_SUCCESS) {
        BS_WARN_VULKAN_ERROR("vkCreateGraphicsPipelines", vk_result, "");
        return _bs_convertVulkanResult(vk_result);
    }

    pipeline->name = _bs_stringF(pipeline->name, BS_PRINT_COLOR("%" PRIx64, BS_PRINT_BLUE_BRIGHT), pipeline->hash);
    bsi_nameHandleN(pipeline->vk_pipeline, VK_OBJECT_TYPE_PIPELINE, pipeline->name->value, pipeline->name->len);

    char* vs_name = vs ? vs->resource->name : NULL;
    char* fs_name = fs ? fs->resource->name : NULL;
    _bs_infoF(BS_PRINT_COLOR("%" PRIx64, BS_PRINT_BLUE_BRIGHT) BS_PRINT_COLOR(" %s", BS_PRINT_CYAN) " -> " BS_PRINT_COLOR("%s", BS_PRINT_CYAN),
        pipeline->hash,
        vs_name,
        fs_name);

    return BS_RESULT_OK;
}



  /*==============================================================================
   * Ray Tracing
   *============================================================================*/

static inline VkRayTracingShaderGroupCreateInfoKHR _bs_shaderGroup(VkRayTracingShaderGroupTypeKHR type, bs_U32 general_id, bs_U32 closest_hit_id) {
    return (VkRayTracingShaderGroupCreateInfoKHR) {
        .sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR,
        .type = type,
        .generalShader = general_id,
        .closestHitShader = closest_hit_id,
        .anyHitShader = VK_SHADER_UNUSED_KHR,
        .intersectionShader = VK_SHADER_UNUSED_KHR,
    };
}

BSAPI bs_Result _bs_rayTracingPipeline(bs_Queue* queue, bs_RayTracePipelineHash* pipeline_hash, bs_Pipeline** out) {
    VkResult vk_result;
    bs_Result bs_result;

    bs_U64 hash = _bs_hash(pipeline_hash, sizeof(bs_RayTracePipelineHash));

    bs_U32 bind_sets = 0;
    for (int i = 0; i < pipeline_hash->ray_tracer->groups_count; i++)
        bind_sets |= pipeline_hash->ray_tracer->_[i].shader->bind_sets;
    
    bs_Pipeline init = {
        .shaders_count = 5,
        .bind_sets = bind_sets,
        .hash = hash,
    };

   // existing->_[0].shader = pipeline_hash->ray_gen_shader;
   // existing->_[1].shader = pipeline_hash->closest_hit_shader;
   // existing->_[2].shader = pipeline_hash->miss_shader;
   // existing->_[3].shader = pipeline_hash->intersection_shader;
   // existing->_[4].shader = pipeline_hash->any_hit_shader;

    bool already_exists = false;
    bs_Pipeline* pipeline = *out = _bs_preparePipeline(BS_PIPELINE_RAY_TRACE, hash, init, &already_exists);
    if (already_exists)
        return BS_RESULT_OK;

    bs_result = _bs_createPipelineLayout(pipeline);
    if (bs_result != BS_RESULT_OK)
        return bs_result;
    
    VkPipelineShaderStageCreateInfo stages[5] = { 0 };
    VkRayTracingShaderGroupCreateInfoKHR shader_groups[5] = { 0 };
    int count = pipeline_hash->ray_tracer->groups_count;
    for (int i = 0; i < count; i++) {
        shader_groups[i] = _bs_shaderGroup(VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR, i, VK_SHADER_UNUSED_KHR);
        stages[i] = _bs_shaderStage(pipeline_hash->ray_tracer->_[i].shader, &pipeline->bind_sets, pipeline_hash->ray_tracer->_[i].shader->type);
    }

    VkRayTracingPipelineCreateInfoKHR ci = {
        .sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR,
        .stageCount = count,
        .pStages = stages,
        .groupCount = count,
        .pGroups = shader_groups,
        .maxPipelineRayRecursionDepth = 1,
        .layout = pipeline->vk_layout,
    };

    bs_result = _bs_convertVulkanResult(_bs_procs_.vkCreateRayTracingPipelinesKHR(
        _bs_instance_->device, 
        NULL, 
        NULL, 
        1, 
        &ci, 
        NULL, 
        &pipeline->vk_pipeline)
    );

    if (bs_result != BS_RESULT_OK) {
        _bs_destroyPipeline(pipeline);
        return bs_result;
    }

    const char* blue = (_bs_args_.color_log ? BS_PRINT_BLUE_BRIGHT : "");
    const char* cyan = (_bs_args_.color_log ? BS_PRINT_CYAN : "");
    const char* reset = (_bs_args_.color_log ? BS_PRINT_RESET : "");

    _bs_infoF("%s%" PRIx64 "%s", blue, pipeline->hash, reset);

    /**
     Binding table
     */
    bs_RayTracer* tracer = pipeline_hash->ray_tracer;

    tracer->record_size = _bs_alignUp(_bs_props_.shader_group_handle_size, _bs_props_.shader_group_base_alignment);
    bs_U32 buffer_size = tracer->groups_count * tracer->record_size;

    char* shader_handle_storage = _bs_malloc(buffer_size);
    _bs_procs_.vkGetRayTracingShaderGroupHandlesKHR(_bs_instance_->device, pipeline->vk_pipeline, 0, tracer->groups_count, buffer_size, shader_handle_storage);

    pipeline->binding_table = BS_BUFFER(-1, 0, 0);

    bs_result = _bs_buffer(pipeline->binding_table, buffer_size,
        VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0);
    if (bs_result != BS_RESULT_OK)
        return bs_result;

    bs_result = _bs_mapBuffer(pipeline->binding_table, BS_U32_MAX);
    if (bs_result != BS_RESULT_OK)
        return bs_result;

    char* binding_table_data = _bs_bufferMap(pipeline->binding_table);

    for (int i = 0; i < tracer->groups_count; i++) {
        memcpy(binding_table_data, shader_handle_storage + i * _bs_props_.shader_group_handle_size, _bs_props_.shader_group_handle_size);
        binding_table_data += tracer->record_size;
    }

    _bs_free(shader_handle_storage);

    return BS_RESULT_OK;
}