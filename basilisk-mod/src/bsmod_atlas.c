
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

/*
void _bsmod_packAtlas(bsmod_AtlasPacker* packer, int width, int height, char* package, char* resource_name) {
	stbrp_context ctx;
	stbrp_node* nodes = _alloca(width * sizeof(stbrp_node));

	stbrp_init_target(&ctx, width, height, nodes, width);
	stbrp_pack_rects(&ctx, packer->rects.data, packer->rects.count);

	const int padding = 0;
	bs_RGBA* atlas = bs_calloc(4, width * height);
	bs_Json json = bs_emptyJson();
	bs_ensureJsonMutable(&json);

	for (int i = 0; i < packer->rects.count; i++) {
		bsmod_TextureInfo* texture = bs_fetchUnit(&packer->info, i);
		stbrp_rect* rect = bs_fetchUnit(&packer->rects, i);

		const int pixels_count = rect->w * rect->h;
		bool has_alpha = false, is_solid = true;
		bs_ivec4 color_sum = { 0 };

		for (int j = 0; j < pixels_count; j++) {
			bs_RGBA* color = texture->data + j;

			if (color->a != 0 && color->a != 255)
				is_solid = false;
			if (color->a != 255)
				has_alpha = true;

			color_sum.x += color->r;
			color_sum.y += color->g;
			color_sum.z += color->b;
			color_sum.w += color->a;
		}

		bs_JsonValue obj = bs_jsonObject(&json);
		bs_Json root = bs_jsonRoot(&json, obj.as_object);

		bs_ensureJson(&root, bs_jsonValue(rect->w), "w");
		bs_ensureJson(&root, bs_jsonValue(rect->h), "h");
		bs_ensureJson(&root, bs_jsonValue(rect->x), "x");
		bs_ensureJson(&root, bs_jsonValue(rect->y), "y");
		bs_ensureJson(&root, bs_jsonValue(has_alpha), "hasAlpha");
		bs_ensureJson(&root, bs_jsonValue(is_solid), "isSolid");
		bs_ensureJson(&root, bs_jsonValue(BS_RGBA(
			color_sum.x / pixels_count,
			color_sum.y / pixels_count,
			color_sum.z / pixels_count,
			color_sum.w / pixels_count
		)), "averageColor");

		bs_ensureJsonF(&json, obj, "table.%s", texture->name);

		int w = width - padding;

		for (int y = 0; y < rect->h; y++) {
			bs_RGBA* dst = atlas;
			dst += rect->x + padding;
			dst += (rect->y + padding + y) * w;

			bs_RGBA* src = texture->data;
			src += y * rect->w;

			memcpy(dst, src, rect->w * 4);
		}

		free(texture->name);
	}

	char* raw = bs_saveJson(&json, BS_JSON_PRETTY);

	size_t png_data_size = 0;
	unsigned char* png_data = bs_encodePng(&png_data_size, atlas, bs_iv2(width, height), BS_PNG_RGBA);

	_bsmod_packResource(BS_RESOURCE_BINARY, raw, strlen(raw), package, "atlas/metadata/%s", resource_name);
	_bsmod_packResource(BS_RESOURCE_ATLAS, png_data, png_data_size, package, "atlas/%s", resource_name);

	bs_saveFile("test.png", png_data, png_data_size);
	free(png_data);
	bs_free(atlas);
	bs_destroyJson(&json);
	bs_destroyList(&packer->rects);
	bs_destroyList(&packer->info);
}
*/

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

	result = bs_savePng(batl + header.binary_offset, BS_IV2(width, height), BS_PNG_RGBA, BS_CONSTANT_STRING("test.png"));
	if (result != BS_RESULT_OK) {
		bs_free(batl);
		return result;
	}

	result = _bsmod_packResource(BS_RESOURCE_ATLAS, batl, total_size, package_name, resource_name, strlen(resource_name));
	bs_free(batl);
//	if (result != BS_RESULT_OK)
//		return result;

	return BS_RESULT_OK;
}