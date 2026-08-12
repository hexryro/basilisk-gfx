
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

void basilisk_renderDither(bs_RendererScope* scope, bs_Queue* queue);
void basilisk_renderUIStencil(bs_RendererScope* scope, bs_Queue* queue);
void basilisk_renderUISolid(bs_RendererScope* scope, bs_Queue* queue);
void basilisk_renderUI(bs_RendererScope* scope, bs_Queue* queue);
void basilisk_renderRoundedQuads(bs_RendererScope* scope, bs_Queue* queue);
void basilisk_renderPrefabOutlines(bs_RendererScope* scope, bs_Queue* queue);
void basilisk_renderFontSubtype(bs_RendererScope* scope, bs_Queue* queue, int subtype, bsgfx_Id font_id, bs_Shader* fragment_shader);
void basilisk_renderTiles(bs_RendererScope* scope, bs_Queue* queue);
void basilisk_renderSelectedTile(bs_RendererScope* scope, bs_Queue* queue);
void basilisk_renderUIPost(bs_RendererScope* scope, bs_Queue* queue);
void basilisk_renderCones(bs_RendererScope* scope, bs_Queue* queue);
void basilisk_renderPoints(bs_RendererScope* scope, bs_Queue* queue);
void basilisk_renderLines(bs_RendererScope* scope, bs_Queue* queue);
void basilisk_renderDepthlessLines(bs_RendererScope* scope, bs_Queue* queue);

void 
basilisk_pipeline();

#endif