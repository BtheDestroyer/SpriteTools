/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifndef __spritetools_animation_h

#define __spritetools_animation_h

#include <spritetools_spritesheet.h>

/********************\
|*     Typedefs     *|
\********************/
/* Frame of animation from a spritesheet */
typedef struct {
  st_spritesheet *spritesheet;
  unsigned int xleft;
  unsigned int ytop;
  unsigned int width;
  unsigned int height;
} st_frame;

/* Animation of frames */
typedef struct {
  int fpf; /* Number of frames to wait between each frame of animation */
  unsigned int loopFrame; /* Frame to jump to when an animation loops */
  unsigned int length; /* Number of frames in the animation */
  st_frame **frames;
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
  unsigned int xleft, unsigned int ytop,
  unsigned int width, unsigned int height);

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
st_animation *ST_AnimationCreateAnimation(int fpf, unsigned int loopFrame,
  unsigned int length, ...);

#endif
