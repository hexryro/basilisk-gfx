
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

#include <basilisk-mod.h>
#include <bsmod_cache.h>
#include <basilisk.h>

#define BASILISK_TITLE_BAR_HEIGHT 32

BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, icon)
BSGFX_CACHE_COLOR_MATERIAL(test_color, BS_RGBA(255, 83, 83, 255))

void basilisk_instantiateBaseUI() {
    bs_ivec2 resolution = bs_resolution(bs_scope()->context);
    bs_vec2 title_bar_size = { resolution.x, BASILISK_TITLE_BAR_HEIGHT };

    bsgfx_AtlasCache* icon_atlas_cache = $BSMOD_ATLAS_UI_icon();

    bs_vec3 position;
    bsgfx_UIElement element_v;
    bsgfx_UIElement* element = &element_v;

    // title icon
    position = BS_V3(0, resolution.y - title_bar_size.y, 0);
    position.y = 0.0;

   /**
    Background
    */
    bsgfx_instantiateSolidUI((bsgfx_UISolid) {
        .position = position,
        .size = title_bar_size,
        .material_id = $test_color()->id,
    }, element);
    position.z++;

}
