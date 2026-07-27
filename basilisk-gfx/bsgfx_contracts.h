
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

 /**
  bsgfx_contracts.h

  this file needs to be compatible with both GLSL and C
  since its included in both the game code and shader code
  */

#ifndef BSGFX_CONTRACTS_H
#define BSGFX_CONTRACTS_H

#ifndef BSGFX_GLSL
	#include <stdint.h>

	#define BSGFXAPI _declspec(dllexport)
	typedef unsigned int uint;
	typedef bs_vec2 vec2;
	typedef bs_vec3 vec3;
	typedef bs_vec4 vec4;

	typedef struct bsgfx_InstanceMetadata bsgfx_InstanceMetadata;
	typedef struct bsgfx_InstanceTypeMetadata bsgfx_InstanceTypeMetadata;
	typedef struct bsgfx_InstanceSubtypeMetadata bsgfx_InstanceSubtypeMetadata;
	typedef struct bsgfx_VolumeOffset bsgfx_VolumeOffset;
	typedef struct bsgfx_MaterialContract bsgfx_MaterialContract;

	typedef enum bsgfx_Id bsgfx_Id;

	#define BSGFX_GLSL_CONTRACT static inline
#else
	#define BSGFX_GLSL_CONTRACT
	#define _DEBUG
	#define bsgfx_Id int
