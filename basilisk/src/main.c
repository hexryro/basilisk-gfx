
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
#include <basilisk.h>
#include <basilisk_pipeline.h>
#include <bsgfx_cache.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <threads.h>

Basilisk basilisk = {
	.sources = { -1 },
	.package_id = -1,
};

Fonts _fonts_ = { 0 };



  /*==============================================================================
   * Load
   *============================================================================*/

static void queryFonts() {
	int package = bs_queryPackage("content/basilisk-fonts.bpak");

	struct {
		const char* resource_name;
		bsgfx_Font** destination;
	} table[] = {
		{ "project/fonts/selawk.ttf", &_fonts_.selawik }
	};
	int count = sizeof(table) / sizeof(*table);

	if (package >= 0) {
		for (int i = 0; i < count; i++) {
			bs_Resource* resource = NULL;
			bs_queryResource(package, BS_RESOURCE_FONT, table[i].resource_name, &resource);
			if (resource)
				*table[i].destination = resource->font;
		}
	}
}

static void onLoadScene() {
	bsgfx_test(); // temp testing fonts
	$vs_bsgfx_mesh_color();
	$fs_bsgfx_atlas();

	basilisk_createRenderers();
		//basilisk_loadFonts();

	queryFonts();

	bs_loadPackage(&basilisk.package_id, "content/basilisk.bpak");
	bsmod_iniPackage(basilisk.package_id);

	bs_Queue* queue = bs_fetch(BSGFX_QUEUES, BSGFX_QUEUE_SINGLE_TIMES)->queue;

	bs_Object* atlas = BS_ATLAS(-1, -1, 0);
	bs_loadAtlasN(queue, atlas, basilisk.package_id, 0, BS_CONSTANT_STRING("temp"));

	bs_Object* title_bar_queue = BS_QUEUE(BASILISK_QUEUES, BASILISK_QUEUE_TITLE_BAR, BS_OBJECT_HAS_SWAPS_BIT);
	bs_queue(title_bar_queue, 0, 0);

	bsmod_onLoad();
	bsmod_bindAtlases();
}



  /*==============================================================================
   * Tick
   *============================================================================*/

static void onTick(bs_Context* context) {
	onTitleBarTick();

}



  /*==============================================================================
   * Log
   *============================================================================*/

static void onLog(const bs_LogQueueItem* item) {
	static const char* libraries[BS_LIBRARIES_COUNT] = {
		[BS_LIBRARY_BASILISK] = "[BASILISK]",
		[BS_LIBRARY_YYJSON] = "[YYJSON]",
		[BS_LIBRARY_LODEPNG] = "[LODEPNG]",
		[BS_LIBRARY_VULKAN] = "[VULKAN]",
		[BS_LIBRARY_WIN32] = "[WIN32]",
	};

	static const char* levels[BS_MESSAGE_LEVELS_COUNT] = {
		[BS_MESSAGE_INFO] = "[INFO]",
		[BS_MESSAGE_WARNING] = "[WARNING]",
		[BS_MESSAGE_VALIDATION_ERROR] = "[VALIDATION]",
	};

#ifdef _DEBUG
	static const char* levels_color[BS_MESSAGE_LEVELS_COUNT] = {
		[BS_MESSAGE_INFO] = BS_PRINT_COLOR("[INFO]", BS_PRINT_CYAN),
		[BS_MESSAGE_WARNING] = BS_PRINT_COLOR("[WARNING]", BS_PRINT_YELLOW),
		[BS_MESSAGE_VALIDATION_ERROR] = BS_PRINT_COLOR("[VALIDATION]", BS_PRINT_RED),
	};

	const char* color = BS_PRINT_MAGENTA;
	if (item->thread_id == basilisk.main_thread_id)
		color = BS_PRINT_GREEN;

	printf("%s %s %s[%d]" BS_PRINT_RESET " %s\n", libraries[item->library], levels_color[item->level], color, item->thread_id, item->message);
	if (item->function) {
		printf("    at %s at %s:%d\n", item->function, item->file, item->line);
	}
#endif

	bs_writeLogFileF("%s %s [%d] %s\n", libraries[item->library], levels[item->level], item->thread_id, item->message);
	if (item->function) {
		bs_writeLogFileF("    at %s at %s:%d\n", item->function, item->file, item->line);
	}
}



  /*==============================================================================
   * Resize
   *============================================================================*/

static void onResizeContext(bs_Context* context) {
	bs_Renderer* renderer = bs_fetch(BASILISK_RENDERERS, BASILISK_RENDERER_MAIN)->renderer;

	bs_resizeRenderer(renderer, bs_resolution(context));

	//bs_resizeImage();
}

int main(int argc, char* argv[]) {
	bs_enableValidation();
	bsgfx_enableValidation();
	bsmod_enableValidation();

	basilisk.main_thread_id = thrd_current()._Tid;

	bs_Callbacks* core_callbacks = bs_callbacks();
	*core_callbacks = (bs_Callbacks) {
		.log = onLog,
		.client_area_tick = onClientAreaTick,
	};

	bsgfx_Callbacks* gfx_callbacks = bsgfx_callbacks();
	*gfx_callbacks = (bsgfx_Callbacks) {
		.loadScene = onLoadScene,
		.pipeline = basilisk_pipeline,
		.tick = onTick,
	};

	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_CONTEXT, BASILISK_CONTEXTS_COUNT, BASILISK_CONTEXT_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_IMAGE, BASILISK_IMAGES_COUNT, BASILISK_IMAGE_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_SAMPLER, BASILISK_SAMPLERS_COUNT, BASILISK_SAMPLER_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_BUFFER, BASILISK_BUFFERS_COUNT, BASILISK_BUFFER_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_QUEUE, BASILISK_QUEUES_COUNT, BASILISK_QUEUE_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_BATCH, BASILISK_BATCHES_COUNT, BASILISK_BATCH_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_RENDERER, BASILISK_RENDERERS_COUNT, BASILISK_RENDERER_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_RAY_TRACER, BASILISK_RAY_TRACERS_COUNT, BASILISK_RAY_TRACER_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_ATLAS, BASILISK_ATLASES_COUNT, BASILISK_ATLAS_IDS);

   /**
    1 for main thread, 1 for tracker thread
	should probably be put in bsmod instead
    */
	bs_configureQueuesCount(2);
	bsgfx_ini("Basilisk", 1920, 1080, BS_WINDOW_NO_TITLE_BAR, argc, argv);

	basilisk.context = bs_fetch(BSGFX_CONTEXTS, BSGFX_CONTEXT_MAIN)->context;

	iniContextMenus();

	//bs_Object* title_bar_context = BS_CONTEXT(BASILISK_CONTEXTS, BASILISK_CONTEXT_TITLE_BAR, 0);
	//bs_window(title_bar_context->context, basilisk.context, onTitleBarTick, bs_resolution(basilisk.context).x, 32, "test", 0);
	//bs_swapchain(title_bar_context->context);

	bsmod_onIni();
	bsmod_onLateIni();
	bsgfx_loadScene("engine");

	bsgfx_tick();

	return 0;
}
