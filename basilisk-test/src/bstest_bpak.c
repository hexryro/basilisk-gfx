#include <bstest.h>
#include <bstest_cache.h>
#include <bstest_assert.h>
#include <bsgfx.h>
#include <bsmod_bpak.h>
#include <bsmod_compile.h>
#include <_bsmod_.h>

#define BSTEST_SHADER_PATH "project/basilisk-test/shaders/"

static void bstest_compileShader(const char* path, const char* output_name) {
	if (!bs_fileExists(path))
		return;

	printf("Compiling \"%s\"\n", path);
	bool success = bsmod_compileShader(path, output_name, BSTEST_CONTENT_PATH);
	if (success) {
	}
}

BSTESTAPI void bstest_create_and_edit_resources(bstest_TestData data) {
	bstest_loadPackage();
	//$vs_bstest_generic_00();

	for (int i = 0; i < 1000; i++) {
		bstest_compileShader(BSTEST_SHADER_PATH "frag/fs_bstest_generic_00.frag", "shaders/fs_bstest_generic_00.frag");
		bsmod_savePackage(BSTEST_CONTENT_PATH);

		bstest_compileShader(BSTEST_SHADER_PATH "frag/fs_bstest_generic_01.frag", "shaders/fs_bstest_generic_00.frag");
		bsmod_savePackage(BSTEST_CONTENT_PATH);
		//bstest_compileShader(BSTEST_SHADER_PATH "vert/vs_bstest_generic_01.vert", "shaders/vs_bstest_generic_00.vert");
		//bsmod_savePackage(BSTEST_CONTENT_PATH);

	}

	printf("test\n");

	exit(1);
	//bsmod_rasterizePrimitiveIcons();
}