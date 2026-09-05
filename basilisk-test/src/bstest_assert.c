#include <bsgfx.h>

int _bstest_package = -1; // not the best place for this external

void bstest_assertSameBitmap(
	int width, 
	int height, 
	int channels_count, 
	unsigned char* bmp_a, 
	unsigned char* bmp_b) 
{
	size_t size = width * height * channels_count;

	int result = memcmp(bmp_a, bmp_b, size);

	if (result != 0) {

	}
}