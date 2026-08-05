
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
  _bs_math.c

  Collection of math tools

  CGLM wrapper functions such as vector and matrix operations are 
  generated from basilisk-core.xml, cglm functions are called 
  directly from the trampoline, see generated/basilisk-core.c
  */

#include <basilisk-core.h>
#include <bs_internal.h>
#include <cglm/vec2.h>
#include <cglm/vec3.h>
#include <cglm/vec4.h>
#include <cglm/mat3.h>
#include <cglm/mat4.h>
#include <cglm/quat.h>
#include <cglm/cam.h>
#include <math.h>



  /*==============================================================================
   * Quads
   =============================================================================*/

static void _bs_quadTextureCoords(const bs_vec2* offset, const bs_vec2* coords, bs_Quad* out) {
    out->ca = BS_V2(offset->x, offset->y);
    out->cb = BS_V2(coords->x, offset->y);
    out->cc = BS_V2(offset->x, coords->y);
    out->cd = BS_V2(coords->x, coords->y);
}

BSAPI void _bs_quad(const bs_vec3* position, const bs_vec2* dimensions, bs_Quad* out) {
    *out = (bs_Quad) {
        *position,
        BS_V3(position->x + dimensions->x, position->y, position->z),
        BS_V3(position->x, position->y + dimensions->y, position->z),
        BS_V3(position->x + dimensions->x, position->y + dimensions->y, position->z)
    };

    _bs_quadTextureCoords(&BS_V2(0.0, 0.0), &BS_V2(1.0, 1.0), out);
}



  /*==============================================================================
   * Vectors
   =============================================================================*/

 /**
  Midpoint
  */
BSAPI void _bs_v2Mid(const bs_vec2* a, const bs_vec2* b, bs_vec2* out) {
    *out = BS_V2((a->x + b->x) / 2.0f, (a->y + b->y) / 2.0f);
}

BSAPI void _bs_v3Mid(const bs_vec3* a, const bs_vec3* b, bs_vec3* out) {
    *out = BS_V3((a->x + b->x) / 2.0f, (a->y + b->y) / 2.0f, (a->z + b->z) / 2.0f);
}



  /*==============================================================================
   * Quaternions
   * TODO: Use CGLM
   =============================================================================*/

BSAPI void _bs_eulToQ(const bs_vec3* eul, bs_vec4* out) {
    double cy = cos(eul->x * 0.5f);
    double sy = sin(eul->x * 0.5f);
    double cp = cos(eul->y * 0.5f);
    double sp = sin(eul->y * 0.5f);
    double cr = cos(eul->z * 0.5f);
    double sr = sin(eul->z * 0.5f);

    *out = BS_V4(
        sr * cp * cy - cr * sp * sy,
        cr * sp * cy + sr * cp * sy,
        cr * cp * sy - sr * sp * cy,
        cr * cp * cy + sr * sp * sy
    );
}

BSAPI void _bs_qToEul(const bs_vec4* qp, bs_vec3* out) {
    bs_vec4 q = *qp;

    float sinr_cosp = 2.0f * (q.w * q.x + q.y * q.z);
    float cosr_cosp = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
    out->x = atan2(sinr_cosp, cosr_cosp);

    float sinp = 2.0f * (q.w * q.y - q.z * q.x);

    if (fabs(sinp) >= 1.0f) 
        out->y = copysign(BS_PI / 2.0f, sinp);
    else 
        out->y = asin(sinp);

    float siny_cosp = 2.0f * (q.w * q.z + q.x * q.y);
    float cosy_cosp = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
    out->z = atan2(siny_cosp, cosy_cosp);
}



  /*==============================================================================
   * Matrices
   =============================================================================*/

BSAPI bs_mat4x3 _bs_m4x3(const bs_mat4* m) {
    return (bs_mat4x3) {
        .v[0] = m->v[0].xyz,
        .v[1] = m->v[1].xyz,
        .v[2] = m->v[2].xyz,
        .v[3] = m->v[3].xyz,
    };
}

BSAPI void bs_m3ToM4(const bs_mat3* m, bs_mat4* out) {
    out->v[0] = BS_V3_TO_V4(m->v[0], 0.0f);
    out->v[1] = BS_V3_TO_V4(m->v[1], 0.0f);
    out->v[2] = BS_V3_TO_V4(m->v[2], 0.0f);
    out->v[3] = BS_V4(0.0f, 0.0f, 0.0f, 1.0f);
}



  /*==============================================================================
   * Color
   =============================================================================*/

 /**
  Taken from https://github.com/Inseckto/HSV-to-RGB/blob/master/HSV2RGB.c
  */
