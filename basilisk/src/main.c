
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

#include <windows.h>
#include <stdio.h>
#include <threads.h>

Basilisk basilisk = {
	.sources = { -1 },
	.package_id = -1,
};

static void basilisk_loadFontCollection(bs_Object* object) {/*
	bs_Sampler* nearest_sampler = bs_fetch(BSGFX_SAMPLERS, BSGFX_SAMPLER_NEAREST)->sampler;

	bs_Object* sans_serif_16 = BS_FONT(BSGFX_FONTS, BSGFX_FONT_SANS_SERIF_16, 0);
	result = bs_loadFont(sans_serif_16, _bsmod_.package, "fonts/sans-serif_16", BSGFX_ALPHABET_DEFAULT, 16.0, 0);
	if (result == BS_RESULT_OK)
		bs_bindFont(sans_serif_16->font, nearest_sampler, BSGFX_SET_FONTS, BSGFX_BINDING_FONT_SANS_SERIF);

	bs_Object* quad_instanced_batch = bs_fetch(BSGFX_BATCHES, BSGFX_BATCH_QUAD_INSTANCED);
	bs_Range range = {
		.num = 6, // single quad
	};
	_bsmod_subtypes_[BSMOD_SUBTYPE_FONT_SANS_SERIF] = bsgfx_subtype(BSGFX_INSTANCE_TYPE_QUAD, quad_instanced_batch->batch, 0, range);
	*/
}

static void onLoadScene() {
	bsgfx_test(); // temp testing fonts
	$vs_bsgfx_mesh_color();
	$fs_bsgfx_atlas();

	basilisk_createRenderers();
		//basilisk_loadFonts();

	bs_loadPackage(&basilisk.package_id, "content/basilisk.bpak");
	bsmod_iniPackage(basilisk.package_id);

	bs_Queue* queue = bs_fetch(BSGFX_QUEUES, BSGFX_QUEUE_SINGLE_TIMES)->queue;

	bs_Object* atlas = BS_ATLAS(-1, -1, 0);
	bs_loadAtlasN(queue, atlas, basilisk.package_id, 0, BS_CONSTANT_STRING("temp"));

	bsmod_onLoad();
	bsmod_bindAtlases();
}

static bs_Queue* onQueue() {
	bs_Queue* queue = bsmod_onQueue();

	return NULL;
}

static void onTick() {
	_bsmod_onTick();

	bs_mat4 transform = BS_MAT4_IDENTITY;
	bs_m4Scale(&transform, &BS_V3(100.0, 100.0, 0.0), &transform);

	basilisk_instantiateTitleBarUI();
}

static void onModTick() {

}

static void onIni() {
	basilisk.context = bs_fetch(BSGFX_CONTEXTS, BSGFX_CONTEXT_MAIN)->context;

	bsmod_onIni();
}

static void onLateIni() {
	bsmod_onLateIni();

	bsgfx_loadScene("engine");
}

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

// hack to debug validation errors
static void onError() {
}

static void basilisk_configureWindow() {
	bs_overrideTitleBar(BASILISK_TITLE_BAR_HEIGHT);
}

int main(int argc, char* argv[]) {
	bs_enableValidation();
	bsgfx_enableValidation();
	bsmod_enableValidation();

	basilisk.main_thread_id = thrd_current()._Tid;
	//return 0;

	bs_Callbacks* core_callbacks = bs_callbacks();
	*core_callbacks = (bs_Callbacks) {
		.log = onLog,
		.error = onError,
		.configureWindow = basilisk_configureWindow,
	};

	bsgfx_Callbacks* gfx_callbacks = bsgfx_callbacks();
	*gfx_callbacks = (bsgfx_Callbacks) {
		.queue = onQueue,
		.loadScene = onLoadScene,
		.ini = onIni,
		.lateIni = onLateIni,
		.tick = onTick,
		.pipeline = basilisk_pipeline,
	};

	bsmod_Callbacks* mod_callbacks = bsmod_callbacks();
	*mod_callbacks = (bsmod_Callbacks) {
		.tick = onModTick,
	};

	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_IMAGE, BASILISK_IMAGES_COUNT, BASILISK_IMAGE_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_SAMPLER, BASILISK_SAMPLERS_COUNT, BASILISK_SAMPLER_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_BUFFER, BASILISK_BUFFERS_COUNT, BASILISK_BUFFER_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_QUEUE, BASILISK_QUEUES_COUNT, BASILISK_QUEUE_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_BATCH, BASILISK_BATCHES_COUNT, BASILISK_BATCH_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_RENDERER, BASILISK_RENDERERS_COUNT, BASILISK_RENDERER_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_RAY_TRACER, BASILISK_RAY_TRACERS_COUNT, BASILISK_RAY_TRACER_IDS);
	BS_CONFIGURE_SOURCE(basilisk.sources, BS_OBJECT_ATLAS, BASILISK_ATLASES_COUNT, BASILISK_ATLAS_IDS);

	bsgfx_ini("Basilisk", 1920, 1080, argc, argv);

	return 0;
}