
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
#define BASILISK_CONTEXT_MENU_TEXT_INDENT 16
#define BASILISK_CONTEXT_MENU_BUTTON_HEIGHT 16
#define BASILISK_CONTEXT_MENU_WIDTH 300
#define BASILISK_CONTEXT_MENU_CLEAR_COLOR BS_RGBA(185, 185, 185, 255)

BSGFX_CACHE_COLOR_MATERIAL(context_menu_button_hover_color, BS_RGBA(0, 120, 215, 255))

  //BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, icon)
  //BSGFX_CACHE_COLOR_MATERIAL(test_color, BS_RGBA(255, 83, 83, 255))

static bsgfx_Font* context_menu_font = NULL;

typedef struct {
    const char* left_text;
    const char* right_text;
    ContextMenuType hover_menu_type;
} ContextMenuElement;

typedef struct {
    int context_id;
    int renderer_id;
    ContextMenuType type;
    bs_Queue* queue;
    bs_Renderer* renderer;
    bs_Context* context;
} ContextMenu;

static ContextMenu _context_menus_[] = {
    { .context_id = BASILISK_CONTEXT_MENU_0, .renderer_id = BASILISK_RENDERER_CONTEXT_MENU_0 },
    { .context_id = BASILISK_CONTEXT_MENU_1, .renderer_id = BASILISK_RENDERER_CONTEXT_MENU_1 },
};

ContextMenuElement _context_menu_open_recent_elements_[] = {
    {
        .left_text = "Testing...",
    },
    {
        .left_text = "Abc123",
    },
};

static ContextMenuElement _context_menu_file_elements_[] = {
    {
        .left_text = "New...",
        .right_text = "Ctrl+N",
    },
    {
        .left_text = "Open...",
    },
    {
        .left_text = "Open Recent",
        .hover_menu_type = CONTEXT_MENU_OPEN_RECENT,
    },
    {
        .left_text = "Save",
        .right_text = "Ctrl+S",
    },
    {
        .left_text = "Save As...",
        .right_text = "Shift+Ctrl+S",
    },
    {
        .left_text = "Exit",
        .right_text = "Alt+F4",
    }
};

#define CONTEXT_MENU(name, context) \
    { .elements = name, .count = sizeof(name) / sizeof(*name), .context_id = context }

static struct {
    ContextMenuElement* elements;
    int count;
    int context_id;
} _context_menu_types_[CONTEXT_MENU_COUNT] = {
    [CONTEXT_MENU_FILE]             = CONTEXT_MENU(_context_menu_file_elements_, BASILISK_CONTEXT_MENU_0),
    [CONTEXT_MENU_OPEN_RECENT]      = CONTEXT_MENU(_context_menu_open_recent_elements_, BASILISK_CONTEXT_MENU_1),
};

void showContextMenuUI(ContextMenuType type, bs_vec3 position) {
    bs_Context* context = bs_fetch(BASILISK_CONTEXTS, _context_menu_types_[type].context_id)->context;

    if (!context->hidden)
        return;

    int window_height = _context_menu_types_[type].count * BASILISK_CONTEXT_MENU_BUTTON_HEIGHT;

    ContextMenu* menu = context->user_data;
    menu->type = type;

    bs_ivec2 new_position = bs_windowPosition(bs_scope()->context);
    new_position.x += position.x;
    new_position.y -= position.y;

    bs_moveWindow(context, new_position.x, new_position.y);
    bs_showWindow(context);

    bs_ivec2 resolution = bs_resolution(context);
    if (resolution.x != BASILISK_CONTEXT_MENU_WIDTH || resolution.y != window_height) {
        bs_resizeWindow(context, BASILISK_CONTEXT_MENU_WIDTH, window_height);
    }
}

void hideContextMenuUI(bs_Context* context) {
    bs_hideWindow(context);
}

void toggleContextMenuUI(ContextMenuType type, bs_vec3 position) {
    bs_Context* context = bs_fetch(BASILISK_CONTEXTS, _context_menu_types_[type].context_id)->context;
    if (context->hidden)
        showContextMenuUI(type, position);
    else
        hideContextMenuUI(context);
}

