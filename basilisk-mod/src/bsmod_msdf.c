
/**

 This code is derived from msdfgl by nyyManni

 ---

 Copyright (c) 2019 Henrik Nyman

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <bsmod_internal.h>
#include <bsmod_cache.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftimage.h>
#include <freetype/ftoutln.h>

typedef struct msdfgl_index_entry {
    float offset_x;
    float offset_y;
    float size_x;
    float size_y;
    float bearing_x;
    float bearing_y;
    float glyph_width;
    float glyph_height;
} msdfgl_index_entry;

struct __glyph_data_ctx {
    int meta_index;
    char* meta_buffer;

    vec2* segment;
    int nsegments_index;
};

struct __glyph_len_ctx {
    int meta_size;
    int data_size;
};

enum Color {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7
};

#define SERIALIZER_SCALE 64.0f

void switch_color(enum Color* color, unsigned long long* seed, enum Color* _banned) {
    enum Color banned = _banned ? *_banned : BLACK;
    enum Color combined = (*color & banned);

    if (combined == RED || combined == GREEN || combined == BLUE) {
        *color = combined ^ WHITE;
        return;
    }
    if (*color == BLACK || *color == WHITE) {
        static const enum Color start[3] = { CYAN, MAGENTA, YELLOW };
        *color = start[*seed % 3];
        *seed /= 3;
        return;
    }
    int shifted = *color << (1 + (*seed & 1));
    *color = (shifted | shifted >> 3) & WHITE;
    *seed >>= 1;
}

static int __add_contour_size(const FT_Vector* to, void* user) {
    struct __glyph_len_ctx* ctx = (struct __glyph_len_ctx*)user;
    ctx->data_size += 1;
    ctx->meta_size += 2; /* winding + nsegments */
    return 0;
}
static int __add_linear_size(const FT_Vector* to, void* user) {
    struct __glyph_len_ctx* ctx = (struct __glyph_len_ctx*)user;
    ctx->data_size += 1;
    ctx->meta_size += 2; /* color + npoints */
    return 0;
}
static int __add_quad_size(const FT_Vector* control, const FT_Vector* to, void* user) {
    struct __glyph_len_ctx* ctx = (struct __glyph_len_ctx*)user;
    ctx->data_size += 2;
    ctx->meta_size += 2; /* color + npoints */
    return 0;
}
static int __add_cubic_size(const FT_Vector* control1, const FT_Vector* control2,
    const FT_Vector* to, void* s) {
    fprintf(stderr, "Cubic segments not supported\n");
    return -1;
}

static int __add_contour(const FT_Vector* to, void* user) {
    struct __glyph_data_ctx* ctx = (struct __glyph_data_ctx*)user;

    ctx->segment += 1;  /* Start contour on a fresh glyph. */

    ctx->segment[0].x = to->x / SERIALIZER_SCALE;
    ctx->segment[0].y = to->y / SERIALIZER_SCALE;

    ctx->meta_buffer[0] += 1;                /* Increase the number of contours. */
    ctx->meta_buffer[ctx->meta_index++] = 0; /* Set winding to zero */

    ctx->nsegments_index = ctx->meta_index++;
    ctx->meta_buffer[ctx->nsegments_index] = 0;

    return 0;
}

static int __add_linear(const FT_Vector* to, void* user) {
    struct __glyph_data_ctx* ctx = (struct __glyph_data_ctx*)user;
    ctx->segment[1].x = to->x / SERIALIZER_SCALE;
    ctx->segment[1].y = to->y / SERIALIZER_SCALE;

    /* Some glyphs contain zero-dimensional segments, ignore those. */
    if (ctx->segment[1].x == ctx->segment[0].x && ctx->segment[1].y == ctx->segment[0].y)
        return 0;

    ctx->segment += 1;

    ctx->meta_buffer[ctx->meta_index++] = 0; /* Set color to 0 */
    ctx->meta_buffer[ctx->meta_index++] = 2;
    ctx->meta_buffer[ctx->nsegments_index]++;
    return 0;
}

