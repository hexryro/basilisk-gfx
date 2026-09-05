
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
#include <assert.h>

#include <string.h>

 /**
  Current frame
  */
BSGFXAPI int _val_bsgfx_animationFrame(bs_Animation* animation, float time, int frames_count) {
    BSGFX_VALIDATE(frames_count > 0, 0,);
    return _bsgfx_animationFrame(animation, time, frames_count);
}

BSGFXAPI int _bsgfx_animationFrame(bs_Animation* animation, float time, int frames_count) {
    return time / animation->length * (float)(frames_count);
}

 /**
  Frame count
  */
BSGFXAPI int _val_bsgfx_animationFrameCount(bs_Animation* animation, float time_scale) {
    BSGFX_VALIDATE(time_scale != 0.0, 0,);
    return _bsgfx_animationFrameCount(animation, time_scale);
}

BSGFXAPI int _bsgfx_animationFrameCount(bs_Animation* animation, float time_scale) {
    return (int)(animation->length / time_scale);
}

 /**
  Apply animation velocity
  */
BSGFXAPI void _val_bsgfx_applyAnimationVelocity(bsgfx_Animator* animator, bs_vec3* velocity, bs_vec2 input) {
    BSGFX_VALIDATE(animator->current_animation_id >= 0,,);
    BSGFX_VALIDATE(animator->current_animation_id < animator->animations_count,,);

    _bsgfx_applyAnimationVelocity(animator, velocity, input);
}

BSGFXAPI void _bsgfx_applyAnimationVelocity(bsgfx_Animator* animator, bs_vec3* velocity, bs_vec2 input) {

    bs_Animation* animation = animator->animations + animator->current_animation_id;

    int root_id = bs_queryBoneId(animator->armature, "Root");
    int frames_count = animation->frames_count - 1;

    float mag = sqrt(input.x * input.x + input.y * input.y);
    if (mag > 1.0f) {
        input.x /= mag;
        input.y /= mag;
    }

    const float epsilon = 1e-6;

    float time = animator->time;
    float previous_time = animator->previous_time;

    int previous_frame = _bsgfx_animationFrame(animation, previous_time, frames_count);
    int frame = _bsgfx_animationFrame(animation, time, frames_count);
    if (previous_frame == frame || frame >= frames_count) {
        return;
    }

    animator->previous_time = time;

    bs_vec3 previous_translation = { 0 };
    bs_vec4 previous_rotation = { 0 };

    if (frame != 0) {
        previous_translation = animation->bones[root_id].translations[frame].value;
        previous_rotation = animation->bones[root_id].rotations[frame].value;
    }

    bs_vec3 current_translation = animation->bones[root_id].translations[frame + 1].value;
    bs_vec4 current_rotation = animation->bones[root_id].rotations[frame + 1].value;

    bs_vec3 translation_diff;
    bs_v3Sub(&current_translation, &previous_translation, &translation_diff);
    bs_v3MulS(&translation_diff, -1, &translation_diff);

    velocity->x += input.x * translation_diff.z;
    //  velocity.y += -diff.y;
    velocity->z += -input.y * translation_diff.z;

    //duL_set("animation_velocity", translation_diff, -2);
    //if (bs_abs(velocity->x) > epsilon ||
    //    bs_abs(velocity->z) > epsilon)
    //    duL_set("direction", bs_v2NormalizeV2(input.x, input.y), -2);
}

/*
void _bsgfx_setPose(int skeleton, bs_Armature* armature, bs_Animation* animation, float time) {
    bs_blendPose(armature, animation, NULL, 0.0, time, time);

}

void _bsgfx_runAnimatorUnfixed(bsgfx_Entity* entity) {
    _bsgfx_runAnimatorCallback(entity, "unfixed", entity->armature->animation);
    _bsgfx_readEntityComponent(entity, BSGFX_COMPONENT_ARMATURE);
}
*/

static inline void _bsgfx_animateOnceDefault(bsgfx_Animator* animator) {
    animator->time = 0.0;
}

static inline void _bsgfx_animateTickDefault(bsgfx_Animator* animator) {
    animator->time += bs_deltaTime();
}

static inline void _bsgfx_animateLoopDefault(bsgfx_Animator* animator) {
    animator->time = 0.0;
}

static inline void _bsgfx_animateExitDefault(bsgfx_Animator* animator) {
}