#endif



  /*==============================================================================
   * Macros
   *============================================================================*/

	#define BSGFX_MAX_NUM_SUBTYPES 256
	#define BSGFX_MAX_NUM_TEXTURED_VOLUMES 128
	#define BSGFX_MAX_MATERIALS_COUNT 512

   /**
	Subtype flags
	*/
	#define BSGFX_SUBTYPE_HAS_SHADOWS					(1 << 0) // dont use with BSGFX_SUBTYPE_HAS_FINE_SHADOWS
	#define BSGFX_SUBTYPE_PRE_COMPUTE_SHADOWS			(1 << 1)
	#define BSGFX_SUBTYPE_HAS_FINE_SHADOWS				(1 << 3) // dont use with BSGFX_SUBTYPE_HAS_SHADOWS

	/**
	 Instance types
	 */
	#define BSGFX_INSTANCE_TYPE_BONE					0
	#define BSGFX_INSTANCE_TYPE_MESH					1
	#define BSGFX_INSTANCE_TYPE_LINE					2
	#define BSGFX_INSTANCE_TYPE_POINT					3
	#define BSGFX_INSTANCE_TYPE_QUAD					4
	#define BSGFX_INSTANCE_TYPE_MESH_STATIC				5
	#define BSGFX_INSTANCE_TYPE_COUNT					6 // MAKE SURE TO INCREMENT

   /**
    Index output flags
    */
	#define BSGFX_ID_INSTANCE_TYPE_BONE				(1 << BSGFX_INSTANCE_TYPE_BONE)
	#define BSGFX_ID_INSTANCE_TYPE_MESH				(1 << BSGFX_INSTANCE_TYPE_MESH)
	#define BSGFX_ID_INSTANCE_TYPE_LINE				(1 << BSGFX_INSTANCE_TYPE_LINE)
	#define BSGFX_ID_INSTANCE_TYPE_POINT				(1 << BSGFX_INSTANCE_TYPE_POINT)
	#define BSGFX_ID_INSTANCE_TYPE_QUAD				(1 << BSGFX_INSTANCE_TYPE_QUAD)
	#define BSGFX_ID_SELECTED							(1 << (BSGFX_INSTANCE_TYPE_COUNT + 0))
	#define BSGFX_ID_IN_SHADOW							(1 << (BSGFX_INSTANCE_TYPE_COUNT + 1))
	#define BSGFX_ID_IS_WATER							(1 << (BSGFX_INSTANCE_TYPE_COUNT + 2))
	#define BSGFX_ID_HIGHLIGHT							(1 << (BSGFX_INSTANCE_TYPE_COUNT + 3))
	#define BSGFX_ID_IS_PRIMITIVE						(1 << (BSGFX_INSTANCE_TYPE_COUNT + 4))
	#define BSGFX_ID_SHADER_RESERVED_0					(1 << (BSGFX_INSTANCE_TYPE_COUNT + 5))
	#define BSGFX_ID_IS_PREFAB					(1 << (BSGFX_INSTANCE_TYPE_COUNT + 6))
	#define BSGFX_ID_IN_SHADOW_TEXTURED				(1 << (BSGFX_INSTANCE_TYPE_COUNT + 7))
	#define BSGFX_ID_X_AXIS							(1 << (BSGFX_INSTANCE_TYPE_COUNT + 8))
	#define BSGFX_ID_Y_AXIS							(1 << (BSGFX_INSTANCE_TYPE_COUNT + 9))

	#define BSGFX_ID_FONT_IS_SELECTED					BSGFX_ID_SHADER_RESERVED_0

	//#define BSGFX_MESH_KEY 20000
	//#define BSGFX_MESH_HI_RES_SCREEN_KEY 30000
	//#define BSGFX_PREFAB_LO_RES_SCREEN_KEY 80000
	//#define BSGFX_PREFAB_PRIMITIVE_LO_RES_SCREEN_KEY 90000


   /**
    Instance buffer sizes
    */
	#define BSGFX_MESH_INSTANCE_COUNT					(819)
	#define BSGFX_MESH_STATIC_INSTANCE_COUNT			(819)
	#define BSGFX_MESH_2_INSTANCE_COUNT					(819)
	#define BSGFX_MESH_COLOR_INSTANCE_COUNT				(512)
	#define BSGFX_TILE_INSTANCE_COUNT					(4096)
	#define BSGFX_BONE_INSTANCE_COUNT					(128)
	#define BSGFX_LINE_INSTANCE_COUNT					(512)
	#define BSGFX_POINT_INSTANCE_COUNT					(512)
	#define BSGFX_QUAD_LEGACY_INSTANCE_COUNT			(4096 * 2)
	#define BSGFX_QUAD_INSTANCE_COUNT					(4096 * 8)
	#define BSGFX_TEXT_INSTANCE_COUNT					(512)
	#define BSGFX_MAX_NUM_JOINTS						(1024)



   /*==============================================================================
	* Structures
	*============================================================================*/

	struct bsgfx_RayPayload {
		float hitSky;
	};

	struct bsgfx_InstanceTypeMetadata {
		int count;
		int allocated;
		int subtype_count;
		int reserved;
	};

	struct bsgfx_InstanceSubtypeMetadata {
		int index_offset;
		int index_count;
		int instance_offset;
		int instance_count;
		int instance_type;
		int batch_source_id;
		int batch_id;
		uint flags;
	};

	struct bsgfx_VolumeOffset {
		int texture;
		int start;
	};

#define BSGFX_VOLUME_VERTEX_SIZE 6

