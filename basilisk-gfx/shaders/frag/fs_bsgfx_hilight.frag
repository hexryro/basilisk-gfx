#version 450
#extension GL_ARB_shading_language_include : require

#include "project/basilisk-gfx/shaders/bsgfx.glsl"
//#include "project/basilisk-gfx/shaders/bsgfx_mesh.glsl"

layout (location = BSGFX_LO_SUBPASS_1_OUT_COLOR) out vec4 out_color;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 in_normal;
layout(location = 3) in vec3 in_world_position;
layout(location = 4) in vec3 in_texture;
layout(location = 5) flat in uint in_instance;
layout(location = 6) flat in uint in_flags;
layout(location = 7) flat in uint in_material;
layout(location = 8) in float in_depth;

layout (input_attachment_index = BSGFX_LO_SUBPASS_1_IN_COLOR, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_COLOR_INPUT) uniform subpassInput in_attachment_color;
layout (input_attachment_index = BSGFX_LO_SUBPASS_1_IN_NORMAL, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_NORMAL_INPUT) uniform subpassInput in_attachment_normal;
//layout (input_attachment_index = BSGFX_SUBPASS_0_IN_POSITION, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_POSITION_INPUT) uniform subpassInput in_attachment_position;
layout (input_attachment_index = BSGFX_LO_SUBPASS_1_IN_INDEX, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_INDEX_INPUT) uniform usubpassInput in_attachment_index;
layout (input_attachment_index = BSGFX_LO_SUBPASS_1_IN_FLAGS, set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_FLAGS_INPUT) uniform usubpassInput in_attachment_flags;

layout(set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_COLOR_ATTACHMENT) uniform sampler2D in_attachment_color_read;
layout(set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_DEPTH_ATTACHMENT) uniform sampler2D in_attachment_depth_read;
layout(set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_INDEX_ATTACHMENT) uniform usampler2D in_attachment_index_read;
layout(set = BSGFX_SET_LO_RES_0, binding = BSGFX_BINDING_LO_RES_0_FLAGS_ATTACHMENT) uniform usampler2D in_attachment_flags_read;

layout(push_constant) uniform constants {
    vec2 camera_offset;
    float elapsed;
} pushConst;

vec3 bsgfx_directionalLight(vec3 direction, vec3 normal, vec3 color) {
    vec3 light_direction = normalize(-direction);
       
    // diffuse shading
    float _diff = max(dot(normalize(normal), light_direction), 0.0) + 0.5;
       
    // specular shading
   // vec3 halfWay = normalize(light_direction + viewDir);
       
   // float spec = pow(max(dot(halfWay, normal), 0.0), material.shininess);
   // vec3 specular = light.specular * spec * material.specular;
      

    const float cdiffuse = 0.8;
    const vec3 cambient = vec3(0.9, 0.83, 0.71);
    vec3 diffuse = cdiffuse * _diff * color;
          
       
    vec3 ambient = 0.2 * (cambient /*  *material.ambient */);
      return _diff * color;
    return (ambient + diffuse /*+ specular + material.emission */);
}

float hash(vec2 p) {
    return fract(sin(dot(p ,vec2(127.1, 311.7))) * 43758.5453);
}

vec2 bsgfx_sineWave(vec2 uv, vec2 world_uv) {
   // float speed = 3.0;
   // float offset = hash(floor(world_uv * 50.0)) * 8.2831;
   // return uv + vec2(sin(world_uv.y * 40.0 + pushConst.elapsed * speed) , cos(world_uv.x * 40.0 + pushConst.elapsed * speed)) * 0.005;

    float time = pushConst.elapsed * 3.0;
    float strength = 0.002;
    float frequency = 100.0;

    float offset = hash(floor(world_uv * 45.0)) * 10.0;

    float warpX = sin(-world_uv.y * frequency + pushConst.elapsed * 5.0 + offset) * strength;
    float warpY = cos(-world_uv.x * frequency + pushConst.elapsed * 3.0 + offset) * strength;

    uv.x += warpX;
    uv.y += warpY;

    return uv;
}

// https://github.com/SableRaf/Filters4Processing/blob/master/sketches/ContrastSaturationBrightness/data/ContrastSaturationBrightness.glsl
vec3 bsgfx_csb(vec3 color, float brt, float sat, float con) {
	// Increase or decrease theese values to adjust r, g and b color channels seperately
	const float AvgLumR = 0.5;
	const float AvgLumG = 0.5;
	const float AvgLumB = 0.5;
	
	const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);
	
	vec3 AvgLumin  = vec3(AvgLumR, AvgLumG, AvgLumB);
	vec3 brtColor  = color * brt;
	vec3 intensity = vec3(dot(brtColor, LumCoeff));
	vec3 satColor  = mix(intensity, brtColor, sat);
	vec3 conColor  = mix(AvgLumin, satColor, con);
	
	return conColor;
}