static inline void _bsgfx_animatePoseDefault(bsgfx_Animator* animator) {
    bs_Animation* animation_a = animator->animations + animator->current_animation_id;
    bs_Animation* animation_b = animator->current_blend_animation_id >= 0 ? animator->animations + animator->current_blend_animation_id : NULL;

    bs_blendPose(animator->armature, animation_a, animation_b, animator->blend_factor, animator->time, animator->time);
}

BSGFXAPI void _bsgfx_queueAnimation(bsgfx_Animator* animator, int animation_id) {
    animator->queued_animation_id = animation_id;
}

BSGFXAPI void _val_bsgfx_runAnimator(bsgfx_Animator* animator, bsgfx_AnimatorCallbacks callbacks) {
    BSGFX_VALIDATE(animator->current_animation_id >= 0,,);
    BSGFX_VALIDATE(animator->current_animation_id < animator->animations_count,,);
    BSGFX_VALIDATE(animator->queued_animation_id >= 0,,);
    BSGFX_VALIDATE(animator->queued_animation_id < animator->animations_count, , );
    BSGFX_VALIDATE(_bsgfx_shader_joints_ != NULL, , );

    _bsgfx_runAnimator(animator, callbacks);
}

BSGFXAPI void _bsgfx_runAnimator(bsgfx_Animator* animator, bsgfx_AnimatorCallbacks callbacks) {
    bs_Animation* queued_animation = animator->animations + animator->queued_animation_id;
    bs_Animation* blend_animation = animator->animations + animator->current_blend_animation_id; // dangling but its fine just do checks pussy
    float length = queued_animation->length;

    if (animator->current_animation_id != animator->queued_animation_id) {
        char* new_name = queued_animation->name;

        bs_Animation* animation = animator->animations + animator->current_animation_id;
        if (animator->current_blend_animation_id >= 0)
            bs_infoF("%s / %s (%f) -> %s\n", animation->name, blend_animation->name, animator->blend_factor, new_name);
        else
            bs_infoF("%s -> %s\n", animation->name, new_name);

        animator->current_animation_id = animator->queued_animation_id;
        animator->current_blend_animation_id = -1;
        animator->blend_factor = 0.0;

        if (animator->exit) animator->exit();
        else _bsgfx_animateExitDefault(animator);
        if (callbacks.once) callbacks.once(animator);
        else _bsgfx_animateOnceDefault(animator);
    }

    if (callbacks.once_per_tick) callbacks.once_per_tick(animator);
    else _bsgfx_animateTickDefault(animator);

    if (animator->time > length) {
        if (callbacks.once_per_loop) callbacks.once_per_loop(animator);
        else _bsgfx_animateLoopDefault(animator);
    }

    if (callbacks.pose) callbacks.pose(animator);
    else _bsgfx_animatePoseDefault(animator);

    bs_Animation* animation = animator->animations + animator->current_animation_id;
    bs_Armature* armature = animator->armature;
    int root_id = bs_queryBoneId(armature, "Root");
    if (root_id >= 0)
        animation->bones[root_id].translations_count =
        animation->bones[root_id].rotations_count =
        animation->bones[root_id].scalings_count = 0;

    for (int i = 0; i < BS_MIN(animation->bones_count, armature->bones_count); i++)
        _bsgfx_shader_joints_[animator->skeleton + i] = armature->bones[i].matrix;

    animator->exit = callbacks.once_per_exit;
}

 /**
  Create skeleton
  */
BSGFXAPI int _val_bsgfx_skeleton(bs_Armature* armature) {
    BSGFX_VALIDATE(_bsgfx_shader_joints_ != NULL, -1, );

    return _bsgfx_skeleton(armature);
}

BSGFXAPI int _bsgfx_skeleton(bs_Armature* armature) {
    for (int i = 0; i < armature->bones_count; i++)
        _bsgfx_shader_joints_[_bsgfx_num_shader_joints_ + i] = BS_MAT4_IDENTITY;
    _bsgfx_num_shader_joints_ += armature->bones_count;

    bs_infoF("Created skeleton for armature %s\n", armature->name);
    return _bsgfx_num_shader_joints_ - armature->bones_count;
}

BSGFXAPI bsgfx_Animator _bsgfx_animator(bs_Armature* armature, int resting_animation_id, int animations_count) {
    int skeleton = _bsgfx_skeleton(armature);

    //bs_blendPose(armature, resting_animation, NULL, 0.0, 0.0, 0.0);

    return (bsgfx_Animator) {
        .armature = armature,
        .queued_animation_id = resting_animation_id,
        .current_animation_id = resting_animation_id,
        .skeleton = skeleton,
        .animations = bs_calloc(animations_count, sizeof(bs_Animation)),
        .animations_count = animations_count,
    };
}