BSAPI bs_vec3 _bs_hsvToRgb(const bs_vec3* hsv) {
    float r, g, b;
    
    float h = hsv->x / 360;
    float s = hsv->y;
    float v = hsv->z;

    int i = floor(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch (i % 6) {
    case 0: r = v, g = t, b = p; break;
    case 1: r = q, g = v, b = p; break;
    case 2: r = p, g = v, b = t; break;
    case 3: r = p, g = q, b = v; break;
    case 4: r = t, g = p, b = v; break;
    case 5: r = v, g = p, b = q; break;
    default: return BS_V3(0.0, 0.0, 0.0);
    }

    return BS_V3(r, g, b);
}

 /**
  Taken from https://stackoverflow.com/questions/6614792/fast-optimized-and-accurate-rgb-hsb-conversion-code-in-c
  */
BSAPI bs_vec3 _bs_rgbToHsv(const bs_vec3* rgb) {
    bs_vec3 hsv;

    float r = rgb->x;
    float g = rgb->y;
    float b = rgb->z;
    float max = fmaxf(fmaxf(r, g), b);
    float min = fminf(fminf(r, g), b);
    float delta = max - min;

    if (delta != 0) {
        float hue;

        if (r == max)
            hue = (g - b) / delta;
        else {
            if (g == max)
                hue = 2 + (b - r) / delta;
            else
                hue = 4 + (r - g) / delta;
        }
        hue *= 60;

        if (hue < 0)
            hue += 360;

        hsv.x = hue;
    }
    else
        hsv.x = 0;

    hsv.y = max == 0 ? 0 : (max - min) / max;
    hsv.z = max;

    return hsv;
}



  /*==============================================================================
   * Bezier Curves
   =============================================================================*/

static float _bs_cubicBezier(float p0, float p1, float p2, float p3, float t) {
    float curve;

    curve = powf(1.0f - t, 3.0f) * p0;
    curve += 3 * powf(1.0f - t, 2.0f) * t * p1;
    curve += 3 * powf(1.0f - t, 1.0f) * powf(t, 2.0f) * p2;
    curve += powf(t, 3.0f) * p3;

    return curve;
}

static float _bs_quadBezier(float p0, float p1, float p2, float t) {
    float u = 1.0f - t;
    return u * u * p0 + 2.0f * u * t * p1 + t * t * p2;
}

static void _bs_nCubicBezier(int n, const bs_vec4* p0, const bs_vec4* p1, const bs_vec4* p2, const bs_vec4* p3, bs_vec4* out, int out_length) {
    float t = 0.0f;
    float incr = 1.0f / (float)out_length;

    for (int i = 0; i < out_length; i++, t += incr) {
        for (int j = 0; j < n; j++)
            out[i].a[j] = _bs_cubicBezier(p0->a[j], p1->a[j], p2->a[j], p3->a[j], t);
    }
}

static void _bs_nQuadBezier(int n, const bs_vec4* p0, const bs_vec4* p1, const bs_vec4* p2, bs_vec4* out, int out_length) {
    float t = 0.0;
    float incr = 1.0 / (float)out_length;

    for (int i = 0; i < out_length; i++, t += incr) {
        for (int j = 0; j < n; j++)
            out[i].a[j] = _bs_quadBezier(p0->x, p1->x, p2->x, t);
    }
}

BSAPI void _bs_v2CubicBezier(const bs_vec2* p0, const bs_vec2* p1, const bs_vec2* p2, const bs_vec2* p3, bs_vec2* out, int out_length) {
    _bs_nCubicBezier(2, p0, p1, p2, p3, out, out_length);
}

BSAPI void _bs_v2QuadBezier(const bs_vec2* p0, const bs_vec2* p1, const bs_vec2* p2, bs_vec2* out, int out_length) {
    _bs_nQuadBezier(2, p0, p1, p2, out, out_length);
}

BSAPI void _bs_v3CubicBezier(const bs_vec3* p0, const bs_vec3* p1, const bs_vec3* p2, const bs_vec3* p3, bs_vec3* out, int out_length) {
    _bs_nCubicBezier(3, p0, p1, p2, p3, out, out_length);
}

BSAPI void _bs_v3QuadBezier(const bs_vec3* p0, const bs_vec3* p1, const bs_vec3* p2, bs_vec3* out, int out_length) {
    _bs_nQuadBezier(3, p0, p1, p2, out, out_length);
}



  /*==============================================================================
   * AABB
   =============================================================================*/

BSAPI void _bs_rotateAabb(const bs_Aabb* aabb, const bs_mat3* rotation_matrix, bs_Aabb* out) {
    bs_vec3 min = aabb->min;
    bs_vec3 max = aabb->max;

    bs_vec3 corners[8] = {
        {min.x, min.y, min.z},
        {max.x, min.y, min.z},
        {min.x, max.y, min.z},
        {max.x, max.y, min.z},
        {min.x, min.y, max.z},
        {max.x, min.y, max.z},
        {min.x, max.y, max.z},
        {max.x, max.y, max.z},
    };

    bs_vec3 new_min = { BS_FLT_MAX,  BS_FLT_MAX,  BS_FLT_MAX };
    bs_vec3 new_max = { -BS_FLT_MAX, -BS_FLT_MAX, -BS_FLT_MAX };

    for (int i = 0; i < 8; i++) {
        bs_vec3 p;
        bs_m3MulV3(rotation_matrix, corners + i, &p);

        new_min = BS_V3_MIN(new_min, p);
        new_max = BS_V3_MAX(new_max, p);
    }

    *out = (bs_Aabb) {
        .min = new_min,
        .max = new_max,
    };
}

BSAPI void _bs_fitAabb(const bs_Aabb* aabb, const bs_vec2* size, const bs_vec4* rotation, bs_mat4* out) {
    bs_Aabb rotated_aabb = *aabb;

    bs_vec3 center;
    bs_v3MulS(&BS_V3_ADD(rotated_aabb.min, rotated_aabb.max), 0.5, &center);

    bs_mat3 rotation_matrix;
    bs_qToM3(rotation, &rotation_matrix);

    _bs_rotateAabb(&rotated_aabb, &rotation_matrix, &rotated_aabb);

    bs_vec3 rotated_size;
    bs_v3Sub(&aabb->max, &aabb->min, &rotated_size);

    float scale_x = size->x / rotated_size.x;
    float scale_y = size->y / rotated_size.y;
    float scale = BS_MIN(scale_x, scale_y);

    // float padding = 4.0;
    // scale *= (render_size.x - padding) / render_size.x;

    bs_mat4 translation_matrix, scale_matrix, center_translation_matrix;

    bs_m4Translate(&BS_MAT4_IDENTITY, &BS_V3(size->x * 0.5, size->y * 0.5, 0.0), &translation_matrix);
    bs_m4Scale(&BS_MAT4_IDENTITY, &BS_V3(scale, scale, scale), &scale_matrix);
    bs_m4Translate(&BS_MAT4_IDENTITY, &BS_V3_MUL_S(center, -1.0), &center_translation_matrix);

    bs_mat4 transform;
    bs_m3ToM4(&rotation_matrix, &transform);

    bs_m4Mul(&transform, &center_translation_matrix, &transform);
    bs_m4Mul(&scale_matrix, &transform, &transform);
    bs_m4Mul(&translation_matrix, &transform, &transform);

    *out = transform;
}



  /*==============================================================================
   * Collision Tests
   =============================================================================*/

 /**
  Line vs Line

  Taken from:
  https://gist.github.com/TimSC/47203a0f5f15293d2099507ba5da44e6
  */
static inline double _bs_determinate(float a, float b, float c, float d) {
    return a * d - b * c;
}

BSAPI bool _val_bs_lineVsLine(const bs_vec2* l1_start, const bs_vec2* l1_end, const bs_vec2* l2_start, const bs_vec2* l2_end, bs_LineVsLine* out) {
    bool result = _bs_lineVsLine(l1_start, l1_end, l2_start, l2_end, out);

    if (!isfinite(out->point.x) || !isfinite(out->point.y)) {
        _bs_warnN(BS_CONSTANT_STRING("_bs_lineVsLine returned an infinite number\n"));
    }

    return result;
}

BSAPI bool _bs_lineVsLine(const bs_vec2* l1_start, const bs_vec2* l1_end, const bs_vec2* l2_start, const bs_vec2* l2_end, bs_LineVsLine* out) {
    out->hit = false;

    double detL1 = _bs_determinate(l1_start->x, l1_start->y, l1_end->x, l1_end->y);
    double detL2 = _bs_determinate(l2_start->x, l2_start->y, l2_end->x, l2_end->y);
    double x1mx2 = l1_start->x - l1_end->x;
    double x3mx4 = l2_start->x - l2_end->x;
    double y1my2 = l1_start->y - l1_end->y;
    double y3my4 = l2_start->y - l2_end->y;

    double xnom = _bs_determinate(detL1, x1mx2, detL2, x3mx4);
    double ynom = _bs_determinate(detL1, y1my2, detL2, y3my4);
    double denom = _bs_determinate(x1mx2, y1my2, x3mx4, y3my4);

    if (denom == 0.0) {
        *out = (bs_LineVsLine) {
            .point = { NAN, NAN }
        };

        return false;
    }

    bs_vec2 result = {
        .x = xnom / denom,
        .y = ynom / denom,
    };

    *out = (bs_LineVsLine) {
        .hit = true,
        .point = result,
    };
    

    if (!isfinite(result.x) || !isfinite(result.y))
        return false;

    return true;
}

 /**
  Rectangle vs Point
  */
BSAPI bool _bs_rectangleVsPoint(const bs_vec2* position, const bs_vec2* dimensions, const bs_vec2* point) {
    bool hit = 
        position->x < point->x &&
        point->x < (position->x + dimensions->x) &&
        position->y < point->y &&
        point->y < (position->y + dimensions->y);

    return hit;
}

 /**
  Fast Ray-Box Intersection
  by Andrew Woo
  from "Graphics Gems", Academic Press, 1990
  */
BSAPI void _bs_rayVsObb(const bs_Ray* ray, const bs_vec3* position, const bs_vec4* rotation, const bs_vec3* scale, bs_RayVsObb* result) {
    result->hit = false;

    char inside = true;
    char quadrant[3];
    register int i;
    int which_plane;
    double max_t[3];
    bs_vec3 candidate_plane = { 0.0 };

    const int RIGHT = 0, LEFT = 1, MIDDLE = 2;

    bs_mat4 transform = BS_MAT4_IDENTITY;
    bs_mat3 rotation_matrix;
    bs_mat3 rotation_matrix_inverse;

    bs_m4Translate(&transform, position, &transform);
    bs_m4Rotate(&transform, rotation, &transform);

    bs_qToM3(rotation, &rotation_matrix);
    bs_m3Inverse(&rotation_matrix, &rotation_matrix_inverse);

    bs_vec3 origin;
    bs_vec3 direction;
    bs_vec3 min, max;

    bs_vec3 s;
    bs_v3Sub(&ray->origin, position, &s);

    bs_m3MulV3(&rotation_matrix_inverse, &s, &origin);
    bs_m3MulV3(&rotation_matrix_inverse, &ray->direction, &direction);

    bs_v3MulS(scale, -1.0, &min);
    max = *scale;

    // find candidate planes; this loop can be avoided if
    // rays cast all from the eye(assume perpsective view)
    for (i = 0; i < 3; i++) {
        if (origin.a[i] < min.a[i]) {
            quadrant[i] = LEFT;
            candidate_plane.a[i] = min.a[i];
            inside = false;
        }
        else if (origin.a[i] > max.a[i]) {
            quadrant[i] = RIGHT;
            candidate_plane.a[i] = max.a[i];
            inside = false;
        }
        else
            quadrant[i] = MIDDLE;
    }

    // ray origin inside bounding box
    if (inside) {
        *result = (bs_RayVsObb){
            .coordinate = ray->origin,
            .hit = true,
        };

        bs_v3MulS(&ray->direction, -1.0, &result->normal);

        return;
    }

    // calculate T distances to candidate planes
    for (i = 0; i < 3; i++) {
        if (quadrant[i] != MIDDLE && direction.a[i] != 0.0)
            max_t[i] = (candidate_plane.a[i] - origin.a[i]) / direction.a[i];
        else
            max_t[i] = -1.0;
    }

    // get largest of the maxT's for final choice of intersection
    which_plane = 0;
    for (i = 1; i < 3; i++) {
        if (max_t[which_plane] < max_t[i])
            which_plane = i;
    }

    bs_vec3 normal;
    bs_vec3 normals[3] = { BS_V3(1, 0, 0), BS_V3(0, 1, 0), BS_V3(0, 0, 1) };
    bs_m3MulV3(&rotation_matrix, &normals[which_plane], &normal);

    if (quadrant[which_plane] == LEFT)
        bs_v3MulS(&normal, -1.0, &normal);
    bs_v3Normalize(&normal, &normal);

    bs_vec3 coord;
    for (i = 0; i < 3; i++) {
        if (which_plane != i) {
            coord.a[i] = origin.a[i] + max_t[which_plane] * direction.a[i];
            if (coord.a[i] < min.a[i] || coord.a[i] > max.a[i])
                return;
        }
        else
            coord.a[i] = candidate_plane.a[i];
    }

    *result = (bs_RayVsObb){
        .plane = which_plane,
        .normal = normal,
        .hit = true,
    };

    bs_m4MulV3(&transform, &coord, &result->coordinate);
}

 /**
  Sphere vs Point
  */
BSAPI bool _bs_sphereVsPoint(const bs_vec3* center, float radius, const bs_vec3* point, bs_SphereVsPoint* out) {
    int x1 = pow((point->x - center->x), 2);
    int y1 = pow((point->y - center->y), 2);
    int z1 = pow((point->z - center->z), 2);

    int dist = (x1 + y1 + z1);

    if (dist <= (radius * radius))
        return out->hit = true;

    return out->hit = false;
}

 /**
  Sphere vs Box
  */

static bool bsi_sphereVsObb(const bs_vec3* center, float radius, const bs_vec3* position, const bs_vec4* rotation, const bs_vec3* scale, bs_mat4* transform, bs_vec3* closest_point) {
    *transform = BS_MAT4_IDENTITY;

    bs_m4Translate(transform, position, transform);
    bs_m4Rotate(transform, rotation, transform);
    bs_m4Inverse(transform, transform);

    bs_vec3 relative_center;
    bs_m4MulV3(transform, center, &relative_center);

    if (bs_abs(relative_center.x) - radius > scale->x ||
        bs_abs(relative_center.y) - radius > scale->y ||
        bs_abs(relative_center.z) - radius > scale->z)
    {
        return false;
    }

    *closest_point = BS_V3(0.0, 0.0, 0.0);
    float dist;

    dist = relative_center.x;
    if (dist > scale->x) dist = scale->x;
    if (dist < -scale->x) dist = -scale->x;
    closest_point->x = dist;

    dist = relative_center.y;
    if (dist > scale->y) dist = scale->y;
    if (dist < -scale->y) dist = -scale->y;
    closest_point->y = dist;

    dist = relative_center.z;
    if (dist > scale->z) dist = scale->z;
    if (dist < -scale->z) dist = -scale->z;
    closest_point->z = dist;

    bs_vec3 diff;
    bs_v3Sub(closest_point, &relative_center, &diff);

    float distance = bs_v3MagnitudeSqrd(&diff);

    return distance <= radius * radius;
}

BSAPI bool _bs_sphereVsObbTest(const bs_vec3* center, float radius, const bs_vec3* position, const bs_vec4* rotation, const bs_vec3* scale) {
    bs_mat4 transform;
    bs_vec3 closest_point;
    float distance;

    bool inside = bsi_sphereVsObb(center, radius, position, rotation, rotation, &transform, &closest_point);
    if (!inside)
        return false;

    return true;
}

BSAPI bool _bs_sphereVsObb(const bs_vec3* center, float radius, const bs_vec3* position, const bs_vec4* rotation, const bs_vec3* scale, bs_SphereVsBox* result) {
    result->hit = false;

    bs_mat4 transform;
    bs_vec3 closest_point;

    bool inside = bsi_sphereVsObb(center, radius, position, rotation, rotation, &transform, &closest_point);
    if (!inside)
        return false;

    bs_m4MulV3(&transform, &closest_point, &result->point);

    bs_v3Sub(&center, &result->point, &result->normal);
    bs_v3Normalize(&result->normal, &result->normal);

    return result->hit = true;
}

/*
BSAPI void _bs_sphereVsSphere(bs_Sphere* a, bs_Sphere* b, bs_Contact* result) {
    bs_vec3 mid;
    _bs_v3Sub(&a->center, &b->center, &mid);

    float magnitude = _bs_v3Magnitude(&mid);

    if (magnitude <= 0.0 || magnitude >= (a->radius + b->radius)) {
        *result = (bs_Contact){

        };
        return;
    }
        return false;

    result->normal = bs_v3MulS(mid, 1.0 / magnitude);
    result->point = bs_v3Add(a->center, bs_v3MulS(mid, 0.5));
    result->penetration = a->radius + b->radius - magnitude;

    return true;
}
*/
