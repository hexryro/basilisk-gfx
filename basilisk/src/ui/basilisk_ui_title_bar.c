
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
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, close_caption)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, maximize_caption)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, minimize_caption)

BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, title_bar_close)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, title_bar_minimize)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, title_bar_maximize)

BSGFX_CACHE_COLOR_MATERIAL(title_bar_background, BS_RGBA(83, 83, 83, 255))
BSGFX_CACHE_COLOR_MATERIAL(close_button_background_color, BS_RGBA(226, 42, 39, 255))
BSGFX_CACHE_COLOR_MATERIAL(default_button_background_color, BS_RGBA(93, 93, 93, 255))

static bsgfx_Font* basilisk_title_bar_font;
static bool basilisk_hovering_title_bar_buttons;

bs_NonClientArea basilisk_onClientAreaTick(bs_ivec2 pt) {
    RECT rc;
    GetWindowRect(bs_scope()->context->hwnd, &rc);

    int y = pt.y - rc.top;

    if (basilisk_hovering_title_bar_buttons)
        return BS_CLIENT_AREA;

    if (y >= 0 && y < 32)
        return BS_NON_CLIENT_AREA_CAPTION;

    return BS_CLIENT_AREA;
}

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

static void basilisk_instantiateButtonBackgroundUI(bsgfx_UIElement* element, bsgfx_Material* material, bs_vec3 position, bs_vec2 size) {
    bsgfx_UISolid button = {
        .position = position,
        .size = size,
        .material_id = material->id,
    };

    bsgfx_solidUIElement(button, element);
   //element->position.x -= element->size.x;
    if (bsgfx_hoveringUIElement(element)) {
        basilisk_hovering_title_bar_buttons = true;
        bsgfx_instantiateSolidUIElement(button, element);
    }
}

static void basilisk_instantiateTitleBarButtonUI(bsgfx_AtlasCache* icon_cache, bsgfx_Material* material, bs_vec3 position, bs_vec2 title_bar_size, int width) {
    bsgfx_UIElement element_v;
    bsgfx_UIElement* element = &element_v;

    basilisk_instantiateButtonBackgroundUI(element, material, position, BS_V2(width, BASILISK_TITLE_BAR_HEIGHT));

    position.z++;
    bsgfx_UIIcon close_button_icon = {
        .position = position,
        .cache = icon_cache,
        .subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
        .align = { width, BASILISK_TITLE_BAR_HEIGHT },
    };

    bsgfx_atlasIconUIElement(close_button_icon, element);
    bsgfx_instantiateAtlasIconUIElement(close_button_icon, element);
}

static void basilisk_instantiateTitleBarTextButtonUI(const char* text, bsgfx_Material* material, bs_vec3 position, bs_vec2 title_bar_size) {
    const float x_padding = 8.0; // px padding on each side of the button
    const float y_padding = -4.0;

    bsgfx_UIElement element_v;
    bsgfx_UIElement* element = &element_v;

    position.z++;
    position.x += x_padding;
    bsgfx_UIText text_ui = {
        .position = position,
        .font = basilisk_title_bar_font,
        .as_ascii = text,
        .px_size = 13,
        .align = { 0, BASILISK_TITLE_BAR_HEIGHT },
    };

    bsgfx_instantiateTextUI(text_ui, element);
    element->position = position;
    element->position.x -= x_padding;
    element->position.z--;

    float height = BASILISK_TITLE_BAR_HEIGHT;
    height += y_padding * 2.0;
    element->position.y -= y_padding;
    basilisk_instantiateButtonBackgroundUI(element, material, element->position, BS_V2(element->size.x + x_padding * 2, height));
}

void basilisk_instantiateTitleBarUI() {
    basilisk_hovering_title_bar_buttons = false;
    basilisk_title_bar_font = basilisk_querySegoeUI();

    if (!basilisk_title_bar_font)
        return;

    bs_ivec2 resolution = bs_resolution(bs_scope()->context);
    bs_vec2 title_bar_size = { resolution.x, BASILISK_TITLE_BAR_HEIGHT };

    bsgfx_AtlasCache* icon_atlas_cache = $BSMOD_ATLAS_UI_icon();
    bsgfx_AtlasCache* close_caption = $BSMOD_ATLAS_UI_title_bar_close();
    bsgfx_AtlasCache* maximize_caption = $BSMOD_ATLAS_UI_title_bar_maximize();
    bsgfx_AtlasCache* minimize_caption = $BSMOD_ATLAS_UI_title_bar_minimize();

    bsgfx_Material* close_button_background_material = $close_button_background_color();
    bsgfx_Material* default_button_background_material = $default_button_background_color();

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
    bsgfx_instantiateAtlasIconUI((bsgfx_UIIcon) {
        .position = position,
        .cache = icon_atlas_cache,
        .subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
        .align = { 32, BASILISK_TITLE_BAR_HEIGHT },
    }, element);

   /**
    Title text
    */
    position.x += element->size.x;
    position.x += 16.0;

    basilisk_instantiateTitleBarTextButtonUI("File", default_button_background_material, position, title_bar_size);

    position.x = title_bar_size.x;

    const int close_button_width = 32;
    const int maximize_button_width = 32;
    const int minimize_button_width = 32;

    position.x -= close_button_width;
    basilisk_instantiateTitleBarButtonUI(close_caption, close_button_background_material, position, title_bar_size, close_button_width);

    position.x -= maximize_button_width;
    basilisk_instantiateTitleBarButtonUI(maximize_caption, default_button_background_material, position, title_bar_size, maximize_button_width);

    position.x -= minimize_button_width;
    basilisk_instantiateTitleBarButtonUI(minimize_caption, default_button_background_material, position, title_bar_size, minimize_button_width);


   /**
    Close button
    const int close_button_width = 48;
    position.x = title_bar_size.x;
    bsgfx_UISolid close_button = {
        .position = position,
        .size = { close_button_width, BASILISK_TITLE_BAR_HEIGHT },
        .material_id = close_button_background_material->id,
    };

    bsgfx_solidUIElement(close_button, element);
    element->position.x -= element->size.x;
    if (bsgfx_hoveringUIElement(element)) {
        bsgfx_instantiateSolidUIElement(close_button, element);
    }

    position.z++;
    position.x -= element->size.x;
    bsgfx_UIIcon close_button_icon = {
        .position = position,
        .cache = close_caption,
        .subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
        .align = { 48, BASILISK_TITLE_BAR_HEIGHT },
    };

    bsgfx_atlasIconUIElement(close_button_icon, element);
   // element->position.x -= element->size.x;
    bsgfx_instantiateAtlasIconUIElement(close_button_icon, element);
    */


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
