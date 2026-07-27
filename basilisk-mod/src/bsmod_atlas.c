
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
#include <stb_rect_pack/stb_rect_pack.h>
#include <string.h>

BSMODAPI void _bsmod_packAtlasTexture(bsmod_AtlasPacker* packer, char* name, bs_RGBA* data, int width, int height, int category) {
	bsmod_TextureInfo info = {
		.name = strdup(name),
		.name_length = strlen(name),
		.data = data,
		.category = category,
	};

	stbrp_rect rect = {
		.w = width,
		.h = height,
	};

	bs_pushBack(&packer->info, &info);
	bs_pushBack(&packer->rects, &rect);
}

BSMODAPI bsmod_AtlasPacker _bsmod_createAtlasPacker() {
	return (bsmod_AtlasPacker) {
		.info = bs_list(sizeof(bsmod_TextureInfo), 64),
		.rects = bs_list(sizeof(stbrp_rect), 64),
	};
}

BSMODAPI bs_Result _val_bsmod_packAtlas(bsmod_AtlasPacker* packer, int width, int height, char* package_name, char* resource_name) {
	BSMOD_VALIDATE(packer->info.count == packer->rects.count, BS_RESULT_OK,);

	return _bsmod_packAtlas(packer, width, height, package_name, resource_name);
}

BSMODAPI bs_Result _bsmod_packAtlas(bsmod_AtlasPacker* packer, int width, int height, char* package_name, char* resource_name) {
	bs_Result result;

	bs_BatlHeader header = {
		.magic = BS_BATL_MAGIC,
		.version = 1,
		.channels_count = 4,
		.width = width,
		.height = height,
	};

	size_t total_name_lengths = 0;
	for (int i = 0; i < packer->info.count; i++) {
		bsmod_TextureInfo* info = bs_fetchUnit(&packer->info, i);
		total_name_lengths += info->name_length;
	}

	const size_t total_size_excluding_binary = sizeof(bs_BatlHeader) + sizeof(bs_BatlPointer) * packer->info.count + total_name_lengths;
	const size_t atlas_size = header.width * header.height * header.channels_count;
	const size_t total_size = total_size_excluding_binary + atlas_size;

	unsigned char* batl = bs_malloc(total_size);

	size_t pointer_offset = sizeof(bs_BatlHeader);
	header.binary_offset = total_size_excluding_binary;

	memset(batl + header.binary_offset, 0, atlas_size);

	stbrp_context ctx;
	stbrp_node* nodes = _alloca(header.width * sizeof(stbrp_node));

	stbrp_init_target(&ctx, header.width, header.height, nodes, header.width);
	stbrp_pack_rects(&ctx, packer->rects.data, packer->info.count);

	const int padding = 0;
	bs_BatlPointer* dbg = batl + pointer_offset; 
	for (int i = 0; i < packer->info.count; i++) {
		bsmod_TextureInfo* image = bs_fetchUnit(&packer->info, i);
		stbrp_rect* rect = bs_fetchUnit(&packer->rects, i);

		// image header
		memcpy(batl + pointer_offset, &(bs_BatlPointer) {
			.name_length = image->name_length,
			.x = rect->x,
			.y = rect->y,
			.w = rect->w,
			.h = rect->h,
			.category = image->category,
		}, sizeof(bs_BatlPointer));
		pointer_offset += sizeof(bs_BatlPointer);

		// image name
		memcpy(batl + pointer_offset, image->name, image->name_length);
		pointer_offset += image->name_length;
		memcpy(batl + pointer_offset, "\0\n", 2);
		pointer_offset += 2;

		int w = header.width - padding;
		
		// lodepng is upside down (:
		for (int y = 0; y < rect->h; y++) {
			unsigned char* dst = batl + header.binary_offset;
			dst += (rect->x + padding) * header.channels_count;
			dst += (rect->y + padding + y) * w * header.channels_count;

			unsigned char* src = image->data;
			src += y * rect->w * header.channels_count;

			memcpy(dst, src, rect->w * header.channels_count);
		}

		free(image->name);
	}
	
	header.images_count = packer->info.count;
	memcpy(batl, &header, sizeof(bs_BatlHeader));

	bs_destroyList(&packer->rects);
	bs_destroyList(&packer->info);

	//result = bs_savePng(batl + header.binary_offset, BS_IV2(width, height), BS_PNG_RGBA, BS_CONSTANT_STRING("test.png"));

	result = _bsmod_packResource(BS_RESOURCE_ATLAS, batl, total_size, package_name, resource_name, strlen(resource_name));
	bs_free(batl);
//	if (result != BS_RESULT_OK)
//		return result;

	return BS_RESULT_OK;
}