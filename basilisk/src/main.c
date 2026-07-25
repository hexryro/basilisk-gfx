#include <basilisk-mod.h>
#include <bsgfx_cache.h>

#include <windows.h>
#include <stdio.h>

volatile long has_performed_tracked_changes = 1;

static void onLoadScene() {
	$vs_bsgfx_mesh_color();
	$fs_bsgfx_atlas();

	bsmod_onLoad();
	bsmod_bindAtlases();
}

static bs_Queue* onQueue() {
	bs_Queue* queue = bsmod_onQueue();

	return queue;
}

static void onTick() {
}

static void onModTick() {
	bs_mat4 transform = BS_MAT4_IDENTITY;
	bs_m4Scale(&transform, &BS_V3(100.0, 100.0, 0.0), &transform);

	bsgfx_instanceQuad(bsgfx_subtypes()[BSGFX_SUBTYPE_UI_COLOR], bs_m4x3(&transform), BS_V4(0.0, 0.0, 1.0, 1.0), 0, 0, 0);
}

static void onIni() {
	bsmod_onIni();

	bsmod_onTrack();
	bsmod_savePackage(BSGFX_CONTENT_PATH);
}

static DWORD WINAPI _bsmod_tickAsync(void* param) {
	while (1) {
		InterlockedExchange(&has_performed_tracked_changes, 0);
		bsmod_onTrack();
		InterlockedExchange(&has_performed_tracked_changes, 1);
		Sleep(1000);
	}
}
static void onLateIni() {
	bsmod_onLateIni();

	CreateThread(NULL, 0, _bsmod_tickAsync, NULL, 0, NULL);

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

	const char const* levels[BS_MESSAGE_LEVELS_COUNT] = {
		[BS_MESSAGE_INFO] = "[INFO]",
		[BS_MESSAGE_WARNING] = "[WARNING]",
		[BS_MESSAGE_VALIDATION_ERROR] = "[VALIDATION]",
	};

#ifdef _DEBUG
	const char const* levels_color[BS_MESSAGE_LEVELS_COUNT] = {
		[BS_MESSAGE_INFO] = BS_PRINT_COLOR("[INFO]", BS_PRINT_CYAN),
		[BS_MESSAGE_WARNING] = BS_PRINT_COLOR("[WARNING]", BS_PRINT_YELLOW),
		[BS_MESSAGE_VALIDATION_ERROR] = BS_PRINT_COLOR("[VALIDATION]", BS_PRINT_RED),
	};

	printf("%s %s %s\n", libraries[item->library], levels_color[item->level], item->message);
	if (item->function) {
		printf("    at %s at %s:%d\n", item->function, item->file, item->line);
	}
#endif

	bs_writeLogFileF("%s %s %s\n", libraries[item->library], levels[item->level], item->message);
	if (item->function) {
		bs_writeLogFileF("    at %s at %s:%d\n", item->function, item->file, item->line);
	}
}

// hack to debug validation errors
static void onError() {
}

int main(int argc, char* argv[]) {
	bs_enableValidation();
	bsgfx_enableValidation();
	bsmod_enableValidation();

	bs_Callbacks* core_callbacks = bs_callbacks();
	*core_callbacks = (bs_Callbacks) {
		.log = onLog,
		.error = onError,
	};

	bsgfx_Callbacks* gfx_callbacks = bsgfx_callbacks();
	*gfx_callbacks = (bsgfx_Callbacks) {
		.queue = onQueue,
		.loadScene = onLoadScene,
		.ini = onIni,
		.lateIni = onLateIni,
		.tick = onTick,
	};

	bsmod_Callbacks* mod_callbacks = bsmod_callbacks();
	*mod_callbacks = (bsmod_Callbacks) {
		.tick = onModTick,
	};

	bsgfx_ini("Basilisk", 1920, 1080, argc, argv);

	return 0;
}