void main() {
    vec3 color = subpassLoad(in_attachment_color).rgb;
    vec3 normal = subpassLoad(in_attachment_normal).rgb;
    //vec3 position = subpassLoad(in_attachment_position).rgb;
    vec3 direction = normalize(vec3(-0.7, -0.8, -0.4));

   // vec3 result = bsgfx_directionalLight(direction, normal, color);

    out_color = vec4(color, 1.0);

    uint index = subpassLoad(in_attachment_index).r;
    uint flags = subpassLoad(in_attachment_flags).r;
    uint instance_id = index;
    int instance_type = findLSB(flags);

    if ((flags & BSGFX_ID_IS_WATER) != 0) {
        vec2 world_texture = in_texture.xy + pushConst.camera_offset;
        vec2 warped_texture = bsgfx_sineWave(in_texture.xy, world_texture);

        ivec2 textureSizePixels = textureSize(in_attachment_index_read, 0);
        vec2 texelSize = 1.0 / vec2(textureSizePixels);

        float w = 1;//bsgfx_mesh_instances[instance_id].transform[0][3];
        float h = 1;//bsgfx_mesh_instances[instance_id].transform[1][3];
        w = 1.0;
        h = 1.0;
        vec2 scale = vec2(2.4);
        scale.x = scale.y * 0.7071;
        vec2 direction_00 = vec2(0.04, 0.02);
        vec2 direction_01 = vec2(-0.04, 0.02);

//        vec3 color = mix(
//            texture(images, vec3(vec2(pushConst.elapsed) * direction_00 + (world_texture + vec2(0.5)) * vec2(w, h) * scale, pushConst.noise_00)).xyz,
//            texture(images, vec3(vec2(pushConst.elapsed) * direction_01 + world_texture * vec2(w, h) * scale, pushConst.noise_00)).xyz, 0.5);

        vec3 color = bsgfx_csb(color, 1.3, 0.8, 2.5);

        if (color.z > 1.0)
            color.z = 1.0;
        color.xyz *= vec3(40, 100, 165) / 255.0;

        vec3 dark = vec3(30, 100, 120) / 255.0;
        vec3 bright = vec3(155, 195, 200) / 255.0;

        float brightness = dot(color.xyz, vec3(0.2126, 0.7152, 0.0722));
        if (brightness < 0.49)
            color = dark;

        vec3 final = bsgfx_directionalLight(direction, normal, texture(in_attachment_color_read, vec2(warped_texture.x, 1.0 - warped_texture.y)).xyz);
        out_color.xyz = mix(final, color, 0.4);
        if (brightness > 0.62)
            out_color.xyz = bright;

       // if ((flags & BSGFX_ID_IN_SHADOW) != 0) {
       //  //   out_color.xyz *= vec3(1.0, 0.8, 0.7);
       // }

        float offset = 1.0;
        if (sin((world_texture.x * -100.0 + pushConst.elapsed * 4.0)) > 0.5)
            offset = -1.0;

        uint up = texture(in_attachment_flags_read, vec2(warped_texture.x, 1.0 - warped_texture.y - texelSize.x * offset)).r;
        uint up2 = texture(in_attachment_flags_read, vec2(warped_texture.x, 1.0 - warped_texture.y - texelSize.x * (offset + 1.0))).r;

        uint right = texture(in_attachment_flags_read, vec2(warped_texture.x + texelSize.x, 1.0 - warped_texture.y)).r;
        uint left = texture(in_attachment_flags_read, vec2(warped_texture.x - texelSize.x, 1.0 - warped_texture.y)).r;

        float depth = texture(in_attachment_depth_read, vec2(in_texture.x, 1.0 - in_texture.y)).r;
        float up_depth = texture(in_attachment_depth_read, vec2(in_texture.x, 1.0 - in_texture.y - texelSize.y)).r;
        float down_depth = texture(in_attachment_depth_read, vec2(in_texture.x, 1.0 - in_texture.y + texelSize.y)).r;
        float left_depth = texture(in_attachment_depth_read, vec2(in_texture.x - texelSize.x, 1.0 - in_texture.y)).r;
        float right_depth = texture(in_attachment_depth_read, vec2(in_texture.x + texelSize.x, 1.0 - in_texture.y)).r;

        if ((depth + 0.0001) > up_depth ) {
            if ((up & BSGFX_ID_IS_WATER) == 0)
                out_color.xyz = out_color.xyz;
            else if ((up2 & BSGFX_ID_IS_WATER) == 0)
                out_color.xyz = mix(out_color.xyz, bright, 0.6);
            else if ((right & BSGFX_ID_IS_WATER) == 0)
                out_color.xyz = mix(out_color.xyz, bright, 0.6);
            else if ((left & BSGFX_ID_IS_WATER) == 0)
                out_color.xyz = mix(out_color.xyz, bright, 0.6);
        }


        if ((down_depth + 0.001) < depth)
            out_color.xyz = vec3(1.0, 0.0, 0.0);
        if ((up_depth + 0.0001) < depth)
            out_color.xyz = vec3(0.0, 1.0 , 0.0);

     //   out_color.xyz = vec3(depth);
     //   out_color.xyz = vec3(1.0);
        out_color.w = 1.0;
    }
}
