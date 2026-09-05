#ifndef BSTEST_CACHE_H
#define BSTEST_CACHE_H

#include <bsgfx_cache.h>
#include <_bsmod_.h>
#include <bstest.h>

#define BSGFX_PACKAGE _bstest_package



/*==============================================================================
 * Shader Cache
 *============================================================================*/

BSGFX_CACHE_FS(fs_bstest_generic_00)
BSGFX_CACHE_FS(fs_bstest_generic_01)

BSGFX_CACHE_VS(vs_bstest_generic_00)
BSGFX_CACHE_VS(vs_bstest_generic_01)
BSGFX_CACHE_VS(vs_bstest_generic_02)



/*==============================================================================
 * Atlas Cache
 *============================================================================*/

	// BSGFX_CACHE_ATLAS_QUERY(_bsmod_atlases, BSMOD_ATLAS_MATERIAL_ICONS, test0)

#undef BSGFX_PACKAGE
#endif