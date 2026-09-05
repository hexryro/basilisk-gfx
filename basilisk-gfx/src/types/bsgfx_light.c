
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

#include <bsgfx_internal.h>

static void _bsgfx_mapLight(const bsgfx_RawLight* unmapped, bsgfx_Light* mapped) {
    *mapped = (bsgfx_Light) {
        .position = unmapped->position,
        .type = unmapped->type,
    };

    bs_vec4 q;
    bs_eulToQ(&unmapped->rotation, &q);
    bs_qRotateV3(&q, &BS_V3(0, -1, 0), &mapped->direction);
}

BSGFXAPI void _bsgfx_loadLights(int package_id) {
    _bsgfx_type(
        BSGFX_TYPE_LIGHT,
        package_id,
        BSGFX_LIGHT_VERSION,
        "lights", "light",
        sizeof(bsgfx_RawLight), sizeof(bsgfx_Light), _bsgfx_mapLight,
        0, 0, 0, 0);
}