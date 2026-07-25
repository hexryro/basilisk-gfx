
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

#ifndef BASILISK_PIPELINE_H
#define BASILISK_PIPELINE_H

void basilisk_renderDither();
void basilisk_renderUIStencil();
void basilisk_renderUISolid();
void basilisk_renderUI();
void basilisk_renderRoundedQuads();
void basilisk_renderPrefabOutlines();
void basilisk_renderFontSubtype(int subtype, bsgfx_Id font_id, bs_Shader* fragment_shader);
void basilisk_renderTiles();
void basilisk_renderSelectedTile();
void basilisk_renderUIPost();
void basilisk_renderCones();
void basilisk_renderPoints();
void basilisk_renderLines();
void basilisk_renderDepthlessLines();

void 
basilisk_pipeline();

#endif