static int __add_quad(const FT_Vector* control, const FT_Vector* to, void* user) {
    struct __glyph_data_ctx* ctx = (struct __glyph_data_ctx*)user;

    ctx->segment[1].x = control->x / SERIALIZER_SCALE;
    ctx->segment[1].y = control->y / SERIALIZER_SCALE;
    ctx->segment[2].x = to->x / SERIALIZER_SCALE;
    ctx->segment[2].y = to->y / SERIALIZER_SCALE;

    /* Some glyphs contain "bugs", where a quad segment is actually a linear
       segment with a double point. Treat it as a linear segment. */
    if ((ctx->segment[1].x == ctx->segment[0].x && ctx->segment[1].y == ctx->segment[0].y)
        || (ctx->segment[2].x == ctx->segment[1].x && ctx->segment[2].y == ctx->segment[1].y))
        return __add_linear(to, user);

    ctx->segment += 2;

    ctx->meta_buffer[ctx->meta_index++] = 0; /* Set color to 0 */
    ctx->meta_buffer[ctx->meta_index++] = 3;
    ctx->meta_buffer[ctx->nsegments_index]++;
    return 0;
}

static inline vec2 mix(const vec2 a, const vec2 b, float weight) {
    return (vec2) { a.x* (1.0f - weight) + b.x * weight, a.y* (1.0f - weight) + b.y * weight };
}

static inline vec2 subt(vec2 p1, vec2 p2) { return (vec2) { p1.x - p2.x, p1.y - p2.y }; }
static inline float length(const vec2 v) { return (float)sqrt(v.x * v.x + v.y * v.y); }

static inline vec2 divide(const vec2 v, float f) { return (vec2) { v.x / f, v.y / f }; }

static inline float cross(vec2 a, vec2 b) { return a.x * b.y - a.y * b.x; }
static inline float dot(vec2 a, vec2 b) { return a.x * b.x + a.y * b.y; }

static bool is_corner(const vec2 a, const vec2 b, float cross_threshold) {
    return dot(a, b) <= 0 || fabs(cross(a, b)) > cross_threshold;
}

static inline vec2 normalize(vec2 v) { return divide(v, length(v)); }

static inline vec2 segment_direction(const vec2* points, int npoints, float param) {
    return mix(subt(points[1], points[0]), subt(points[npoints - 1], points[npoints - 2]),
        param);
}

static inline vec2 segment_point(const vec2* points, int npoints, float param) {
    return mix(mix(points[0], points[1], param),
        mix(points[npoints - 2], points[npoints - 1], param), param);
}

static inline float shoelace(const vec2 a, const vec2 b) {
    return (b.x - a.x) * (a.y + b.y);
}



  /*==============================================================================
   * Serializer
   *============================================================================*/