#define BSGFX_NUM_SHADOW_VERTICES (32768 * BSGFX_VOLUME_VERTEX_SIZE) // just needs to be divisible by the vertex size
#define BSGFX_NUM_SHADOW_DOWN_VERTICES (16386)
#define BSGFX_PRE_COMPUTED_VOLUME_SIZE (131072)
#define BSGFX_NUM_VOLUME_COMPUTATIONS 16

	struct bsgfx_InstanceMetadata {
		uint computed_volume_vertices[BSGFX_NUM_VOLUME_COMPUTATIONS];
		int subtypes_count, textured_volumes_count, b, c;

		int computed_subtype_volume_vertices[BSGFX_MAX_NUM_SUBTYPES];

		bsgfx_InstanceTypeMetadata instance_types[BSGFX_INSTANCE_TYPE_COUNT];
		bsgfx_InstanceSubtypeMetadata instance_subtypes[BSGFX_MAX_NUM_SUBTYPES];
		bsgfx_VolumeOffset textured_volumes[BSGFX_MAX_NUM_TEXTURED_VOLUMES];
	};

	struct bsgfx_InstanceHeader {
		int id;
		int subtype;
		uint16_t material;
		uint16_t flags;
		uint bone_index;
	};

	struct bsgfx_MaterialContract {
		vec4 color;
		int image, width, height, image_binding;
		vec4 hsva;
		vec4 pad;
	};

	struct bsgfx_AtlasTexture { // must be same as bs_AtlasTexture
		vec4 coords;
		int x, y;
		int w, h;
		int split;
		uint flags;
	};



   /*==============================================================================
    * Methods
    *============================================================================*/

	BSGFX_GLSL_CONTRACT uint bsgfx_extractInstanceId(uint index) {
		return index & 0xFFFFu;
	}

	BSGFX_GLSL_CONTRACT uint bsgfx_extractBoneOffset(uint index) {
		return index >> 16;
	}

	BSGFX_GLSL_CONTRACT uint bsgfx_extractBoneCount(uint index) {
		return index & 0xFFFFu;
	}

	BSGFX_GLSL_CONTRACT uint bsgfx_index(uint a, uint b) {
		return (a << 16) | (b & 0xFFFFu);
	}

	BSGFX_GLSL_CONTRACT uint bsgfx_index24(uint a, uint b) {
		return ((a & 0xFFFFFFu) << 8) | (b & 0xFFu);
	}

	BSGFX_GLSL_CONTRACT uint bsgfx_extract24(uint index) {
		return (index >> 8) & 0xFFFFFFu;
	}

	BSGFX_GLSL_CONTRACT uint bsgfx_extract8(uint index) {
		return index & 0xFFu;
	}



  /*==============================================================================
   * Subpass Outputs
   *============================================================================*/

	 /**
	  Low Resolution Subpass 0
	  */
#define BSGFX_LO_SUBPASS_0_OUT_COLOR 0
#define BSGFX_LO_SUBPASS_0_OUT_NORMAL 1
#define BSGFX_LO_SUBPASS_0_OUT_INDEX 2
#define BSGFX_LO_SUBPASS_0_OUT_FLAGS 3
#define BSGFX_LO_SUBPASS_0_OUT_POSITION 4
#define BSGFX_LO_SUBPASS_0_OUT_POSITION_LOCAL 5

#define BSGFX_LO_SUBPASS_0_IN_COLOR 0
#define BSGFX_LO_SUBPASS_0_IN_NORMAL 1
#define BSGFX_LO_SUBPASS_0_IN_INDEX 2
#define BSGFX_LO_SUBPASS_0_IN_FLAGS 3
#define BSGFX_LO_SUBPASS_0_IN_POSITION 4

	/**
	 Low Resolution Subpass 1
	 */
#define BSGFX_LO_SUBPASS_1_OUT_COLOR 0

#define BSGFX_LO_SUBPASS_1_IN_COLOR 0
#define BSGFX_LO_SUBPASS_1_IN_NORMAL 1
#define BSGFX_LO_SUBPASS_1_IN_INDEX 2
#define BSGFX_LO_SUBPASS_1_IN_FLAGS 3
#define BSGFX_LO_SUBPASS_1_IN_POSITION 4

    /**
     Low Resolution UI Subpass 0
     */
#define BSGFX_LO_UI_SUBPASS_0_OUT_COLOR 0
#define BSGFX_LO_UI_SUBPASS_0_OUT_DEPTH 1

	/**
	 High Resolution Subpass 0
	 */