static void instantiateContextMenuUI(bs_Context* context, ContextMenuElement elements[], int elements_count) {
    int window_height = elements_count * BASILISK_CONTEXT_MENU_BUTTON_HEIGHT;
    const int border_size = 1;

    bs_vec3 position = { 0.0 };

    bsgfx_UIElement element;

   /**
    Background
    */
    bsgfx_UISolid solid = {
        .material_id = $white_material()->id,
        .position = {
            position.x + border_size,
            position.y + border_size,
            position.z,
        },
        .size = { 
            BASILISK_CONTEXT_MENU_WIDTH - border_size * 2,
            window_height - border_size * 2,
        },
    };
    bsgfx_solidUIElement(solid, &element);
    bool hovering_menu = bsgfx_hoveringUIElement(&element);
    bsgfx_instantiateSolidUIElement(solid, &element);
    position.z++;

   /**
    Elements
    */
    position.y += window_height;

    for (int i = 0; i < elements_count; i++) {
        ContextMenuElement* context_menu_element = elements + i;
        bsgfx_UIElement element;

        bsgfx_Material* text_material = $black_material();

       /**
        Hovering button background
        */
        bsgfx_UISolid solid = {
            .position = position,
            .size = { BASILISK_CONTEXT_MENU_WIDTH, BASILISK_CONTEXT_MENU_BUTTON_HEIGHT },
        };

        bsgfx_solidUIElement(solid, &element);
        element.position.y -= element.size.y;
        position = element.position;

        bool hovering = bsgfx_hoveringUIElement(&element);
        bool child_open = false;

        if (context_menu_element->hover_menu_type != CONTEXT_MENU_UNDEFINED) {
            bs_Context* child_context = bs_fetch(BASILISK_CONTEXTS, _context_menu_types_[context_menu_element->hover_menu_type].context_id)->context;
            child_open = !child_context->hidden;
        }

        if (hovering || child_open) {
            solid.material_id = $context_menu_button_hover_color()->id;
            bsgfx_instantiateSolidUIElement(solid, &element);
            text_material = $white_material();
        }

        bs_vec3 revert_position = position;

       /**
        Left Text
        */
        position.z++;
        position.x += BASILISK_CONTEXT_MENU_TEXT_INDENT;
        bsgfx_UIText left_text = {
            .position = position,
            .as_ascii = context_menu_element->left_text,
            .font = _fonts_.selawik,
            .px_size = 13,
            .material_id = text_material->id,
            .align = { 0, BASILISK_CONTEXT_MENU_BUTTON_HEIGHT },
        };

        bsgfx_instantiateTextUI(left_text, &element);
        position.x -= BASILISK_CONTEXT_MENU_TEXT_INDENT;

       /**
        Right text
        */
        if (context_menu_element->right_text) {
            position.x += BASILISK_CONTEXT_MENU_WIDTH - BASILISK_CONTEXT_MENU_TEXT_INDENT;
            bsgfx_UIText right_text = {
                .position = position,
                .as_ascii = context_menu_element->right_text,
                .font = _fonts_.selawik,
                .px_size = 13,
                .material_id = text_material->id,
                .align = { 0, BASILISK_CONTEXT_MENU_BUTTON_HEIGHT },
            };


            bsgfx_instantiateTextUI(right_text, &element);

            bs_vec3 translation = { -(element.size.x), 0.0, 0.0 };
            bsgfx_translateUIElement(&element, &translation);
        }

       /**
        Expandable menu
        */
        if (context_menu_element->hover_menu_type != CONTEXT_MENU_UNDEFINED) {
            position.x += BASILISK_CONTEXT_MENU_WIDTH - BASILISK_CONTEXT_MENU_TEXT_INDENT;
            bsgfx_AtlasCache* expand_cache = $BSMOD_ATLAS_UI_expand();

            bsgfx_UIIcon icon = {
                .position = position,
                .cache = expand_cache,
                .subtype = bsgfx_subtypes()[BSGFX_SUBTYPE_UI],
                .material_id = text_material->id,
                .align = { BASILISK_CONTEXT_MENU_TEXT_INDENT, BASILISK_CONTEXT_MENU_BUTTON_HEIGHT },
            };

            bsgfx_atlasIconUIElement(icon, &element);
            bsgfx_instantiateAtlasIconUIElement(icon, &element);

            if (hovering) {
                position.x += BASILISK_CONTEXT_MENU_TEXT_INDENT;
                position.y += BASILISK_CONTEXT_MENU_BUTTON_HEIGHT;
                showContextMenuUI(context_menu_element->hover_menu_type, position);
            }
            else if (hovering_menu) {
                bs_Context* menu_context = bs_fetch(BASILISK_CONTEXTS, _context_menu_types_[context_menu_element->hover_menu_type].context_id)->context;
                hideContextMenuUI(menu_context);
            }
        }

        position = revert_position;
    }
}

void basilisk_instantiateContextMenuUI(bs_Context* context) {
    ContextMenu* menu = context->user_data;

    bs_ivec2 resolution = bs_resolution(context);
    bs_vec2 title_bar_size = { resolution.x, BASILISK_TITLE_BAR_HEIGHT };

    bs_vec3 position;
    bsgfx_UIElement element_v;
    bsgfx_UIElement* element = &element_v;

    // title icon
    position = BS_V3(0, resolution.y - title_bar_size.y, 0);
    position.y = 0.0;

    instantiateContextMenuUI(context, _context_menu_types_[menu->type].elements, _context_menu_types_[menu->type].count);
}

void onContextMenuTick(bs_Context* context) {

    if (context->hidden)
        return;
    ContextMenu* menu = context->user_data;

    bsgfx_computeContextCamera();
    basilisk_instantiateContextMenuUI(context);

    if (bs_leftClickOnce()) {
        //hideContextMenuUI();
    }

    bsgfx_tickInstanceTypes();
    basilisk_pipeline(menu->queue, menu->renderer, BASILISK_CONTEXT_MENU_CLEAR_COLOR);
    bsgfx_resetInstanceTypes();
}

static void iniContextMenu(int i) {
    ContextMenu* menu = _context_menus_ + i;

    bs_Object* menu_context_queue = BS_QUEUE(-1, -1, BS_OBJECT_HAS_SWAPS_BIT);
    bs_queue(menu_context_queue, 0, BS_QUEUE_GRAPHICS_BIT);

    char* name = bs_alloca(sizeof("ContextMenu_") + bs_numDigits(i));
    sprintf(name, "ContextMenu_%d", i);

    bs_Object* context_obj = BS_CONTEXT(BASILISK_CONTEXTS, menu->context_id, 0);
    bs_Context* context = context_obj->context;

    context->user_data = menu;

    bs_window(context, NULL, onContextMenuTick, 512, 512, strdup(name), BS_WINDOW_MENU);
    bs_swapchain(context);

    menu->queue = menu_context_queue->queue;
    menu->context = context;
    menu->renderer = basilisk_createHiResRenderer(context, menu->renderer_id)->renderer;
}

void iniContextMenus() {
    int context_menus_count = sizeof(_context_menus_) / sizeof(*_context_menus_);
    for (int i = 0; i < context_menus_count; i++) {
        iniContextMenu(i);
    }
}