int msdfgl_serialize_glyph(FT_Face face, int code, char* meta_buffer, float* point_buffer) {

    if (FT_Load_Char(face, code, FT_LOAD_NO_SCALE))
        return -1;

    FT_Outline_Funcs fns;
    fns.shift = 0;
    fns.delta = 0;
    fns.move_to = __add_contour;
    fns.line_to = __add_linear;
    fns.conic_to = __add_quad;
    fns.cubic_to = 0;

    struct __glyph_data_ctx ctx;
    ctx.meta_buffer = meta_buffer;
    ctx.meta_index = 1;
    ctx.meta_buffer[0] = 0;
    // Start 1 before the actual buffer. The pointer is moved in the move_to callback.
    // FT_Outline_Decompose does not have a callback for finishing a contour.
    ctx.segment = ((vec2*)&point_buffer[0]) - 1;

    if (FT_Outline_Decompose(&face->glyph->outline, &fns, &ctx))
        return -1;

    // Calculate windings.
    int meta_index = 0;
    vec2* point_ptr = (vec2*)&point_buffer[0];

    int ncontours = meta_buffer[meta_index++];
    for (int i = 0; i < ncontours; ++i) {
        int winding_index = meta_index++;
        int nsegments = meta_buffer[meta_index++];

        float total = 0;
        if (nsegments == 1) {
            int npoints = meta_buffer[meta_index + 1];
            vec2 a = segment_point(point_ptr, npoints, 0);
            vec2 b = segment_point(point_ptr, npoints, 1 / 3.0f);
            vec2 c = segment_point(point_ptr, npoints, 2 / 3.0f);
            total += shoelace(a, b);
            total += shoelace(b, c);
            total += shoelace(c, a);

            point_ptr += npoints - 1;
            meta_index += 2;

        }
        else if (nsegments == 2) {
            int npoints = meta_buffer[meta_index + 1];
            vec2 a = segment_point(point_ptr, npoints, 0);
            vec2 b = segment_point(point_ptr, npoints, 0.5);
            point_ptr += npoints - 1;
            meta_index += 2;
            npoints = meta_buffer[meta_index + 1];
            vec2 c = segment_point(point_ptr, npoints, 0);
            vec2 d = segment_point(point_ptr, npoints, 0.5);
            total += shoelace(a, b);
            total += shoelace(b, c);
            total += shoelace(c, d);
            total += shoelace(d, a);

            point_ptr += npoints - 1;
            meta_index += 2;
        }
        else {
            int prev_npoints = meta_buffer[meta_index + 2 * (nsegments - 2) + 1];
            vec2* prev_ptr = point_ptr;
            for (int j = 0; j < nsegments - 1; ++j) {
                int _npoints = meta_buffer[meta_index + 2 * j + 1];
                prev_ptr += (_npoints - 1);
            }
            vec2 prev = segment_point(prev_ptr, prev_npoints, 0);

            for (int j = 0; j < nsegments; ++j) {
                meta_index++; // Color, leave empty here.
                int npoints = meta_buffer[meta_index++];

                vec2 cur = segment_point(point_ptr, npoints, 0);

                total += shoelace(prev, cur);
                point_ptr += (npoints - 1);
                prev = cur;
            }
        }
        point_ptr += 1;
        meta_buffer[winding_index] = total > 0 ? 2 : 0;
    }

    // Calculate coloring
    float cross_threshold = (float)sin(3.0);
    unsigned long long seed = 0;

    meta_index = 0;
    point_ptr = (vec2*)&point_buffer[0];

    int corners[30];
    int len_corners = 0;

    ncontours = meta_buffer[meta_index++];
    for (int i = 0; i < ncontours; ++i) {
        meta_index++; // Winding 
        int nsegments = meta_buffer[meta_index++];
        int _meta = meta_index;
        vec2* _point = point_ptr;

        len_corners = 0; // clear

        if (nsegments) {
            int prev_npoints = meta_buffer[meta_index + 2 * (nsegments - 2) + 1];
            vec2* prev_ptr = point_ptr;
            for (int j = 0; j < nsegments - 1; ++j)
                prev_ptr += (meta_buffer[meta_index + 2 * j + 1] - 1);
            vec2 prev_direction = segment_direction(prev_ptr, prev_npoints, 1);
            int index = 0;
            vec2* cur_points = point_ptr;
            for (int j = 0; j < nsegments; ++j, ++index) {
                meta_index++; // Color, leave empty here.
                int npoints = meta_buffer[meta_index++];

                vec2 cur_direction = segment_direction(cur_points, npoints, 0.0);
                vec2 new_prev_direction = segment_direction(cur_points, npoints, 1.0);

                if (is_corner(normalize(prev_direction), normalize(cur_direction),
                    cross_threshold))
                    corners[len_corners++] = index;
                cur_points += (npoints - 1);
                prev_direction = new_prev_direction;
            }
        }

        // Restore state
        meta_index = _meta;
        point_ptr = _point;

        if (!len_corners) {
            // Smooth contour
            for (int j = 0; j < nsegments; ++j) {
                meta_buffer[meta_index++] = WHITE;
                meta_index++; // npoints
            }
        }
        else if (len_corners == 1) {
            // Teardrop
            enum Color colors[3] = { WHITE, WHITE };
            switch_color(&colors[0], &seed, NULL);
            colors[2] = colors[0];
            switch_color(&colors[2], &seed, NULL);

            int corner = corners[0];
            if (nsegments >= 3) {
                int m = nsegments;
                for (int i = 0; i < m; ++i) {
                    enum Color c =
                        (colors + 1)[(int)(3 + 2.875 * i / (m - 1) - 1.4375 + .5) - 3];
                    meta_buffer[meta_index + 2 * ((corner + i) % m)] = (char)c;
                }
            }
            else if (nsegments >= 1) {
                // TODO: whoa, split in thirds and stuff
                fprintf(stderr, "Non-supported shape\n");
            }
        }
        else {
            // Multiple corners.
            int corner_count = len_corners;
            int spline = 0;
            int start = corners[0];
            int m = nsegments;
            enum Color color = WHITE;
            switch_color(&color, &seed, NULL);
            enum Color initial_color = color;
            for (int i = 0; i < m; ++i) {
                int index = (start + i) % m;

                if (spline + 1 < corner_count && corners[spline + 1] == index) {
                    ++spline;
                    enum Color banned =
                        (enum Color)((spline == corner_count - 1) * initial_color);
                    switch_color(&color, &seed, &banned);
                }
                meta_buffer[meta_index + 2 * index] = (char)color;
            }
        }

        // Restore state
        meta_index = _meta;
        point_ptr = _point;

        for (int j = 0; j < nsegments; ++j) {
            meta_index++;
            point_ptr += (meta_buffer[meta_index++] - 1);
        }
        point_ptr += 1;
    }

    return 0;
}



  /*==============================================================================
   * Font Packing
   *============================================================================*/

