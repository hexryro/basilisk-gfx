
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

#include <bsmod_internal.h>

#include <string.h>
#include <stdlib.h>
#include <assert.h>

BSGFXAPI void _bsmod_saveBiff() {
	bs_BiffHeader header = {
		.magic = BS_BIFF_MAGIC,
		.version = 1,
	};
}

typedef struct {
	char* name;
	int name_length;
	unsigned char* bmp;
	size_t size;
} bsmod_BiffInfo;

typedef struct {
	bs_BiffHeader* header;
	bs_List* output;
	char* resource_name;
	size_t total_images_size;
	size_t total_name_lengths;
} bsmod_FileGatherParams;

static bs_Result _bsmod_gatherFileInfo(bs_FileInfo info, void* p) {
    bsmod_FileGatherParams* param = p;

	char* file_extension = bs_fileExtension(info.path);

	if (strcmp(file_extension, "png") == 0) {
		int width = 0, height = 0;

		bs_PngData png_data;
		bs_loadPng(info.path, param->header->channels_count, &png_data);

		if (param->header->width == 0) { // dimensions = first texture dimensions
			param->header->width = width;
			param->header->height = height;
		}
		else if (width != param->header->width || height != param->header->height) {
			bs_warnF("Image \"%s\" (w = %d, h = %d) could not be added to image array \"%s\" (w = %d, h = %d) due to mismatching dimensions\n",
				info.path, width, height, param->resource_name, param->header->width, param->header->height);

			return BS_RESULT_OK;
		}

		file_extension[-1] = '\0';
		char* name = bs_fileName(info.path);
		bsmod_BiffInfo* result = bs_pushBack(param->output, &(bsmod_BiffInfo) {
			.name = strdup(name),
			.name_length = strlen(name),
			.bmp = png_data.data,
			.size = width * height * param->header->channels_count,
		});
		file_extension[-1] = '.';

		param->total_images_size += result->size;
		param->total_name_lengths += result->name_length + 2;
	}

	return BS_RESULT_OK;
}

BSMODAPI bs_Result _bsmod_packImageDirectory(char* directory_name, char* package_name, char* resource_name) {
	bs_Result result;

	bs_List images = bs_list(sizeof(bsmod_BiffInfo), 32);

	bs_BiffHeader header = {
		.magic = BS_BIFF_MAGIC,
		.version = 1,
		.channels_count = 4,
	};

	bsmod_FileGatherParams param = {
		.header = &header,
		.output = &images,
		.resource_name = resource_name,
	};

	result = bs_foreachFile(_bsmod_gatherFileInfo, &param, directory_name);
	if (result != BS_RESULT_OK)
		return result;

	const size_t total_size_excluding_binary = sizeof(bs_BiffHeader) + sizeof(bs_BiffPointer) * images.count + param.total_name_lengths;
	const size_t total_size = total_size_excluding_binary + param.total_images_size;

	unsigned char* biff = bs_malloc(total_size);

	size_t pointer_offset = sizeof(bs_BiffHeader);
	size_t binary_offset = total_size_excluding_binary;

	for (int i = 0; i < images.count; i++) {
		bsmod_BiffInfo* image = bs_fetchUnit(&images, i);

		// image header
		memcpy(biff + pointer_offset, &(bs_BiffPointer) {
			.name_length = image->name_length,
			.offset = binary_offset,
			.size = image->size,
		}, sizeof(bs_BiffPointer));
		pointer_offset += sizeof(bs_BiffPointer);

		// image name
		memcpy(biff + pointer_offset, image->name, image->name_length);
		pointer_offset += image->name_length;
		memcpy(biff + pointer_offset, "\0\n", 2);
		pointer_offset += 2;

		// image data
		assert((binary_offset + image->size) <= total_size);
		memcpy(biff + binary_offset, image->bmp, image->size);
		binary_offset += image->size;

		free(image->name);
		free(image->bmp);
	}

	header.images_count = images.count;
	memcpy(biff, &header, sizeof(bs_BiffHeader));

	bs_destroyList(&images);

	result = _bsmod_packResource(BS_RESOURCE_IMAGE, biff, total_size, package_name, resource_name);
	bs_free(biff);
	if (result != BS_RESULT_OK)
		return result;

	return BS_RESULT_OK;
}
