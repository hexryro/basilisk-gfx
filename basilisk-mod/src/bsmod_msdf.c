
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

#include <windows.h>

#ifdef RENDERDOC_PATH
#include RENDERDOC_PATH
#endif

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

int msdfgl_serialize_glyph(FT_Face face, bs_U32 codepoint, char* meta_buffer, float* point_buffer) {
    FT_UInt glyph_id = FT_Get_Char_Index(face, codepoint);

    if (glyph_id == 0)
        return -1;

    if (FT_Load_Glyph(face, glyph_id, FT_LOAD_NO_SCALE))
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

typedef struct {
    bs_mat4 camera;
    bs_vec2 offset;
    bs_vec2 translate;
    bs_vec2 scale;
    float range;
    int meta_offset;
    int point_offset;
    float glyph_height;
} bsmod_MSDFPushConstant;

static void _bsmod_renderGlyphAtlas(bsmod_MSDFPushConstant push_const) {
    bs_PipelineHash hash;
    bs_Pipeline* pipeline;

    bs_Queue* queue = bs_fetch(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS_RASTERIZATION)->queue;
    bs_Renderer* renderer = bs_fetch(BSMOD_RENDERERS, BSMOD_RENDERER_MSDF)->renderer;
    bs_Batch* msdf_glyphs = bs_fetch(BSMOD_BATCHES, BSMOD_BATCH_MSDF_GLYPHS)->batch;

    hash = bsgfx_defaultPipelineHash();
    hash.shaders[0] = $vs_bsmod_tracker_quad_instanced();
    hash.shaders[1] = $fs_bsgfx_msdf_glyph();

    //hash.shaders[0] = $vs_bsgfx_msdf_glyph();
    //hash.shaders[1] = $fs_bsgfx_msdf_glyph();

    bs_RendererScope scope = {
        .renderer = renderer,
        .queue = queue,
    };

    if (bs_pipeline(&scope, queue, &hash, &pipeline) == BS_RESULT_OK) {
        const int width = 1024;
        const int height = 1024;

        const bs_ivec2 render_size = { width, height };
        const bs_ivec2 output_size = { width, height };

        bs_mat4 proj, view, camera;
        bs_orthographic(0, render_size.x, 0, render_size.y, -500.0, 500.0, &proj);
        bs_lookAt(&BS_V3(0, 0, 1), &BS_V3(0, 0, 0), &BS_V3(0, 1, 0), &view);

        bs_m4Mul(&proj, &view, &camera);
        push_const.camera = camera;

        _bsmod_beginRasterize(render_size, output_size);

        int subtype = _bsmod_subtypes_[BSMOD_SUBTYPE_TRACKER_QUAD_MSDF];

        bs_mat4x3 matrix = bsgfx_matrix(BS_V3(0, 0, 0), BS_V3(width, height, 0));
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

bs_Result _msdfgl_generate_glyphs_internal(FT_Face face, int32_t start, int32_t end);
void _bsmod_generateGlyphsMSDF() {

#ifdef RENDERDOC_PATH
    if (_bsmod_.renderdoc_device) {
        bs_logF("Starting frame capture");
        _bsmod_.renderdoc_api->StartFrameCapture(_bsmod_.renderdoc_device, NULL);
    }
#endif

    bs_Object* queue = bs_fetch(BSMOD_QUEUES, BSMOD_QUEUE_GRAPHICS_RASTERIZATION);
    bs_Object* renderer = bs_fetch(BSMOD_RENDERERS, BSMOD_RENDERER_MSDF);
    bs_Object* msdf_glyphs = bs_fetch(BSMOD_BATCHES, BSMOD_BATCH_MSDF_GLYPHS);

    FT_Error error;
    FT_Face face;
    FT_Library freetype_library = NULL;

     if (!freetype_library) {
        error = FT_Init_FreeType(&freetype_library);
        if (error) {
            BSMOD_WARN_FREETYPE_ERROR("FT_Init_FreeType", error, );
            //return _bsmod_convertFreetypeError(error);
        }
    }

    error = FT_New_Face(freetype_library, "project/fonts/segoeui.ttf", 0, &face);
    if (error) {
        BSMOD_WARN_FREETYPE_ERROR("FT_New_Face", error, );
      //  return _bsmod_convertFreetypeError(error);
    }


    if (bs_resetQueue(queue->queue) == BS_RESULT_OK) {
        _msdfgl_generate_glyphs_internal(face, 65, 66);
        bs_pushQueue(queue->queue, 0, NULL);
    }

#ifdef RENDERDOC_PATH
    if (_bsmod_.renderdoc_device) {
        bs_logF("Ending frame capture");

        bs_U32 result = _bsmod_.renderdoc_api->EndFrameCapture(_bsmod_.renderdoc_api, NULL);

        if (result != 1)
            BS_WARN("EndFrameCapture returned %d", result);
    }
#endif

    bs_stallQueue(queue->queue);
    _bsmod_pollRasterizer();
}

BSMODAPI void _bsmod_rasterizeGlyphAtlas() {

}

static inline int _msdfgl_is_control(int32_t code) {
    return (code <= 31) || (code >= 128 && code <= 159);
}

bs_Result _msdfgl_generate_glyphs_internal(FT_Face face, int32_t start, int32_t end) {

    int retval = -2;

    int nrender = end - start;

    if (nrender <= 0)
        return -1;

    const float font_scale = 4;
    const float font_range = 2;

    size_t* meta_sizes = NULL, * point_sizes = NULL;
    msdfgl_index_entry* atlas_index = NULL;

    meta_sizes = bs_alloca(nrender * sizeof(size_t));
    point_sizes = bs_alloca(nrender * sizeof(size_t));

    atlas_index = bs_alloca(nrender * sizeof(msdfgl_index_entry));

    size_t meta_size_sum = 0, point_size_sum = 0;
    for (size_t i = 0; (int)i < (int)nrender; i++) {
        int index = start + (int)i;
        msdfgl_glyph_buffer_size(face, index, &meta_sizes[i], &point_sizes[i]);

        meta_size_sum += meta_sizes[i];
        point_size_sum += point_sizes[i];
    }

    bs_Object* point_data_object = BS_BUFFER(-1, -1, 0);
    bs_Object* metadata_object = BS_BUFFER(-1, -1, 0);

    bs_buffer(
        point_data_object, 
        point_size_sum, 
        BS_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT,
        BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0);

    bs_buffer(
        metadata_object,
        meta_size_sum,
        BS_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT,
        BS_MEMORY_PROPERTY_HOST_VISIBLE_BIT | BS_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        0);

    bs_bufferView(point_data_object->buffer, BS_FORMAT_R32_SFLOAT, 0, BS_U64_MAX);
    bs_bufferView(metadata_object->buffer, BS_FORMAT_R8_UINT, 0, BS_U64_MAX);

    bs_mapBuffer(point_data_object->buffer, BS_U32_MAX);
    bs_mapBuffer(metadata_object->buffer, BS_U32_MAX);

    bs_bindBuffer(BSMOD_SET_MSDF_BITMAP, BSMOD_BINDING_MSDF_BITMAP, metadata_object->buffer);
    bs_bindBuffer(BSMOD_SET_MSDF_INDEX, BSMOD_BINDING_MSDF_INDEX, point_data_object->buffer);

    bs_pushBindings();
    bs_pushDescriptors();

    void* point_data = point_data_object->buffer->_->data;
    void* metadata = metadata_object->buffer->_->data;

    /* Serialize the glyphs into RAM. */
    char* meta_ptr = metadata;
    char* point_ptr = point_data;
    for (size_t i = 0; (int)i < (int)nrender; i++) {
        float buffer_width, buffer_height;

        int index = start + (int)i;
        msdfgl_serialize_glyph(face, index, meta_ptr, (float*)point_ptr);

        buffer_width = face->glyph->metrics.width / SERIALIZER_SCALE + font_range;
        buffer_height = face->glyph->metrics.height / SERIALIZER_SCALE + font_range;
        buffer_width *= font_scale;
        buffer_height *= font_scale;

        atlas_index[i].offset_x = 0;
        atlas_index[i].offset_y = 0;
        atlas_index[i].size_x = buffer_width;
        atlas_index[i].size_y = buffer_height;
        atlas_index[i].bearing_x = (float)face->glyph->metrics.horiBearingX;
        atlas_index[i].bearing_y = (float)face->glyph->metrics.horiBearingY;
        atlas_index[i].glyph_width = (float)face->glyph->metrics.width;
        atlas_index[i].glyph_height = (float)face->glyph->metrics.height;

        meta_ptr += meta_sizes[i];
        point_ptr += point_sizes[i];
    }

    const int atlas_width = 1024, atlas_height = 1024;

    bs_mat4 framebuffer_projection;
    bs_mat4 atlas_projection;

    bs_orthographic(0, atlas_width, 0, atlas_height, -1.0, 1.0, &framebuffer_projection);

    bs_orthographic(-atlas_width, atlas_width, -atlas_height, atlas_height, -1.0, 1.0, &atlas_projection);

    bsmod_MSDFPushConstant push_const = {
        .scale = { font_scale, font_scale},
        .range = font_range,
        .meta_offset = 0,
        .point_offset = 0,
    };

    int meta_offset = 0;
    int point_offset = 0;
    for (int i = 0; i < nrender; ++i) {
        if (end && start == 0 && i != 0 && _msdfgl_is_control(i))
            continue;

        msdfgl_index_entry g = atlas_index[i];

        push_const.translate = BS_V2(
            -g.bearing_x / SERIALIZER_SCALE + font_range / 2.0f,
            (g.glyph_height - g.bearing_y) / SERIALIZER_SCALE + font_range / 2.0f
        );
        push_const.glyph_height = g.size_y;

        push_const.meta_offset = meta_offset;
        push_const.point_offset = point_offset / (2 * sizeof(float));

        if (((unsigned char*)metadata)[meta_offset])
            _bsmod_renderGlyphAtlas(push_const);

        meta_offset += meta_sizes[i];
        point_offset += point_sizes[i];
    }

    retval = nrender;

    return BS_RESULT_OK;
}