/* We need two rounds of decomposing, the first one will just figure out
   how much space we need to serialize the glyph, and the second one
   serializes it and generates colour mapping for the segments. */
int msdfgl_glyph_buffer_size(FT_Face face, int code, size_t* meta_size,
    size_t* point_size) {

    if (FT_Load_Char(face, code, FT_LOAD_NO_SCALE))
        return -1;

    FT_Outline_Funcs fns;
    fns.shift = 0;
    fns.delta = 0;
    fns.move_to = __add_contour_size;
    fns.line_to = __add_linear_size;
    fns.conic_to = __add_quad_size;
    fns.cubic_to = __add_cubic_size;
    struct __glyph_len_ctx ctx = { 1, 0 };
    if (FT_Outline_Decompose(&face->glyph->outline, &fns, &ctx))
        return -1;

    *meta_size = ctx.meta_size;
    *point_size = ctx.data_size * 2 * sizeof(float);

    return 0;
}

static void _bsmod_renderGlyphAtlas() {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    bs_Queue* queue = bs_fetch(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS_RASTERIZATION)->queue;
    bs_Renderer* renderer = bs_fetch(BSMOD_RENDERERS, BSMOD_RENDERER_MSDF)->renderer;
    bs_Batch* msdf_glyphs = bs_fetch(BSMOD_BATCHES, BSMOD_BATCH_MSDF_GLYPHS)->batch;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsgfx_quad_instanced();
    hash.shaders[1] = $fs_bsgfx_msdf_glyph();

    //hash.shaders[0] = $vs_bsgfx_msdf_glyph();
    //hash.shaders[1] = $fs_bsgfx_msdf_glyph();

    bs_RendererScope scope = {
        .renderer = renderer,
        .queue = queue,
    };

    if (bs_pipeline(&scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        const int width = 74;

        const bs_ivec2 render_size = { width, width };
        const bs_ivec2 output_size = { width, width };

        bs_mat4 proj, view, camera;
        bs_orthographic(0, render_size.x, 0, render_size.y, -500.0, 500.0, &proj);
        bs_lookAt(&BS_V3(0, 0, 1), &BS_V3(0, 0, 0), &BS_V3(0, 1, 0), &view);

        bs_m4Mul(&proj, &view, &camera);

        struct {
            bs_mat4 camera;
        } push_const = {
            .camera = camera,
        };

        _bsmod_beginRasterize(render_size, output_size);

        int subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI];

        bs_mat4x3 matrix = bsgfx_matrix(BS_V3(0, 0, 0), BS_V3(width, width, 0));
        int instance = bsgfx_instanceQuad(
            subtype,
            matrix,
            BS_V4(0, 0, 1, 1),
            0, 0, 0);

        //int instance = bsgfx_instancePrimitive(sphere_subtype, BS_MAT4_IDENTITY, 0, 0, 0);
        _bsmod_rasterizeInstance(queue, hash, subtype, instance, 0, "test", render_size.x, render_size.y, sizeof(push_const), &push_const);

        _bsmod_endRasterize(queue);
    }
}

