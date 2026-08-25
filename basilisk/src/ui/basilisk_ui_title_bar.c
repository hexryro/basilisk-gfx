
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
BSGFX_CACHE_COLOR_MATERIAL(title_bar_background, BS_RGBA(83, 83, 83, 255))
BSGFX_CACHE_COLOR_MATERIAL(test_color, BS_RGBA(255, 83, 83, 255))

static bsgfx_Font* basilisk_querySegoeUI() {
    int package = bs_queryPackage("content/basilisk-fonts.bpak");
    if (package >= 0) {
        bs_Resource* resource = NULL;
        bs_queryResource(package, BS_RESOURCE_FONT, "project/fonts/segoeui.ttf", &resource);

        if (resource && resource->model) {
            return (bsgfx_Font*)resource->model;
        }
    }

    return NULL;
}

void basilisk_instantiateTitleBarUI() {
    bs_ivec2 resolution = bs_resolution();
    bs_vec2 title_bar_size = { resolution.x, BASILISK_TITLE_BAR_HEIGHT };

    bsgfx_AtlasCache* icon_atlas_cache = $BSMOD_ATLAS_UI_icon();
    bsgfx_Font* segoe_ui = basilisk_querySegoeUI();

    bs_vec3 position;
    bsgfx_UIElement element_v;
    bsgfx_UIElement* element = &element_v;

    // title icon
    //position = bsgfx_seekTopLeftUI(title_bar_size);
    position = BS_V3(0, resolution.y - title_bar_size.y, 0);

   /**
    Background
    */
    bsgfx_instantiateSolidUI((bsgfx_UISolid) {
        .position = position,
        .size = title_bar_size,
        .material_id = $title_bar_background()->id,
    }, element);
    position.z++;
    
   /**
    Icon
    */
    position.x += 4.0;
    bsgfx_instantiateAtlasIconUI((bsgfx_UIIcon) {
        .position = position,
        .cache = icon_atlas_cache,
        .subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
        .align_height = BASILISK_TITLE_BAR_HEIGHT,
    }, element);

   /**
    Title text
    */
    position.x += element->size.x;
    position.x += 4.0;

    bsgfx_instantiateTextUI((bsgfx_UIText) {
        .position = position,
        .font = segoe_ui,
        .as_ascii = "Basilisk",
        .px_size = 16,
        .align_height = BASILISK_TITLE_BAR_HEIGHT,
    }, element);

   /**
    */
    const int close_button_width = 48;
    position.x = title_bar_size.x;
    bsgfx_UISolid close_button = {
        .position = position,
        .size = { close_button_width, BASILISK_TITLE_BAR_HEIGHT },
        .material_id = $test_color()->id,
    };

    bsgfx_solidUIElement(close_button, element);
    element->position.x -= element->size.x;
    if (bsgfx_hoveringUIElement(element)) {

    }
    bsgfx_instantiateSolidUIElement(close_button, element);


    /*

    // close button
    const int button_width = 40;
    position = bsgfx_seekTopRightUI();
    position.x -= button_width;

    element = bsgfx_instantiateSolidUI((bsgfx_UISolid) {
        .position = position,
        // .color = 
    });
    position = bsgfx_seekUIElementCenter(element, close_button_icon->size);
    element = bsgfx_instantiateIconUI((bsgfx_UIIcon) {
        .position = position,
        //.cache = 
    });

    position.x -= element.width.x;

    // maximize button
    position.x -= button_width;

    element = bsgfx_instantiateIconUI((bsgfx_UIIcon) {
        .position = position,
            //.cache = 
    });

    position.x -= element.width.x;

    // minimize button
    position.x -= button_width;

    element = bsgfx_instantiateIconUI((bsgfx_UIIcon) {
        .position = position,
            //.cache = 
    });

    position.x -= element.width.x;
    */
   /**
    Engine icon
    */
}
