
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

#include <bsgfx_internal.h>

BSGFXAPI bs_vec3 _bsgfx_spawnPosition(bs_vec2 coords, float y) {
    return (bs_vec3) {
        .x = 2.0 * coords.x + 1.0,
        .z = 2.0 * (-coords.y - 1.0) + y + 1.0,
        .y = y,
    };
}

static void _bsgfx_mapSpawner(bsgfx_RawSpawner* unmapped, bsgfx_Spawner* mapped) {
    *mapped = (bsgfx_Spawner){
        .position = unmapped->position,
        .spawn_type = unmapped->spawn_type,
        .spawn_name = unmapped->spawn_name,
        .flags = unmapped->flags,
        .spawn_periodicity = unmapped->spawn_periodicity,
        .material_id = unmapped->material_name ? _bsgfx_queryMaterialHash(unmapped->material_name)->id : 0,
    };
}

// static void _bsgfx_onSelectSpawner(int id) {
//     _bsgfx_deselectAll();
// }

BSGFXAPI void _bsgfx_loadSpawners(int package_id) {
    _bsgfx_type(
        BSGFX_TYPE_SPAWNER, 
        package_id, 
        BSGFX_SPAWNER_VERSION,
        "spawners", "spawner",
        sizeof(bsgfx_RawSpawner), sizeof(bsgfx_Spawner), 
        _bsgfx_mapSpawner, 
        0, 
        0, 
        0, 
        0);
   // _bsgfx_onSelect(BSGFX_TYPE_SPAWNER, _bsgfx_onSelectSpawner);
}

BSGFXAPI void _bsgfx_spawn(bsgfx_Spawner* spawner) {
    return;
    switch (spawner->spawn_type) {
    case BSGFX_SPAWNER_ITEM:
       // bs_throwBasilisk(BSX_NOT_IMPLEMENTED);
        /*
        bs_Model* model = $items();
        bs_Mesh* mesh = bs_queryMeshHash(model, spawner->spawn_name, NULL);
        _bsgfx_spawnItem(mesh - model->meshes, bs_v3AddY(spawner->position, 2.0), 10.0, spawner->material_id);
        */
        break;
    case BSGFX_SPAWNER_ENTITY:
       // bs_throwBasilisk(BSX_NOT_IMPLEMENTED);

       //bsgfx_Script* script = bs_queryHash(NULL, "lua", spawner->spawn_name, 0).model;
       //bsgfx_spawnEntity(script, spawner->position);
        break;
    }
}

/*
struct bsgfx_SpawnerMenuParams {
    int id;
    int clicked_spawner;
};

static void _bsgfx_onClickSpawn(bool confirm, struct bsgfx_SpawnerMenuParams* params) {
    if (!confirm) return;

    bsgfx_Spawner* spawner = _bsgfx_get(BSGFX_TYPE_SPAWNER, params->clicked_spawner);
    _bsgfx_spawn(spawner);
}

static void _bsgfx_onClickDeleteSpawner(bool confirm, struct bsgfx_SpawnerMenuParams* params) {
    if (!confirm) return;

    bsmod_delete(BSGFX_TYPE_SPAWNER, params->clicked_spawner);
}

static bool _bsgfx_instanceSpawner(bs_vec3 position, int id, const char* material) {
    _bsgfx_meshInstance(_bsgfx_subtypes_[BSGFX_SUBTYPE_BIPYRAMID], &(bsgfx_MeshInstance) {
        .transform = bs_rotate(bs_translate(BS_MAT4_IDENTITY, bs_v3AddY(position, 1.0)), bs_qFromDegreesV3(0.0, bs_elapsedTime() * 60.0, 0.0))
    }, 0, id, _bsgfx_queryMaterial(material)->id);

    return _bsgfx_app_.hovering.subtype == _bsgfx_subtypes_[BSGFX_SUBTYPE_BIPYRAMID] && _bsgfx_app_.hovering.instance_id == id;
}

void _bsgfx_instanceSpawners() {
    if (!_bsgfx_settings_.draw_spawners)
        return;

    const float rotation_speed = 30.0;
    bs_vec4 rotation = bs_qFromDegreesV3(0.0, bs_elapsedTime() * rotation_speed, 0.0);

    static struct bsgfx_SpawnerMenuParams params;

    for (int i = 0; i < _bsgfx_count(BSGFX_TYPE_SPAWNER); i++) {
        bsgfx_Spawner* spawner = _bsgfx_get(BSGFX_TYPE_SPAWNER, i);

        char* name = NULL;
        int id = -1;
        bool hovering = false;
        switch (spawner->spawn_type) {
        case BSGFX_SPAWNER_ITEM:
            bs_Model* model = $items();
            bs_Mesh* mesh = bs_queryMeshHash(model, spawner->spawn_name, NULL);

            name = mesh->name;
           // hovering = _bsgfx_instanceItemPreview(BSGFX_ITEM_SUBTYPE, spawner->position, mesh->name_hash, i);
            id = mesh - model->meshes;
            // _bsgfx_obbInstance(&mesh->aabb, BS_BLACK, &transform);
            hovering = _bsgfx_instanceSpawner(spawner->position, i, "red");
            break;
        case BSGFX_SPAWNER_ENTITY: 
            bsgfx_Script* script = bs_queryHash(NULL, "lua", spawner->spawn_name, 0).data;
            bsgfx_Script* scripts = bs_resource(BSGFX_RESOURCE_SCRIPT, 0);

            name = script->name;

           // hovering = _bsgfx_instanceScriptPreview(spawner->position, script->name, false);
            id = script - scripts;
            hovering = _bsgfx_instanceSpawner(spawner->position, i, "green");
            break;
        }
        
        if (hovering && !_bsgfx_app_.menu_blocked) {
            //if (!_bsgfx_quickMenuEnabled())
            //    _bsgfx_instanceHint(bs_windowCursorPosition(bs_scope()->context), name);

            if (bs_inputDownOnce(BS_LEFT_MOUSE_BUTTON)) {
                bsmod_select(BSGFX_TYPE_SPAWNER, i);
            }

            if (bs_rightClickOnce()) {
                params = (struct bsgfx_SpawnerMenuParams){
                    .clicked_spawner = i,
                    .id = id,
                };

                _bsgfx_enableRightClickMenu((bsgfx_RightClickMenu) {
                    .buttons = {
                        {
                            .name = "spawn",
                            .on_click = _bsgfx_onClickSpawn,
                        },
                        {
                            .name = "delete",
                            .on_click = _bsgfx_onClickDeleteSpawner,
                            .confirm = true,
                        }
                    }
                }, &params);
            }
        }

    }
}
*/