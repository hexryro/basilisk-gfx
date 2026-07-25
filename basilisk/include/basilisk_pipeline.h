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