#define BSGFX_HI_SUBPASS_0_OUT_COLOR 0


  /*==============================================================================
   * Bindings
   * TODO: put fonts in separate bind set
   *============================================================================*/

   /**
    Bind set 0
    */
	#define BSGFX_SET_34_24								0
	#define BSGFX_SET_JOINTS							0
	#define BSGFX_SET_MESH_INSTANCES					0
	#define BSGFX_SET_MESH_STATIC_INSTANCES				0
	#define BSGFX_SET_MESH_COLOR_INSTANCES				0
	#define BSGFX_SET_BONE_INSTANCES					0
	#define BSGFX_SET_TILE_INSTANCES					0
	#define BSGFX_SET_LINE_INSTANCES					0
	#define BSGFX_SET_POINT_INSTANCES					0
	#define BSGFX_SET_QUAD_LEGACY_INSTANCES				0
	#define BSGFX_SET_QUAD_INSTANCES					0
	#define BSGFX_SET_TEXT_INSTANCES					0
	#define BSGFX_SET_IMAGE_ATLAS_ANY					0
	#define BSGFX_SET_BUFFER_ATLAS_ANY					0
	#define BSGFX_SET_FONT_STANDARD						0
	#define BSGFX_SET_FONT_SMALL						0
	#define BSGFX_SET_FONT_TEMPLE						0
	#define BSGFX_SET_FONTS								0
	#define BSGFX_SET_64								0
	#define BSGFX_SET_256								0
	#define BSGFX_SET_512								0
	#define BSGFX_SET_IMAGE_LEVEL_THUMBNAIL				0
	#define BSGFX_SET_MATERIALS							0
	#define BSGFX_SET_MINIMAP							0
	#define BSGFX_SET_ACCELERATION_STRUCTURE			0
	#define BSGFX_SET_RAY_TRACE_OUTPUT					0
	#define BSAPP_SET_MATERIAL_TEXTURES					4

	#define BSGFX_BINDING_34_24							0
	#define BSGFX_BINDING_JOINTS						1
	#define BSGFX_BINDING_MESH_INSTANCES				2
	#define BSGFX_BINDING_MESH_COLOR_INSTANCES			3
	#define BSGFX_BINDING_BONE_INSTANCES				4
	#define BSGFX_BINDING_TILE_INSTANCES				5
	#define BSGFX_BINDING_IMAGE_ATLAS_ANY				6
	#define BSGFX_BINDING_BUFFER_ATLAS_ANY				7
	#define BSGFX_BINDING_LINE_INSTANCES				8
	#define BSGFX_BINDING_POINT_INSTANCES				9
	#define BSGFX_BINDING_QUAD_LEGACY_INSTANCES			10
	#define BSGFX_BINDING_TEXT_INSTANCES				11
	#define BSGFX_BINDING_64							12
	#define BSGFX_BINDING_256							13
	#define BSGFX_BINDING_512							14
	#define BSGFX_BINDING_FONTS							15
	#define BSGFX_BINDING_IMAGE_LEVEL_THUMBNAIL			16
	#define BSGFX_BINDING_MATERIALS						17
	#define BSGFX_BINDING_MINIMAP						18
	#define BSGFX_BINDING_QUAD_INSTANCES				19
	#define BSGFX_BINDING_ACCELERATION_STRUCTURE		20
	#define BSGFX_BINDING_RAY_TRACE_OUTPUT				21
	#define BSGFX_BINDING_FONT_CONSOLAS					22
	#define BSGFX_BINDING_FONT_SANS_SERIF				23
	#define BSAPP_BINDING_MATERIAL_TEXTURES				24
	#define BSGFX_BINDING_MESH_STATIC_INSTANCES			25

	#define BSGFX_MAX_FONTS_COUNT						16 // 16 maxPerStageDescriptorSamplers guaranteed

   /**
    Bind set 1
    */
	#define BSGFX_SET_MESH_DATA						1
	#define BSGFX_BINDING_MESH_DATA					4

   /**
    Bind set 2
    */
	#define BSGFX_SET_VOLUME_IN_VERTICES					2
	#define BSGFX_SET_VOLUME_IN_INDICES					2
	#define BSGFX_SET_VOLUME_OUT_VERTICES					2

	#define BSGFX_BINDING_VOLUME_IN_VERTICES_MESH			5
	#define BSGFX_BINDING_VOLUME_IN_INDICES_MESH			6
	#define BSGFX_BINDING_VOLUME_OUT_VERTICES				7

	#define BSGFX_BINDING_VOLUME_IN_VERTICES_BONE			9
	#define BSGFX_BINDING_VOLUME_IN_INDICES_BONE			10

	#define BSGFX_BINDING_VOLUME_IN_VERTICES_MESH_TYPE		11
	#define BSGFX_BINDING_VOLUME_IN_INDICES_MESH_TYPE		12
	#define BSGFX_BINDING_VOLUME_OUT_VERTICES_MESH_TYPE	13

   /**
    Bind set 3
    */
	#define BSGFX_SET_LO_RES_0							3

	#define BSGFX_BINDING_LO_RES_0_COLOR_ATTACHMENT		0
	#define BSGFX_BINDING_LO_RES_0_NORMAL_ATTACHMENT	1
	#define BSGFX_BINDING_LO_RES_0_INDEX_ATTACHMENT		2
	#define BSGFX_BINDING_LO_RES_0_FLAGS_ATTACHMENT		3
	#define BSGFX_BINDING_LO_RES_0_POSITION_ATTACHMENT	4
	#define BSGFX_BINDING_LO_RES_0_DEPTH_ATTACHMENT		5
	#define BSGFX_BINDING_LO_RES_0_SHADOW_ATTACHMENT	6
	#define BSGFX_BINDING_LO_RES_1_COLOR_ATTACHMENT		7
	#define BSGFX_BINDING_LO_RES_0_VERTEX_ATTACHMENT	8

	#define BSGFX_BINDING_LO_RES_0_COLOR_INPUT			9
	#define BSGFX_BINDING_LO_RES_0_NORMAL_INPUT			10
	#define BSGFX_BINDING_LO_RES_0_INDEX_INPUT			11
	#define BSGFX_BINDING_LO_RES_0_FLAGS_INPUT			12
	#define BSGFX_BINDING_LO_RES_0_POSITION_INPUT		13
	#define BSGFX_BINDING_LO_RES_0_DEPTH_INPUT			14
	#define BSGFX_BINDING_LO_RES_UI_0_COLOR_ATTACHMENT	15

   /**
    Bind set 4
    */
	#define BSMOD_ATLAS_ICONS_MATERIALS_BINDING			0
	#define BSMOD_ATLAS_ICONS_PRIMITIVES_BINDING		1
	#define BSMOD_ATLAS_ICONS_PREFABS_BINDING			2
	#define BSMOD_ATLAS_ICONS_COUNT						3 // increment

	#define BSMOD_BIND_SET								4
	#define BSMOD_SET_IMAGE_ATLAS_UI					4
	#define BSMOD_SET_IMAGE_ATLAS_ICONS					4
	#define BSMOD_SET_MATERIAL_TEXTURES					4

	#define BSMOD_BINDING_IMAGE_ATLAS_UI				0
	#define BSMOD_BINDING_IMAGE_ATLAS_ICONS				1
	#define BSMOD_BINDING_MATERIAL_TEXTURES				2
	#define BSMOD_BINDING_UI_OUTPUT						3

	#define BSGFX_MATERIAL_TEXTURE_64					0
	#define BSGFX_MATERIAL_TEXTURE_256					1
	#define BSGFX_MATERIAL_TEXTURE_512					2
	#define BSGFX_MATERIAL_TEXTURE_COUNT				3 // increment


   /**
    Bind set 5
    */
	#define BSGFX_SET_MESH_2_INSTANCES					5
	#define BSGFX_BINDING_MESH_2_INSTANCES				0

#endif