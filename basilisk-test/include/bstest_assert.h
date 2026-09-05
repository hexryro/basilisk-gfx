#ifndef BSTEST_ASSERT_H
#define BSTEST_ASSERT_H

void 
bstest_assertSameBitmap(
	int width,
	int height,
	int channels_count,
	unsigned char* bmp_a,
	unsigned char* bmp_b);

#endif