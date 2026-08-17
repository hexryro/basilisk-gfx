
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

#ifndef BSMOD_CACHE_H
#define BSMOD_CACHE_H

#include <bsmod_internal.h>
#include <bsgfx_cache.h>

#define BSGFX_PACKAGE _bsmod_.package



  /*==============================================================================
   * Shader Cache
   *============================================================================*/

BSGFX_CACHE_FS(fs_bsmod_rasterize)
BSGFX_CACHE_FS(fs_bsmod_material_icon)
BSGFX_CACHE_FS(fs_bsmod_billboard)

BSGFX_CACHE_VS(vs_bsmod_mesh_instanced)
BSGFX_CACHE_VS(vs_bsmod_billboard)
BSGFX_CACHE_VS(vs_bsmod_tracker_quad_instanced)



  /*==============================================================================
   * Atlas Cache
   *============================================================================*/

BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_MATERIAL_ICONS, test0)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, grid_hover)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, white)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, title_bar_close)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, scrollbar_button)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, material)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, instance)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, increment)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, circle)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, prohibition)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, expand)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, light)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, light_add)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, sun)
BSGFX_CACHE_ATLAS_QUERY(BSMOD_ATLASES, BSMOD_ATLAS_UI, sun_add)



#undef BSGFX_PACKAGE
#endif