void _bsmod_generateGlyphsMSDF() {
    bs_Object* queue = bs_fetch(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS_RASTERIZATION);
    bs_Object* renderer = bs_fetch(BSMOD_RENDERERS, BSMOD_RENDERER_MSDF);
    bs_Object* msdf_glyphs = bs_fetch(BSMOD_BATCHES, BSMOD_BATCH_MSDF_GLYPHS);

    if (bs_resetQueue(queue->queue) == BS_RESULT_OK) {
        _bsmod_renderGlyphAtlas();
        bs_pushQueue(queue->queue, 0, NULL);
    }

    //_bsmod_pollRasterizer();
}

BSMODAPI void _bsmod_rasterizeGlyphAtlas() {

}

void _bsmod_loadMsdfResources() {
    bs_Result result;

    bs_Object* queue = BS_QUEUE(BSMOD_QUEUES, BSMOD_QUEUE_MSDF, 0);
    bs_Object* renderer = BS_RENDERER(BSMOD_RENDERERS, BSMOD_RENDERER_MSDF, 0);
    bs_Object* msdf_glyphs = BS_BATCH(BSMOD_BATCHES, BSMOD_BATCH_MSDF_GLYPHS, 0);

    bs_batch(msdf_glyphs, sizeof(int), $vs_bsgfx_msdf_glyph(), 0);

    result = bs_queue(queue, BS_QUEUE_GRAPHICS_BIT);
    if (result != BS_RESULT_OK) {
        return;
    }

    result = bs_renderer(renderer, 0);

    if (result == BS_RESULT_OK) {
        bs_ivec2 resolution = bs_resolution();
         
        //bs_Object* depth = BS_IMAGE(BSMOD_IMAGES, BSMOD_IMAGE_DEPTH_3D, 0);
        //bs_image(depth, resolution, 0, BS_FORMAT_D32_SFLOAT_S8_UINT, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_DST_BIT);

        bs_Object* color = BS_IMAGE(BSMOD_IMAGES, BSMOD_IMAGE_COLOR, 0);

        bs_image(color, resolution, 0, BS_FORMAT_R8G8B8A8_UNORM, BS_IMAGE_ATTACHMENT_BIT | BS_IMAGE_USAGE_TRANSFER_SRC_BIT);

        bs_output(renderer->renderer, (bs_Output) {
            .subpass = 0,
            .image = bs_context()->swapchain_image->image,
            .load_op = BS_ATTACHMENT_LOAD_OP_LOAD,
            .store_op = BS_ATTACHMENT_STORE_OP_STORE,
            .old_layout = BS_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
            .new_layout = BS_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        });

        bs_dependency(renderer->renderer, -1, 0, BS_DEPENDENCY_BY_REGION_BIT,
            BS_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
            BS_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | BS_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
            BS_ACCESS_MEMORY_READ_BIT,
            BS_ACCESS_COLOR_ATTACHMENT_READ_BIT | BS_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | BS_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT);

      //  bs_renderPass(renderer->renderer);
        bs_framebuffer(renderer->renderer, resolution);
    }
}

