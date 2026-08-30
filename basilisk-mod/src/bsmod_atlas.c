
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

BSMODAPI bsmod_TextureInfo* _bsmod_packAtlasTextureN(
	bsmod_AtlasPacker* packer, 
	unsigned char* data, 
	PFN_bsmod_getAtlasTextureData get_data,
	void* param, 
	int width, 
	int height, 
	int category, 
	int id,
	char* name, 
	int name_length) 
{
	bsmod_TextureInfo info = {
		.name = strdup(name),
		.name_length = name_length,
		.data = data,
		.get_data = get_data,
		.param = param,
		.page = -1,
		.category = category,
		.id = id,
	};

	stbrp_rect rect = {
		.w = width,
		.h = height,
		.id = packer->info.count
	};

	bs_pushBack(&packer->rects, &rect);
	return bs_pushBack(&packer->info, &info);
}

BSMODAPI bsmod_AtlasPacker _bsmod_createAtlasPacker() {
	return (bsmod_AtlasPacker) {
		.info = bs_list(sizeof(bsmod_TextureInfo), 64),
		.rects = bs_list(sizeof(stbrp_rect), 64),
	};
}

BSMODAPI void _bsmod_destroyAtlasPacker(bsmod_AtlasPacker* packer) {
	bs_destroyList(&packer->rects);
	bs_destroyList(&packer->info);
}

BSMODAPI bs_Result _val_bsmod_packAtlas(bsmod_AtlasPacker* packer, int width, int height, int channels_count, char* package_name, char* resource_name, bool allow_paging) {
	BSMOD_VALIDATE(packer->info.count == packer->rects.count, BS_RESULT_OK,);

	return _bsmod_packAtlas(packer, width, height, channels_count, package_name, resource_name, allow_paging);
}

BSMODAPI bs_Result _bsmod_packAtlas(bsmod_AtlasPacker* packer, int width, int height, int channels_count, char* package_name, char* resource_name, bool allow_paging) {
	const int padding = 1;

	bs_Result result;

	bs_BatlHeader header = {
		.magic = BS_BATL_MAGIC,
		.version = 1,
		.channels_count = channels_count,
		.width = width,
		.height = height,
		.images_count = packer->info.count,
	};

	size_t total_name_lengths = 0;
	for (int i = 0; i < header.images_count; i++) {
		bsmod_TextureInfo* info = bs_fetchUnit(&packer->info, i);
		total_name_lengths += info->name_length;
	}

	stbrp_node* nodes = bs_alloca(header.width * sizeof(stbrp_node));

	stbrp_rect* original_rects = packer->rects.data;
	stbrp_rect* remaining_rects = bs_alloca(header.images_count * sizeof(stbrp_rect));

	memcpy(remaining_rects, packer->rects.data, header.images_count * sizeof(stbrp_rect));

	for (int i = 0; i < header.images_count; i++) {
		remaining_rects[i].w += padding * 2;
		remaining_rects[i].h += padding * 2;
	}

	packer->rects.count = 0;

	int remaining = header.images_count;
	while (remaining > 0) {
		stbrp_context ctx;
		stbrp_init_target(&ctx, header.width, header.height, nodes, header.width);

		stbrp_pack_rects(&ctx, remaining_rects, remaining);

		int j = 0;
		for (int i = 0; i < remaining; i++) {
			stbrp_rect* rect = remaining_rects + i;

			if (rect->was_packed) {
				bsmod_TextureInfo* info = bs_fetchUnit(&packer->info, rect->id);

				info->page = header.pages_count;

				rect->x += padding;
				rect->y += padding;
				rect->w -= padding * 2;
				rect->h -= padding * 2;

				original_rects[packer->rects.count++] = *rect;
			}
			else {
				remaining_rects[j] = *rect;

				j++;
			}
		}

		remaining = j;
		header.pages_count++;

		if (!allow_paging)
			break;
	}

   /**
    Allocate memory
    */
	size_t total_size = 0;
	size_t total_size_excluding_binary = 0;

	total_size += sizeof(bs_BatlHeader);
	total_size += header.images_count * sizeof(bs_BatlImage);

	for (int i = 0; i < header.images_count; i++) {
		bsmod_TextureInfo* info = bs_fetchUnit(&packer->info, i);
		total_size += info->name_length + 2; // \0\n
	}
	total_size_excluding_binary = total_size;
	total_size += header.pages_count * width * height * header.channels_count;

	unsigned char* batl = bs_malloc(total_size);

   /**
    Pack atlas
    */
	unsigned char* offset = batl;
	offset += sizeof(bs_BatlHeader);
	memset(batl + total_size_excluding_binary, 0, (total_size - total_size_excluding_binary));

	for (int i = 0; i < header.images_count; i++) {
		stbrp_rect* rect = bs_fetchUnit(&packer->rects, i);
		bsmod_TextureInfo* info = bs_fetchUnit(&packer->info, rect->id);

		bs_BatlImage batl_image = {
			.x = rect->x,
			.y = rect->y,
			.w = rect->w,
			.h = rect->h,
			.page = info->page,
			.category = info->category,
			.name_length = info->name_length,
		};

		memcpy(offset, &batl_image, sizeof(bs_BatlImage));
		offset += sizeof(bs_BatlImage);

		memcpy(offset, info->name, info->name_length);
		offset += info->name_length;

		memcpy(offset, "\0\n", 2);
		offset += 2;

		if (info->get_data)
			info->data = info->get_data(packer, rect->id);

		if (!info->data)
			goto next;

		int w = width;

		// lodepng is upside down (:
		unsigned char* atlas_offset = batl + total_size_excluding_binary;
		atlas_offset += info->page * width * height * header.channels_count;
		for (int y = 0; y < rect->h; y++) {
			unsigned char* dst = atlas_offset;
			dst += (rect->x) * header.channels_count;
			dst += (rect->y + y) * w * header.channels_count;

			unsigned char* src = info->data;
			src += y * rect->w * header.channels_count;

			memcpy(dst, src, rect->w * header.channels_count);
		}

	next:void;
		//free(info->name);
	}

	memcpy(batl, &header, sizeof(bs_BatlHeader));

	result = bs_savePngN(batl + total_size_excluding_binary, BS_IV2(width, height), BS_PNG_RGBA, BS_CONSTANT_STRING("test.png"));

	if (package_name && resource_name)
		result = _bsmod_packResource(BS_RESOURCE_ATLAS, batl, total_size, package_name, resource_name);
	bs_free(batl);
//	if (result != BS_RESULT_OK)
//		return result;

	return BS_RESULT_OK;
}