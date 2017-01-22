/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifdef __cplusplus
extern "C"{
#endif

#ifndef __spritetools_animation_h

#define __spritetools_animation_h

#include <spritetools_spritesheet.h>

/********************\
|*     Typedefs     *|
\********************/
/* Frame of animation from a spritesheet */
typedef struct {
  st_spritesheet *spritesheet;
  u32 xleft;
  u32 ytop;
  u32 width;
  u32 height;
  s32 xoff;
  s32 yoff;
} st_frame;

/* Animation of frames */
typedef struct {
  s16 fpf; /* Number of frames to wait between each frame of animation */
  u16 ftn; /* Counts number of frames between displayed frame */
  u16 loopFrame; /* Frame to jump to when an animation loops */
  u16 length; /* Number of frames in the animation */
  st_frame **frames;
  u16 currentFrame;
} st_animation;

/***************************\
|*     Frame Functions     *|
\***************************/
/* Returns a pointer to a frame */
/*   Returns NULL if failed */
/* Takes a pointer to a spritesheet */
/*   Takes the position of the frame in the spritesheet */
/*   Takes the dimensions of the frame */
st_frame *ST_AnimationCreateFrame(st_spritesheet *spritesheet,
  u32 xleft, u32 ytop, u32 width, u32 height);

/* Returns a pointer to a frame */
/*   Returns NULL if failed */
/* Takes a pointer to a spritesheet */
/*   Takes the position of the frame in the spritesheet */
/*   Takes the dimensions of the frame */
/*   Takes offset for rendering (hotspot) */
st_frame *ST_AnimationCreateFrameOffset(st_spritesheet *spritesheet,
  u32 xleft, u32 ytop, u32 width, u32 height, s32 xoff, s32 yoff);

/* Frees frame from memory */
/* Takes a pointer to a frame */
void ST_AnimationFreeFrame(st_frame *frame);

/*******************************\
|*     Animation Functions     *|
\*******************************/
/* Returns a pointer to an animation */
/*   Returns NULL if failed */
/* Takes speed of animation (in frames between each frame of animation) */
/*   Takes frame to loop to when the animation has reached its end */
/*   Takes length of animation in frames */
/*   Takes a list of pointers to frames */
st_animation *ST_AnimationCreateAnimation(s16 fpf, u16 loopFrame,
  u16 length, ...);

/* Frees an animation and all of its frames from memory */
/* Takes a pointer to an animation */
void ST_AnimationFreeAnimation(st_animation *animation);

/* Sets the current frame of an animation */
/* Takes a pointer to an animation and frame to go to */
void ST_AnimationSetFrame(st_animation *animation, u16 frame);

/* Adds 1 to the current frame of an animation. Wraps to 0 if needed */
/* Takes a pointer to an animation */
void ST_AnimationNextFrame(st_animation *animation);

/* Subs 1 from the current frame of an animation */
/*   Wraps to the last frame if needed */
/* Takes a pointer to an animation */
void ST_AnimationPreviousFrame(st_animation *animation);

/* Sets the speed (fpf) of an animation */
/* Takes a pointer to an animation and frame to go to */
void ST_AnimationSetSpeed(st_animation *animation, s16 speed);

#endif

#ifdef __cplusplus
}
#endif