bs_Result _msdfgl_generate_glyphs_internal(bsgfx_Font* font2, FT_Face face, int32_t start, int32_t end) {

    int retval = -2;

    int nrender = end - start;

    if (nrender <= 0)
        return -1;

    //if (!atlas->nglyphs && range && !start) {
    //    /* We can generate an optimized lookup for the atlas index. */
    //    font->_direct_lookup_upper_limit = end;
    //}
    size_t* meta_sizes = NULL, * point_sizes = NULL;
    msdfgl_index_entry* atlas_index = NULL;

    /* We will start with a square texture. */
    //int new_texture_height = atlas->texture_height ? atlas->texture_height : 1;
    //int new_index_size = atlas->nallocated ? atlas->nallocated : 1;

    /* Calculate the amount of memory needed on the GPU.*/
    meta_sizes = bs_alloca(nrender * sizeof(size_t));
    point_sizes = bs_alloca(nrender * sizeof(size_t));

    /* Amount of new memory needed for the index. */
    //size_t index_size = nrender * sizeof(msdfgl_index_entry);
    //atlas_index = bs_calloc(1, index_size);

    size_t meta_size_sum = 0, point_size_sum = 0;
    for (size_t i = 0; (int)i < (int)nrender; i++) {
        int index = start + (int)i;
        msdfgl_glyph_buffer_size(face, index, &meta_sizes[i], &point_sizes[i]);

        meta_size_sum += meta_sizes[i];
        point_size_sum += point_sizes[i];
    }

    /* Allocate the calculated amount. */
    //point_data = bs_calloc(point_size_sum, 1);
    //metadata = bs_calloc(meta_size_sum, 1);

    bs_Object* point_data_object = BS_BUFFER(-1, -1, 0);
    bs_Object* metadata_object = BS_BUFFER(-1, -1, 0);

    bs_buffer(
        point_data_object, 
        point_size_sum, 
        BS_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
        BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0);

    bs_buffer(
        metadata_object,
        point_size_sum,
        BS_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
        BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0);

    bs_mapBuffer(point_data_object->buffer, BS_U32_MAX);
    bs_mapBuffer(metadata_object->buffer, BS_U32_MAX);


    bs_bindBuffer(BSMOD_SET_MSDF_BITMAP, BSMOD_BINDING_MSDF_BITMAP, point_data_object->buffer);
    bs_bindBuffer(BSMOD_BINDING_MSDF_INDEX, BSMOD_BINDING_MSDF_INDEX, metadata_object->buffer);

    void* point_data = point_data_object->buffer->_->data;
    void* metadata = metadata_object->buffer->_->data;

    /* Serialize the glyphs into RAM. */
    char* meta_ptr = metadata;
    char* point_ptr = point_data;
    for (size_t i = 0; (int)i < (int)nrender; i++) {
        float buffer_width, buffer_height;

        int index = start + (int)i;
        msdfgl_serialize_glyph(face, index, meta_ptr, (float*)point_ptr);

       // msdfgl_map_item_t* m = msdfgl_map_insert(&font->character_index, index);
       // m->index = atlas->nglyphs + i;
       // m->advance[0] = (float)font->face->glyph->metrics.horiAdvance;
       // m->advance[1] = (float)font->face->glyph->metrics.vertAdvance;

        // If we are generating a range starting from 0, we reuse the NULL
        // character bitmap for all control characters.
        //if (range && start == 0 && index != 0 && _msdfgl_is_control(index)) {
        //    atlas_index[i] = atlas_index[0];
        //    while ((int)(atlas->nglyphs + i) > new_index_size)
        //        new_index_size *= 2;
        //    continue;
        //}

//        buffer_width = face->glyph->metrics.width / SERIALIZER_SCALE + font->range;
//        buffer_height = face->glyph->metrics.height / SERIALIZER_SCALE + font->range;
//        buffer_width *= font->scale;
//        buffer_height *= font->scale;
//
        meta_ptr += meta_sizes[i];
        point_ptr += point_sizes[i];

//        if (atlas->offset_x + buffer_width > atlas->texture_width) {
//            atlas->offset_y += (atlas->y_increment + atlas->padding);
//            atlas->offset_x = 1;
//            atlas->y_increment = 0;
//        }
//        atlas->y_increment = (size_t)buffer_height > atlas->y_increment
//            ? (size_t)buffer_height
//            : atlas->y_increment;

        //atlas_index[i].offset_x = (GLfloat)atlas->offset_x;
        //atlas_index[i].offset_y = (GLfloat)atlas->offset_y;
        //atlas_index[i].size_x = buffer_width;
        //atlas_index[i].size_y = buffer_height;
        //atlas_index[i].bearing_x = (GLfloat)font->face->glyph->metrics.horiBearingX;
        //atlas_index[i].bearing_y = (GLfloat)font->face->glyph->metrics.horiBearingY;
        //atlas_index[i].glyph_width = (GLfloat)font->face->glyph->metrics.width;
        //atlas_index[i].glyph_height = (GLfloat)font->face->glyph->metrics.height;

//        atlas->offset_x += (size_t)buffer_width + atlas->padding;

        //while ((atlas->offset_y + buffer_height) > new_texture_height) {
        //    new_texture_height *= 2;
        //}
        //if (new_texture_height > font->context->_max_texture_size) {
        //    goto error;
        //}
        //while ((int)(atlas->nglyphs + i) >= new_index_size) {
        //    new_index_size *= 2;
        //}
    }

    /* Allocate and fill the buffers on GPU. */
    /*
    glBindBuffer(GL_ARRAY_BUFFER, font->_meta_input_buffer);
    glBufferData(GL_ARRAY_BUFFER, meta_size_sum, metadata, GL_DYNAMIC_READ);

    glBindBuffer(GL_ARRAY_BUFFER, font->_point_input_buffer);
    glBufferData(GL_ARRAY_BUFFER, point_size_sum, point_data, GL_DYNAMIC_READ);

    if ((int)atlas->nallocated == new_index_size) {
        glBindBuffer(GL_ARRAY_BUFFER, atlas->index_buffer);
    }
    else {
        GLuint new_buffer;
        glGenBuffers(1, &new_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, new_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(msdfgl_index_entry) * new_index_size, 0,
            GL_DYNAMIC_READ);
        if (glGetError() == GL_OUT_OF_MEMORY) {
            glDeleteBuffers(1, &new_buffer);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            goto error;
        }
        if (atlas->nglyphs) {
            glBindBuffer(GL_COPY_READ_BUFFER, atlas->index_buffer);
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_ARRAY_BUFFER, 0, 0,
                atlas->nglyphs * sizeof(msdfgl_index_entry));
            glBindBuffer(GL_COPY_READ_BUFFER, 0);
        }
        atlas->nallocated = new_index_size;
        glDeleteBuffers(1, &atlas->index_buffer);
        atlas->index_buffer = new_buffer;
    }
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(msdfgl_index_entry) * atlas->nglyphs,
        index_size, atlas_index);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    */

    /* Link sampler textures to the buffers. */
    /*
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_BUFFER, font->_meta_input_texture);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_R8UI, font->_meta_input_buffer);
    glBindTexture(GL_TEXTURE_BUFFER, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_BUFFER, font->_point_input_texture);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, font->_point_input_buffer);
    glBindTexture(GL_TEXTURE_BUFFER, 0);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_BUFFER, atlas->index_texture);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, atlas->index_buffer);
    glBindTexture(GL_TEXTURE_BUFFER, 0);

    glActiveTexture(GL_TEXTURE0);
    */

    /* Generate the atlas texture and bind it as the framebuffer. */
    /*
    if (atlas->texture_height == new_texture_height) {
        // No need to extend the texture.
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, atlas->atlas_framebuffer);
        glBindTexture(GL_TEXTURE_2D, atlas->atlas_texture);
        glViewport(0, 0, atlas->texture_width, atlas->texture_height);
    }
    else {
        GLuint new_texture;
        GLuint new_framebuffer;
        glGenTextures(1, &new_texture);
        glGenFramebuffers(1, &new_framebuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, new_framebuffer);

        glBindTexture(GL_TEXTURE_2D, new_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, atlas->texture_width,
            new_texture_height, 0, GL_RGBA, GL_FLOAT, NULL);

        if (glGetError() == GL_OUT_OF_MEMORY) {
            // Buffer size too big, are you trying to type Klingon?
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glDeleteFramebuffers(1, &new_framebuffer);
            glDeleteTextures(1, &new_texture);
            goto error;
        }

        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
            new_texture, 0);
        glViewport(0, 0, atlas->texture_width, new_texture_height);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        if (atlas->texture_height) {
            // Old texture had data -> copy.
            glBindFramebuffer(GL_READ_FRAMEBUFFER, atlas->atlas_framebuffer);
            glBlitFramebuffer(0, 0, atlas->texture_width, atlas->texture_height, 0, 0,
                atlas->texture_width, atlas->texture_height,
                GL_COLOR_BUFFER_BIT, GL_NEAREST);
            glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        }

        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        atlas->texture_height = new_texture_height;
        glDeleteTextures(1, &atlas->atlas_texture);
        atlas->atlas_texture = new_texture;
        glDeleteFramebuffers(1, &atlas->atlas_framebuffer);
        atlas->atlas_framebuffer = new_framebuffer;
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    GLfloat framebuffer_projection[4][4];
    _msdfgl_ortho(0, (GLfloat)atlas->texture_width, 0, (GLfloat)atlas->texture_height,
        -1.0, 1.0, framebuffer_projection);
    _msdfgl_ortho(-(GLfloat)atlas->texture_width, (GLfloat)atlas->texture_width,
        -(GLfloat)atlas->texture_height, (GLfloat)atlas->texture_height, -1.0,
        1.0, atlas->projection);

    glUseProgram(ctx->gen_shader);
    glUniform1i(ctx->metadata_uniform, 0);
    glUniform1i(ctx->point_data_uniform, 1);

    glUniformMatrix4fv(ctx->_atlas_projection_uniform, 1, GL_FALSE,
        (GLfloat*)framebuffer_projection);

    glUniform2f(ctx->_scale_uniform, font->scale, font->scale);
    glUniform1f(ctx->_range_uniform, font->range);
    glUniform1i(ctx->_meta_offset_uniform, 0);
    glUniform1i(ctx->_point_offset_uniform, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        fprintf(stderr, "msdfgl: framebuffer incomplete: %x\n",
            glCheckFramebufferStatus(GL_FRAMEBUFFER));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_BUFFER, font->_meta_input_texture);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_BUFFER, font->_point_input_texture);

    glBindVertexArray(ctx->bbox_vao);
    glBindBuffer(GL_ARRAY_BUFFER, ctx->bbox_vbo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    int meta_offset = 0;
    int point_offset = 0;
    for (int i = 0; i < nrender; ++i) {
        if (range && start == 0 && i != 0 && _msdfgl_is_control(i))
            continue;

        msdfgl_index_entry g = atlas_index[i];
        float w = g.size_x;
        float h = g.size_y;
        GLfloat bounding_box[] = { 0, 0, w, 0, 0, h, 0, h, w, 0, w, h };
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bounding_box), bounding_box);

        glUniform2f(
            ctx->_translate_uniform, -g.bearing_x / SERIALIZER_SCALE + font->range / 2.0f,
            (g.glyph_height - g.bearing_y) / SERIALIZER_SCALE + font->range / 2.0f);

        glUniform2f(ctx->_texture_offset_uniform, g.offset_x, g.offset_y);
        glUniform1i(ctx->_meta_offset_uniform, meta_offset);
        glUniform1i(ctx->_point_offset_uniform, point_offset / (2 * sizeof(GLfloat)));
        glUniform1f(ctx->_glyph_height_uniform, g.size_y);

        // No need for draw call if there are no contours
        if (((unsigned char*)metadata)[meta_offset])
            glDrawArrays(GL_TRIANGLES, 0, 6);

        meta_offset += meta_sizes[i];
        point_offset += point_sizes[i];
    }

    glDisableVertexAttribArray(0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_BUFFER, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_BUFFER, 0);

    glUseProgram(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    atlas->nglyphs += nrender;
    retval = nrender;

error:
    if (meta_sizes)
        free(meta_sizes);
    if (point_sizes)
        free(point_sizes);
    if (atlas_index)
        free(atlas_index);
    if (point_data)
        free(point_data);
    if (metadata)
        free(metadata);

    glViewport(original_viewport[0], original_viewport[1], original_viewport[2], original_viewport[3]);
    */

    return BS_RESULT_OK;
}
